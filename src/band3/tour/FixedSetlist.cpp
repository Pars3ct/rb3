#include "FixedSetlist.h"
#include "os/Debug.h"
#include "system/utl/Symbols.h"
#include <vector>
// #include "band3/meta_band/AccomplishmentManager.h"

FixedSetlist::FixedSetlist() : mWeight(1), m_pSongEntries(NULL), mName("") {
}

FixedSetlist::~FixedSetlist() {
    
}

void FixedSetlist::Init(const DataArray *i_pConfig) {
    MILO_ASSERT(i_pConfig, 0x1e);

    mName = i_pConfig->Sym(0);

    i_pConfig->FindData(group, mGroup, true);
    i_pConfig->FindData(weight, mWeight, false);
    DataArray* pSongsArray = i_pConfig->FindArray(songs, true);

    MILO_ASSERT(pSongsArray, 0x2A);
    MILO_ASSERT(pSongsArray->Size() > 1, 0x2B);

    m_pSongEntries = pSongsArray;
}

Symbol FixedSetlist::GetName() const {
    return mName;
}

Symbol FixedSetlist::GetGroup() const {
    return mGroup;
}

float FixedSetlist::GetWeight() const {
    return mWeight;
}

Symbol FixedSetlist::GetSongName(int i_iIndex) {
    MILO_ASSERT(i_iIndex < GetNumSongs(), 0x44);

    DataArray* result;
    std::vector<Symbol> songs;

    InqSongs(songs);

    return songs[i_iIndex];
}

int FixedSetlist::GetNumSongs() const {
    MILO_ASSERT(m_pSongEntries, 0x4F);

    return m_pSongEntries->Size() - 1;
}

void FixedSetlist::InqSongs(std::vector<Symbol>& o_rSongs) const {
    MILO_ASSERT(o_rSongs.empty(), 0x56);

    for (int i = 0; i < m_pSongEntries->Size(); i++) {
        Symbol var1 = gNullStr;
        DataNode node = m_pSongEntries->Node(i);

        if (mWeight) {

        } else if (mWeight) {
            DataArray* pArray = node.Array(0);
            MILO_ASSERT(pArray->Size() == 1, 99);
            DataNode node2 = pArray->Node(0);
            int i2 = node2.Int(pArray);
            // TheAccomplishmentMgr.GetTourSafeDiscSongAtDifficultyIndex(i2);
        } else {
            MILO_ASSERT(false, 0x6b);
        }

        o_rSongs.push_back(var1);
    }
}