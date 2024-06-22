#include "ui/PanelDir.h"
#include "obj/ObjMacros.h"
#include "obj/ObjPtr_p.h"
#include "obj/Object.h"
#include "obj/ObjVersion.h"
#include "ui/UIComponent.h"
#include "ui/UIPanel.h"
#include "rndobj/Cam.h"
#include "rndobj/Rnd.h"
#include "ui/Utl.h"
#include "ui/UITrigger.h"
#include "ui/UI.h"
#include "ui/UIMessages.h"
#include "utl/Messages.h"
#include "utl/Symbols.h"

INIT_REVS(PanelDir)
bool gSendFocusMsg;
bool PanelDir::sAlwaysNeedFocus;

PanelDir::PanelDir() : mFocusComponent(0), mOwnerPanel(0), mCam(this, 0), mCanEndWorld(1), mUseSpecifiedCam(0), mShowEditModePanels(0), mShowFocusComponent(1) {
    if(TheLoadMgr.EditMode()) mShowEditModePanels = true;
}

PanelDir::~PanelDir() {
    for (std::vector<class PanelDir*>::iterator it = mBackPanels.begin(); it != mBackPanels.end(); it++) {
        delete (*it);
        *it = NULL;
    }
    for (std::vector<class PanelDir*>::iterator it = mFrontPanels.begin(); it != mFrontPanels.end(); it++) {
        delete (*it);
        *it = NULL;
    }
}

SAVE_OBJ(PanelDir, 57)

void PanelDir::PreLoad(BinStream& bs) {
    LOAD_REVS(bs)
    ASSERT_REVS(8, 0)
    PushRev(packRevs(gAltRev, gRev), this);    
    RndDir::PreLoad(bs);
}

void PanelDir::PostLoad(BinStream& bs){
    RndDir::PostLoad(bs);
    int revs = PopRev(this);
    gAltRev = getAltRev(revs);
    gRev = getHmxRev(revs);
    if(this == Dir()){
        if(gRev != 0) bs >> mCam;
        if(gRev == 2){
            Symbol s;
            bs >> s;
        }
    }
    if(gRev > 3) bs >> mCanEndWorld;
    if(gRev > 4) bs >> mBackFilenames >> mFrontFilenames;
    if(gRev > 5) bs >> mShowEditModePanels;
    if(gRev > 7){
        if(gLoadingProxyFromDisk){
            bool b;
            bs >> b;
        }
        else bs >> mUseSpecifiedCam;
    }
    SyncEditModePanels();
}

BEGIN_COPYS(PanelDir)
    COPY_SUPERCLASS(RndDir)
    CREATE_COPY(PanelDir)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mCam)
        COPY_MEMBER(mCanEndWorld)
        COPY_MEMBER(mBackFilenames)
        COPY_MEMBER(mFrontFilenames)
        COPY_MEMBER(mShowEditModePanels)
        COPY_MEMBER(mUseSpecifiedCam)
        SyncEditModePanels();
    END_COPYING_MEMBERS
END_COPYS

// fn_8054B508
void PanelDir::SyncObjects(){
    RndDir::SyncObjects();
    mComponents.clear();
    for(ObjDirItr<UIComponent> it(this, true); it != 0; ++it){
        AddComponent(it);
    }
    mTriggers.clear();
    for(ObjDirItr<UITrigger> it(this, true); it != 0; ++it){
        mTriggers.push_back(it);
        it->CheckAnims();
    }
    if(sAlwaysNeedFocus){
        UIComponent* comp = GetFirstFocusableComponent();
        if(!mFocusComponent && comp){
            gSendFocusMsg = false;
            SetFocusComponent(comp, gNullStr);
            gSendFocusMsg = true;
        }
    }
}

void PanelDir::RemovingObject(Hmx::Object* o){
    ObjMatchPr pr;
    pr.obj = o;
    // mComponents.remove_if(pr);
}

RndCam* PanelDir::CamOverride(){
    if(TheLoadMgr.EditMode() && !mUseSpecifiedCam) return 0;
    if(mCam) return mCam;
    return TheUI->unk34;
}

void PanelDir::DrawShowing(){
    if(mCanEndWorld) TheRnd->EndWorld();
    RndCam* curCam = RndCam::sCurrent;
    RndCam* camOverride = CamOverride();
    if(camOverride && camOverride != RndCam::sCurrent){
        camOverride->Select();
    }
    if(!mEnv){
        RndEnviron* curEnv = TheUI->unk38;
        if(curEnv != RndEnviron::sCurrent){
            curEnv->Select(0);
        }
    }
    for(std::vector<PanelDir*>::iterator it = mBackPanels.begin(); it != mBackPanels.end(); ++it){
        if(*it) (*it)->DrawShowing();
    }
    RndDir::DrawShowing();
    for(std::vector<PanelDir*>::iterator it = mFrontPanels.begin(); it != mFrontPanels.end(); ++it){
        if(*it) (*it)->DrawShowing();
    }
    if(curCam && curCam != RndCam::sCurrent){
        curCam->Select();
    }
}

void PanelDir::Enter(){
    RndDir::Enter();
    for(std::list<UITrigger*>::iterator it = mTriggers.begin(); it != mTriggers.end(); it++){
        (*it)->Enter();
    }
    SendTransition(ui_enter_msg, ui_enter_forward, ui_enter_back);
}

void PanelDir::Exit(){
    RndDir::Exit();
    SendTransition(ui_exit_msg, ui_exit_forward, ui_exit_back);
}

#pragma push
#pragma pool_data off
void PanelDir::SendTransition(const Message& msg, Symbol s1, Symbol s2){
    static Message dirMsg = Message("");
    dirMsg->Node(1) = DataNode(TheUI->WentBack() ? s2 : s1);
    RndDir::Handle(msg, false);
    RndDir::Handle(dirMsg, false);
}
#pragma pop

bool PanelDir::Entering() const {
    for(std::list<UIComponent*>::const_iterator compIt = mComponents.begin(); compIt != mComponents.end(); compIt++){
        if((*compIt)->Entering()) return true;
    }
    for(std::list<UITrigger*>::const_iterator trigIt = mTriggers.begin(); trigIt != mTriggers.end(); trigIt++){
        if((*trigIt)->IsBlocking()) return true;
    }
    return false;
}

bool PanelDir::Exiting() const {
    for(std::list<UIComponent*>::const_iterator compIt = mComponents.begin(); compIt != mComponents.end(); compIt++){
        if((*compIt)->Exiting()) return true;
    }
    for(std::list<UITrigger*>::const_iterator trigIt = mTriggers.begin(); trigIt != mTriggers.end(); trigIt++){
        if((*trigIt)->IsBlocking()) return true;
    }
    return false;
}

UIComponent* PanelDir::FindComponent(const char* cc){
    return dynamic_cast<UIComponent*>(FindObject(cc, false));
}

void PanelDir::AddComponent(UIComponent* c){
    mComponents.push_back(c);
}

void PanelDir::SetFocusComponent(UIComponent* c, Symbol s){
    if(c && !c->CanHaveFocus()) MILO_WARN("Trying to set focus on a component that can't have focus.  Component: %s", c->Name());
    else if(c != mFocusComponent){
        UIComponent* focused = FocusComponent();
        if(mFocusComponent && mFocusComponent->GetState() != UIComponent::kDisabled){
            mFocusComponent->SetState(UIComponent::kNormal);
        }
        mFocusComponent = c;
        UpdateFocusComponentState();
        if(gSendFocusMsg){
            TheUI->Handle(UIComponentFocusChangeMsg(c, focused, this, s), false);
        }
    }
}

void PanelDir::SetShowFocusComponent(bool b){
    mShowFocusComponent = b;
    UpdateFocusComponentState();
}

void PanelDir::UpdateFocusComponentState(){
    if(!mFocusComponent) return;
    if(mShowFocusComponent) mFocusComponent->SetState(UIComponent::kFocused);
    else mFocusComponent->SetState(UIComponent::kNormal);
}

void PanelDir::EnableComponent(UIComponent* c, PanelDir::RequestFocus req){
    if(c->GetState() == UIComponent::kDisabled) c->SetState(UIComponent::kNormal);
    if(c->CanHaveFocus() && (req == kAlwaysFocus || (req == kMaybeFocus && !mFocusComponent))){
        SetFocusComponent(c, gNullStr);
    }
}

void PanelDir::DisableComponent(UIComponent* c, JoypadAction nav_action){
    MILO_ASSERT(nav_action == kAction_None || IsNavAction(nav_action), 0x18C);
    if(c == mFocusComponent){
        if(nav_action == kAction_None){
            PanelNav(kAction_Down, kPad_NumButtons, none);
            if(c == mFocusComponent){
                PanelNav(kAction_Up, kPad_NumButtons, none);
            }
        }
        else PanelNav(nav_action, kPad_NumButtons, none);
    }
    if(c == mFocusComponent) mFocusComponent = 0;
    c->SetState(UIComponent::kDisabled);
}

DataNode PanelDir::GetFocusableComponentList(){
    std::vector<UIComponent*> components;
    for(std::list<UIComponent*>::iterator it = mComponents.begin(); it != mComponents.end(); ++it){
        UIComponent* component = *it;
        MILO_ASSERT(component, 0x1B8);
        if(component->CanHaveFocus()){
            components.push_back(component);
        }
    }
    DataArrayPtr ptr(new DataArray(components.size()));
    int i = 0;
    for(std::vector<UIComponent*>::iterator it = components.begin(); it != components.end(); ++it, i++){
        ptr.Node(i) = DataNode(*it);
    }
    return DataNode(ptr);
}

UIComponent* PanelDir::GetFirstFocusableComponent(){
    UIComponent* ret = 0;
    for(std::list<UIComponent*>::iterator it = mComponents.begin(); it != mComponents.end(); ++it){
        UIComponent* component = *it;
        MILO_ASSERT(component, 0x1D8);
        if(component->CanHaveFocus()){
            ret = component;
            break;
        }
    }
    return ret;
}

BEGIN_HANDLERS(PanelDir)
    HANDLE(enable, OnEnableComponent)
    HANDLE(disable, OnDisableComponent)
    HANDLE_ACTION(set_focus, SetFocusComponent(_msg->Obj<UIComponent>(2), gNullStr))
    HANDLE_EXPR(focus_name, mFocusComponent ? mFocusComponent->Name() : "")
    if(sym == get_focusable_components){ return GetFocusableComponentList(); }
    HANDLE_ACTION(set_show_focus_component, SetShowFocusComponent(_msg->Int(2)))
    HANDLE_SUPERCLASS(RndDir)
    HANDLE_MESSAGE(ButtonDownMsg)
    if(sym != "button_down") HANDLE_MEMBER_PTR(mFocusComponent)
    HANDLE_CHECK(0x1FC)
END_HANDLERS

DataNode PanelDir::OnMsg(const ButtonDownMsg& msg){
    DataNode node(kDataUnhandled, 0);
    if(mFocusComponent){
        node = mFocusComponent->Handle(msg, false);
    }
    if(node.Type() == kDataUnhandled){
        if(PanelNav(msg.GetAction(), msg.GetButton(), JoypadControllerTypePadNum(msg.GetPadNum()))){
            return DataNode(0);
        }
    }
    return DataNode(node);
}

DataNode PanelDir::OnEnableComponent(const DataArray* da){
    UIComponent* c = da->Obj<UIComponent>(2);
    if(da->Size() == 4){
        EnableComponent(c, (RequestFocus)da->Int(3));
    }
    else if(da->Size() == 3){
        EnableComponent(c, (RequestFocus)0);
    }
    else MILO_WARN("wrong number of args to PanelDir enable");
    return DataNode(0);
}

DataNode PanelDir::OnDisableComponent(const DataArray* da){
    UIComponent* c = da->Obj<UIComponent>(2);
    if(da->Size() == 4){
        DisableComponent(c, (JoypadAction)da->Int(3));
    }
    else if(da->Size() == 3){
        DisableComponent(c, kAction_None);
    }
    else MILO_WARN("wrong number of args to PanelDir disable");
    return DataNode(0);
}

BEGIN_PROPSYNCS(PanelDir)
    SYNC_PROP(cam, mCam)
    SYNC_PROP(postprocs_before_draw, mCanEndWorld)
    SYNC_PROP(use_specified_cam, mUseSpecifiedCam)
    SYNC_PROP(focus_component, mFocusComponent)
    SYNC_PROP(owner_panel, mOwnerPanel)
    {
        static Symbol _s("front_view_only_panels");
        if(sym == _s){
            PropSyncEditModePanels(mFrontFilenames, _val, _prop, _i + 1, _op);
            return true;
        }
    }
    {
        static Symbol _s("back_view_only_panels");
        if(sym == _s){
            PropSyncEditModePanels(mBackFilenames, _val, _prop, _i + 1, _op);
            return true;
        }
    }
    SYNC_PROP_MODIFY(show_view_only_panels, mShowEditModePanels, SyncEditModePanels())
    SYNC_SUPERCLASS(RndDir)
END_PROPSYNCS