#ifndef UTL_CACHEMGR_H
#define UTL_CACHEMGR_H

#include "Cache.h"

class LocalUser;

void CacheMgrInit();
void CacheMgrTerminate();

class CacheMgr {
private:
    enum OpType {};

    class CacheIDStoreEntry {};

    std::vector<CacheMgr::CacheIDStoreEntry> mStoreEntries;
public:
    CacheMgr();
    virtual ~CacheMgr();
    void SearchAsync(const char*, CacheID**);
    void ShowUserSelectUIAsync(LocalUser*, unsigned long long, const char*, const char*, CacheID**);
    void CreateCacheIDFromDeviceID(unsigned int, const char*, const char*, CacheID**);
    void CreateCacheID(const char*, const char*, const char*, const char*, const char*, int, CacheID**);
    bool IsDone();
    void GetLastResult();
    void AddCacheID(CacheID*, Symbol);
    void RemoveCacheID(CacheID*);
    void GetCacheID(Symbol);
    void SetOp(CacheMgr::OpType);
    void GetOp();
    void SetLastResult();
};

static CacheMgr TheCacheMgr;

#endif // UTL_CACHEMGR_H