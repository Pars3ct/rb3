#include "SongMgr.h"
#include "system/os/ContentMgr.h"

const char* unusedStrings[] = {
    "The song %s has an invalid songID, assigning temp id %d.\n" 
};

void GetSongID(DataArray*, DataArray*) {}
void CountSongsInArray(DataArray*) {}

const char* unusedStrings2[] = {
    "false", 
    "d",
    ".",
    "%s", 
    "%s_song", 
    "Content %s isn't cached!",
    "mContentUsedForSong.find(id) == mContentUsedForSong.end()"
};

SongMgr::~SongMgr() {}

void SongMgr::Init() {
    unk_50 = 0xffffffff;
    unk_b4 = 0;
    unk_b8 = 0;
    unk_bc = false;
    mClearSongCacheNeedsWrite = false;
    mAllowCacheWrite = true;
}

bool SongMgr::HasSong(int) const {}

bool SongMgr::HasSong(Symbol, bool) const {}

void SongMgr::Data(int) const {}
void SongMgr::ContentStarted() {}
void SongMgr::ContentDiscovered(Symbol) {}

void SongMgr::ContentDone() {
    if (unk_bc == 0) { return; }
    mClearSongCacheNeedsWrite = 1;
}

void SongMgr::ContentLoaded(Loader*, ContentLocT, Symbol) {

}

bool SongMgr::AllowContentToBeAdded(DataArray*, ContentLocT) {
    return true;
}

void SongMgr::ContentMounted(const char*, const char*) {}
void SongMgr::ContentUnmounted(const char*) {}
void SongMgr::ContentName(int) const {}
void SongMgr::SongAudioData(Symbol) const {}
const char* SongMgr::ContentName(Symbol, bool) const {}
void SongMgr::GetContentNames(Symbol, std::vector<Symbol>) {}

bool SongMgr::SongCacheNeedsWrite() const {
    bool needsWrite = false;

    if (mAllowCacheWrite != false && mClearSongCacheNeedsWrite != false) {
        needsWrite = true;
    }
    return needsWrite;
}

bool SongMgr::IsSongCacheWriteDone() const {
    if (unk_50 == 3) {
        return true;
    }
    if (unk_50 == 4) {
        return true;
    }
    return false;
}

bool SongMgr::IsSongMounted(Symbol param_2) const {
    const char* contentName = ContentName(param_2, 1);
    bool isMounted;
    if (contentName == NULL) {
        isMounted = true; 
    } else {
        Symbol uVar2 = Symbol(contentName);
        //TheContentMgr.
    }
    return isMounted;
}

void SongMgr::ClearSongCacheNeedsWrite() {
    mClearSongCacheNeedsWrite = false;
}

void SongMgr::StartSongCacheWrite() {}
void SongMgr::SaveCachedSongInfo(BufStream&) {}
void SongMgr::LoadCachedSongInfo(BufStream&) {}

void SongMgr::GetCachedSongInfoSize() const {}

void SongMgr::GetCachedSongInfoName() const {}

void SongMgr::ClearCachedContent() {}
void SongMgr::ClearFromCache(Symbol) {}

void SongMgr::SetState(SongMgrState) {}

void SongMgr::SaveMount() {
    Symbol uVar1;

    if (unk_b4 == 0) {
        uVar1 = Symbol();
        //unk_b4 = TheCacheMgr.GetCacheID(uVar1);
    }

    if (unk_b4 == 0) {
        SetState((SongMgrState)3);
    } else {
        // Something involving TheCacheMgr
        int iVar2;
        if (iVar2 == 0) {
            // TheCacheMgr.GetLastResult();
            int CVar3 = 0;
            if (CVar3 == 1) {
                SetState((SongMgrState)3);
            } else {
                TheDebug.Fail(MakeString("SongMgr: Error %d while mounting.\n", CVar3));
            }
        }
    }
}

const char* unusedStrings4[] = {
    "ret", 
    "SongMgr: Failed to save cached song info - write aborted.\n", 
    "SongMgr: Error %d while unmounting.\n", 
    "SongMgr: Failed to unmount NULL song info cache.\n", 
};

void SongMgr::SaveWrite() {}
void SongMgr::SaveUnmount() {}

void SongMgr::OnCacheMountResult(int i) {
    if (unk_50 != 0) {
        TheDebug << MakeString("SongMgr: Mount result error %d - aborting cache write.\n", unk_50);
    } else {
        if (i != 0) {
            TheDebug << MakeString("SongMgr: Mount result received in state %d.\n", i);
            SetState((SongMgrState)3);
        } else {
            SetState((SongMgrState)1);
        }
    }
}

const char* unusedStrings3[] = {
    "SongMgr: Write result received in state %d.\n", 
    "SongMgr: Write result error %d - cache write failed.\n", 
    "SongMgr: Unmount result received in state %d.\n", 
    "SongMgr: Unmount result error %d - aborting cache unmount.\n", 
    "--------------------\n", 
    "mAvailableSongs:\n", 
    " %d. ID: %d\n",  
    " skipped %d non-DLC songs\n", 
    " Total Count: %d\n", 
    "mUncachedSongMetadata:\n",
    " %d. ID: %d, "
    "Short Name: %s, Age: %d\n", 
    "mCachedSongMetadata:\n", 
    "mSongIDsInContent:\n", 
    " %d. Content: %s\n", 
    "  SongID: %d\n", 
    "mContentUsedForSong:\n", 
    " %d. ID: %d, Content: %s\n", 
    "%s(%d): %s unhandled msg: %s"
};

void SongMgr::OnCacheWriteResult(int) {}
void SongMgr::OnCacheUnmountResult(int) {}

void SongMgr::GetSongsInContent(Symbol, std::vector<int>&) const {}

void SongMgr::NumSongsInContent(int) const {}

void SongMgr::DumpSongMgrContents(bool) {}

void SongMgr::Handle(DataArray*, bool) {}

void SongMgr::AllowCacheWrite(bool allowCacheWrite) {
    mAllowCacheWrite = allowCacheWrite;
}

void SongMgr::Terminate() {}
