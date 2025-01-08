package com.copgem.indicator;

import java.util.Optional;
import java.util.function.Function;

import com.copgem.domain.OHLC;
import com.copgem.domain.Signal;

public abstract class Indicator implements Function<OHLC, Optional<Signal>> {
    public abstract Optional<Signal> apply(OHLC olhcv);
}
