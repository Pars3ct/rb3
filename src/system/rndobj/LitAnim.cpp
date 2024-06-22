#include "rndobj/LitAnim.h"
#include "os/Debug.h"
#include "utl/Symbols.h"

int LIGHTANIM_REV = 2;

RndLightAnim::RndLightAnim() : mLight(this, 0), mKeysOwner(this, this) {

}

void RndLightAnim::SetKeysOwner(RndLightAnim* o){
    MILO_ASSERT(o, 0x27);
    mKeysOwner = o;
}

void RndLightAnim::Replace(Hmx::Object* from, Hmx::Object* to){
    Hmx::Object::Replace(from, to);
    if(mKeysOwner.Ptr() == from){
        if(!to) mKeysOwner = this;
        else mKeysOwner = dynamic_cast<RndLightAnim*>(to)->mKeysOwner.Ptr();
    }
}

SAVE_OBJ(RndLightAnim, 0x46);

void RndLightAnim::Load(BinStream& bs){
    int rev;
    bs >> rev;
    ASSERT_GLOBAL_REV(rev, LIGHTANIM_REV);
    if(rev > 1) Hmx::Object::Load(bs);
    RndAnimatable::Load(bs);
    bs >> mLight;
    if(rev < 1){
        Keys<Hmx::Color, Hmx::Color> keys;
        bs >> keys;
    }
    bs >> mColorKeys;
    if(rev < 1){
        Keys<Hmx::Color, Hmx::Color> keys;
        bs >> keys;
    }
    bs >> mKeysOwner;
    if(!mKeysOwner.Ptr()){
        mKeysOwner = this;
    }
}

BEGIN_COPYS(RndLightAnim)
    CREATE_COPY_AS(RndLightAnim, l)
    MILO_ASSERT(l, 0x6B);
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(RndAnimatable)
    COPY_MEMBER_FROM(l, mLight)
    if(ty == kCopyShallow || (ty == kCopyFromMax && l->mKeysOwner != l)){
        COPY_MEMBER_FROM(l, mKeysOwner)
    }
    else {
        mKeysOwner = this;
        mColorKeys = l->mKeysOwner->mColorKeys;
    }
END_COPYS

void RndLightAnim::Print(){
    TextStream& ts = TheDebug;
    ts << "   light: " << mLight.Ptr() << "\n";
    ts << "   keysOwner: " << mKeysOwner.Ptr() << "\n";
    ts << "   colorKeys: " << mColorKeys << "\n";
}

float RndLightAnim::EndFrame(){
    Keys<Hmx::Color, Hmx::Color>& keys = mKeysOwner->mColorKeys;
    int size = keys.size();
    if(size != 0) return keys[size].frame;
    else return 0.0f;
}

BEGIN_HANDLERS(RndLightAnim)
    HANDLE(copy_keys, OnCopyKeys)
    HANDLE_SUPERCLASS(RndAnimatable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0xBF)
END_HANDLERS

BEGIN_PROPSYNCS(RndLightAnim)
    SYNC_SUPERCLASS(RndAnimatable)
END_PROPSYNCS
