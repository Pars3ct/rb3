#ifndef UTL_HXGUID_H
#define UTL_HXGUID_H

class HxGuid {
public:
    HxGuid();

    void Generate();
    void Clear();
    bool IsNull() const;
    bool operator==(const HxGuid&) const;
    bool operator<(const HxGuid&) const;

    int mData[4];
};

class UserGuid : public HxGuid {
public:
    UserGuid(){}
    UserGuid& operator=(const UserGuid& u){
        mData[0] = u.mData[0];
        mData[1] = u.mData[1];
        mData[2] = u.mData[2];
        mData[3] = u.mData[3];
    }
};

#endif
