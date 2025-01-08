package com.copgem.indicator;

import java.util.Optional;

import com.copgem.domain.OHLC;
import com.copgem.domain.Signal;


// https://www.mtsocketapi.com/doc5/introduction.html

public abstract class LookbackIndicator extends Indicator {
    public final static int MIN_LOOKBACK_SIZE = 60;
    protected OHLC[] lookback;
    protected int lookbackSize = 0;
    protected int lookbackIndex = 0;

    public LookbackIndicator(int lookbackSize) {
        this.lookbackSize = Math.min(MIN_LOOKBACK_SIZE, lookbackSize);
        this.lookback = new OHLC[lookbackSize];
        this.lookbackIndex = lookbackSize - 1;
    }

    void updateLookback(OHLC olhcv) {
        for (int i = 0; i < lookbackIndex; i++) {
            lookback[i] = lookback[i + 1];
        }
        lookback[lookbackIndex] = olhcv;
    }
    

    @Override
    public Optional<Signal> apply(OHLC olhcv) {
        updateLookback(olhcv);
        if(lookback[0] == null) {
            return Optional.empty();
        }   

        return createSignal(olhcv);
    }

    protected abstract Optional<Signal> createSignal(OHLC olhcv);

}
