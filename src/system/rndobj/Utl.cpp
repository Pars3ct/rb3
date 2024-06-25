#include "rndobj/Utl.h"
#include "math/Color.h"
#include "math/Geo.h"
#include "obj/Data.h"
#include "obj/DataFunc.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "os/System.h"
#include "rndobj/Cam.h"
#include "rndobj/Draw.h"
#include "rndobj/Env.h"
#include "rndobj/Group.h"
#include "rndobj/Mesh.h"
#include "rndobj/MultiMesh.h"
#include "rndobj/Rnd.h"
#include "utl/Loader.h"
#include "math/Key.h"
#include <cmath>

float gLimitUVRange;

RndGroup* GroupOwner(Hmx::Object* o) {
    for(std::vector<ObjRef*>::const_reverse_iterator rit = o->Refs().rbegin(); rit != o->Refs().rend(); rit++){
        RndGroup* grp = dynamic_cast<RndGroup*>((*rit)->RefOwner());
        if(grp){
            for(ObjPtrList<Hmx::Object, class ObjectDir>::iterator pit = grp->mObjects.begin(); pit != grp->mObjects.end(); ++pit){
                if(*pit == o) return grp;
            }
        }
    }
    return 0;
}

static DataNode OnGroupOwner(DataArray* da) {
    return DataNode(GroupOwner(da->GetObj(1)));
}

RndEnviron* FindEnviron(RndDrawable*) {

}

void CalcBox(RndMesh* m, Box& b) {
    m->mOwner->mOwner;
    m->mOwner->mOwner;
    m->mOwner->mOwner;
}

void UtilDrawString(const char* c, const Vector3& v, const Hmx::Color& col) {
    Vector2 v2;
    if (RndCam::sCurrent->WorldToScreen(v, v2) > 0) {
        v2.x *= (float)TheRnd->mWidth;
        v2.y *= (float)TheRnd->mHeight;
        TheRnd->DrawString(c, v2, col, true);
    }
}

void SortXfms(RndMultiMesh*, const Vector3&) {
    MILO_ASSERT(0, 3150);
}

void RandomXfms(RndMultiMesh*) {
    MILO_ASSERT(0, 3173);
}

void MoveXfms(RndMultiMesh* mm, const Vector3& v) {
    for (std::list<RndMultiMesh::Instance>::iterator i = mm->mInstances.begin(); i != mm->mInstances.end(); i++) {
        i->mXfm.v += v;
    }

}

const char* CacheResource(const char*, Hmx::Object*);

Loader* ResourceFactory(const FilePath& f, LoaderPos p) {
    return new FileLoader(f, CacheResource(f.c_str(), NULL), p, 0, false, true, NULL);
}


DataNode DataFindEnviron(DataArray* da) {
    return DataNode(FindEnviron(da->Obj<RndDrawable>(1)));
}

void RndUtlPreInit() {
    SystemConfig("rnd")->FindData("limit_uv_range", gLimitUVRange, true);
    TheLoadMgr.RegisterFactory("bmp", ResourceFactory);
    TheLoadMgr.RegisterFactory("png", ResourceFactory);
    TheLoadMgr.RegisterFactory("xbv", ResourceFactory);
    TheLoadMgr.RegisterFactory("jpg", ResourceFactory);
    TheLoadMgr.RegisterFactory("tif", ResourceFactory);
    TheLoadMgr.RegisterFactory("tiff", ResourceFactory);
    TheLoadMgr.RegisterFactory("psd", ResourceFactory);
    TheLoadMgr.RegisterFactory("gif", ResourceFactory);
    TheLoadMgr.RegisterFactory("tga", ResourceFactory);
    DataRegisterFunc("find_environ", DataFindEnviron);
    DataRegisterFunc("group_owner", OnGroupOwner);
}

float ConvertFov(float a, float b) {
    float x = tan(0.5f * a);
    return atan(b * x) * 2;
}

void PreMultiplyAlpha(Hmx::Color& c) {
    c.red *= c.alpha;
    c.green *= c.alpha;
    c.blue *= c.alpha;
}

void RndScaleObject(Hmx::Object* o, float f1, float f2){
    
}