#ifndef UI_UICOLOR_H
#define UI_UICOLOR_H
#include "obj/Object.h"
#include "math/Color.h"

class UIColor : public Hmx::Object {
public:
    UIColor();
    virtual ~UIColor(){}
    OBJ_CLASSNAME(UIColor);
    OBJ_SET_TYPE(UIColor);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);

    static unsigned short gRev;
    static unsigned short gAltRev;
    Hmx::Color mColor;

    const Hmx::Color& GetColor() const;
    void SetColor(const Hmx::Color&);
};

#endif
