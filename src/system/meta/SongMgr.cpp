#include "SongMgr.h"
#include "system/os/ContentMgr.h"
#include "system/utl/CacheMgr.h"

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

// SongMgr::~SongMgr() {}
// void SongMgr::Init() {}
// void SongMgr::HasSong(int) const {}
// void SongMgr::HasSong(Symbol, bool) const {}
// void SongMgr::Data(int) const {}
// void SongMgr::ContentStarted() {}
// void SongMgr::ContentDiscovered(Symbol) {}
// void SongMgr::ContentDone() {}
// void SongMgr::ContentMounted(const char*, const char*) {}
// void SongMgr::ContentUnmounted(const char*) {}
// void SongMgr::ContentName(int) const {}
// void SongMgr::SongAudioData(Symbol) const {}
// void SongMgr::ContentName(Symbol, bool) const {}
// void SongMgr::GetContentNames(Symbol, std::vector<Symbol>) {}
// void SongMgr::SongCacheNeedsWrite() const {}
// void SongMgr::IsSongCacheWriteDone() const {}
// void SongMgr::IsSongMounted(Symbol) const {}
