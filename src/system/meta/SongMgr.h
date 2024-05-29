#ifndef METABAND_SONGMGR_H
#define METABAND_SONGMGR_H

#include "system/utl/Symbol.h"
#include "system/utl/Loader.h"
#include "system/utl/BufStream.h"
#include "system/obj/Data.h"
#include "system/os/ContentMgr.h"
#include <vector>

enum SongMgrState {

};

void GetSongID(DataArray*, DataArray*);
void CountSongsInArray(DataArray*);

class SongMgr {
    virtual ~SongMgr();
    void Init();
    bool HasSong(int) const;
    bool HasSong(Symbol, bool) const;
    void Data(int) const;
    void ContentStarted();
    void ContentDiscovered(Symbol);
    void ContentLoaded(Loader*, ContentLocT, Symbol);
    bool AllowContentToBeAdded(DataArray*, ContentLocT);
    void ContentDone();
    void ContentMounted(const char*, const char*);
    virtual void ContentUnmounted(const char*);
    void ContentName(int) const;
    void SongAudioData(Symbol) const;
    const char* ContentName(Symbol, bool) const;
    void GetContentNames(Symbol, std::vector<Symbol>);
    bool SongCacheNeedsWrite() const;
    bool IsSongCacheWriteDone() const;
    bool IsSongMounted(Symbol) const;
    void ClearSongCacheNeedsWrite();
    void StartSongCacheWrite();
    void SaveCachedSongInfo(BufStream&);
    void LoadCachedSongInfo(BufStream&);
    void GetCachedSongInfoSize() const;
    void GetCachedSongInfoName() const;
    void ClearCachedContent();
    void ClearFromCache(Symbol);
    void SetState(enum SongMgrState);
    //void CacheSongData(DataArray*, DataLoader*, ContentLocT, Symbol)
    void SaveMount();
    void SaveWrite();
    void SaveUnmount();
    void OnCacheMountResult(int);
    void OnCacheWriteResult(int);
    void OnCacheUnmountResult(int);
    void GetSongsInContent(Symbol, std::vector<int>&) const;
    void NumSongsInContent(int) const;
    void DumpSongMgrContents(bool);
    void Handle(DataArray*, bool);
    void AllowCacheWrite(bool);
    void Terminate();

    int mPadding1[19];

    int unk_50;

    int mPadding2[24];

    int unk_b4;                     // 0xb4
    int unk_b8;                     // 0xb8
    bool unk_bc;                    // 0xbc
    bool mClearSongCacheNeedsWrite; // 0xbd
    bool mAllowCacheWrite;          // 0xbe
};

#endif // METABAND_SONGMGR_H