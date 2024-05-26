#ifndef METABAND_ACCOMPLISHMENTSONGCONDITIONAL_H
#define METABAND_ACCOMPLISHMENTSONGCONDITIONAL_H

#include "AccomplishmentConditional.h"
#include "system/ui/UILabel.h"

class SongStatusMgr;

class AccomplishmentSongConditional : public AccomplishmentConditional {
    AccomplishmentSongConditional(DataArray*, int);
    virtual ~AccomplishmentSongConditional();
    void CheckStarsCondition(SongStatusMgr*, Symbol, const AccomplishmentCondition&) const;
    void CheckScoreCondition(SongStatusMgr*, Symbol, const AccomplishmentCondition&) const;
    void CheckAccuracyCondition(SongStatusMgr*, Symbol, const AccomplishmentCondition&) const;
    void CheckStreakCondition(SongStatusMgr*, Symbol, const AccomplishmentCondition&) const;
    void CheckHoposPercentCondition(SongStatusMgr*, Symbol, const AccomplishmentCondition&) const;
    void CheckSoloPercentCondition(SongStatusMgr*, Symbol, const AccomplishmentCondition&) const;
    void CheckAwesomesCondition(SongStatusMgr*, Symbol, const AccomplishmentCondition&) const;
    void CheckDoubleAwesomesCondition(SongStatusMgr*, Symbol, const AccomplishmentCondition&) const;
    void CheckTripleAwesomesCondition(SongStatusMgr*, Symbol, const AccomplishmentCondition&) const;
    void CheckHitBRECondition(SongStatusMgr*, Symbol, const AccomplishmentCondition&) const;
    void CheckAllDoubleAwesomesCondition(SongStatusMgr*, Symbol, const AccomplishmentCondition&) const;
    void CheckAllTripleAwesomesCondition(SongStatusMgr*, Symbol, const AccomplishmentCondition&) const;
    void CheckPerfectDrumRollsCondition(SongStatusMgr*, Symbol, const AccomplishmentCondition&) const;
    void CheckFullComboCondition(SongStatusMgr*, Symbol, const AccomplishmentCondition&) const;
    void CheckConditionsForSong(SongStatusMgr*, Symbol) const;
    void UpdateIncrementalEntryName(UILabel*, Symbol);
    void InqProgressValues(BandProfile*, int&, int&);
    void IsSymbolEntryFulfilled(BandProfile*, Symbol) const;
    void ShowBestAfterEarn() const;
    void InitializeTrackerDesc(TrackerDesc&) const;
};

#endif // METABAND_ACCOMPLISHMENTCONDITIONAL_H