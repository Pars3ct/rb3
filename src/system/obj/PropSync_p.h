#ifndef OBJ_PROPSYNC_H
#define OBJ_PROPSYNC_H
#include "math/Color.h"
#include "math/Sphere.h"
#include "math/Mtx.h"
#include "math/Vec.h"
#include "obj/Object.h"
#include "utl/FilePath.h"
#include "utl/Symbol.h"
#include "os/Debug.h"

bool PropSync(class String&, DataNode&, DataArray*, int, PropOp);
bool PropSync(FilePath&, DataNode&, DataArray*, int, PropOp);
bool PropSync(Hmx::Color&, DataNode&, DataArray*, int, PropOp);
bool PropSync(Hmx::Matrix3&, DataNode&, DataArray*, int, PropOp);
bool PropSync(class Sphere&, DataNode&, DataArray*, int, PropOp);
bool PropSync(Vector2&, DataNode&, DataArray*, int, PropOp);
bool PropSync(Vector3&, DataNode&, DataArray*, int, PropOp);
// bool PropSync(Transform&, DataNode&, DataArray*, int, PropOp);
// bool PropSync(Hmx::Rect&, DataNode&, DataArray*, int, PropOp);
// bool PropSync(Box&, DataNode&, DataArray*, int, PropOp);

inline bool PropSync(float& f, DataNode& node, DataArray* prop, int i, PropOp op){
    MILO_ASSERT(i == prop->Size() && op <= kPropInsert, 0x17);
    if(op == kPropGet) node = DataNode(f);
    else f = node.Float(0);
    return true;
}

inline bool PropSync(int& iref, DataNode& node, DataArray* prop, int i, PropOp op){
    MILO_ASSERT(i == prop->Size() && op <= kPropInsert, 0x2C);
    if(op == kPropGet) node = DataNode(iref);
    else iref = node.Int(0);
    return true;
}

inline bool PropSync(bool& b, DataNode& node, DataArray* prop, int i, PropOp op){
    MILO_ASSERT(i == prop->Size() && op <= kPropInsert, 0x40);
    if(op == kPropGet) node = DataNode(b);
    else b = node.Int(0) != 0;
    return true;
}

inline bool PropSync(Symbol& sym, DataNode& node, DataArray* prop, int i, PropOp op){
    MILO_ASSERT(i == prop->Size() && op <= kPropInsert, 0x4A);
    if(op == kPropGet) node = DataNode(sym);
    else sym = node.Str(0);
    return true;
}

#endif
