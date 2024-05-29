#include "CacheMgr.h"

void CacheMgrInit() {}
void CacheMgrTerminate() {}

CacheMgr::CacheMgr() {}
CacheMgr::~CacheMgr() {}
void CacheMgr::SearchAsync(const char*, CacheID**) {}
void CacheMgr::ShowUserSelectUIAsync(LocalUser*, unsigned long long, const char*, const char*, CacheID**) {}
void CacheMgr::CreateCacheIDFromDeviceID(unsigned int, const char*, const char*, CacheID**) {}
void CacheMgr::CreateCacheID(const char*, const char*, const char*, const char*, const char*, int, CacheID**) {}
bool CacheMgr::IsDone() {}
void CacheMgr::GetLastResult() {}
void CacheMgr::AddCacheID(CacheID*, Symbol) {}
void CacheMgr::RemoveCacheID(CacheID*) {}
void CacheMgr::GetCacheID(Symbol) {}
void CacheMgr::SetOp(CacheMgr::OpType) {}
void CacheMgr::GetOp() {}
void CacheMgr::SetLastResult() {}
