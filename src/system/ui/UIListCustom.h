#ifndef UI_UILISTCUSTOM_H
#define UI_UILISTCUSTOM_H

#include "obj/Dir.h"
#include "obj/ObjMacros.h"
#include "obj/ObjPtr_p.h"
#include "obj/Object.h"
#include "rndobj/Trans.h"
#include "ui/UIComponent.h"
#include "ui/UIListProvider.h"
#include "ui/UIListSlot.h"

class UIListCustomTemplate {
public:
    UIListCustomTemplate(){}
    virtual ~UIListCustomTemplate(){}
    virtual void SetAlphaColor(float, UIColor*) = 0;
    virtual void GrowBoundingBox(Box&) const = 0;
};

class UIListCustom : public UIListSlot {
public:
    UIListCustom();
    virtual ~UIListCustom() {}
    OBJ_CLASSNAME(UIListCustom)
    OBJ_SET_TYPE(UIListCustom)
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, CopyType);
    virtual void Load(BinStream&);
    virtual void CreateElement(UIList*);
    virtual RndTransformable* RootTrans();

    void SetObject(Hmx::Object*);

    ObjPtr<Hmx::Object, ObjectDir> mObject;

    NEW_OBJ(UIListCustom)
    DECLARE_REVS
};

class UIListCustomElement : public UIListSlotElement {
    public:
    UIListCustomElement(class UIListCustom* own, Hmx::Object* ptr) : mOwner(own), mPtr(ptr) {}
    virtual ~UIListCustomElement() { delete mPtr; }
    virtual void Fill(const UIListProvider& p, int i1, int i2) { p.Custom(i1, i2, mOwner, mPtr); }
    virtual void Draw(const Transform&, float, UIColor*, Box*);

    class UIListCustom* mOwner;
    Hmx::Object* mPtr;
};

#endif // UI_UILISTCUSTOM_H
