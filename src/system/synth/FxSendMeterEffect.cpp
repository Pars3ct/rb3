#include "synth/FxSendMeterEffect.h"
#include "utl/Symbols.h"
#include "obj/PropSync_p.h"

unsigned short FxSendMeterEffect::gRev = 0;
unsigned short FxSendMeterEffect::gAltRev = 0;

FxSendMeterEffect::FxSendMeterEffect() : mResetPeaks(0) {
    
}

SAVE_OBJ(FxSendMeterEffect, 0x15);

void FxSendMeterEffect::Load(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(1, 0);
    FxSend::Load(bs);
    OnParametersChanged();
}

BEGIN_COPYS(FxSendMeterEffect)
    COPY_SUPERCLASS(FxSend)
    GET_COPY(FxSendMeterEffect)
END_COPYS

float FxSendMeterEffect::ChannelData(int idx){
    if(mChannels.empty()) return 0.0f;
    int max = mChannels.size() - 1;
    if(max < idx)
        idx = max;
    return mChannels[idx];
}

BEGIN_HANDLERS(FxSendMeterEffect)
    HANDLE_EXPR(channel1, ChannelData(0))
    HANDLE_EXPR(channel2, ChannelData(1))
    HANDLE_SUPERCLASS(FxSend)
    HANDLE_CHECK(0x39)
END_HANDLERS

BEGIN_PROPSYNCS(FxSendMeterEffect)
    SYNC_PROP_ACTION(reset_peaks, mResetPeaks, kPropSize|kPropGet, OnParametersChanged())
    SYNC_SUPERCLASS(FxSend)
END_PROPSYNCS