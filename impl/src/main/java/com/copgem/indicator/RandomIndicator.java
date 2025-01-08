package com.copgem.indicator;

import com.copgem.domain.OHLC;
import com.copgem.domain.Signal;

import java.time.LocalDateTime;
import java.util.Optional;
import java.util.concurrent.ThreadLocalRandom;

public class RandomIndicator extends Indicator {

    @Override
    public Optional<Signal> apply(OHLC olhcv) {
        boolean buy =ThreadLocalRandom.current().nextInt(2, 100) % 2 == 0;
        return Optional.of(new Signal(
            LocalDateTime.now(),
            (olhcv.open + olhcv.close) / 2,
            Math.abs(olhcv.open - olhcv.close),
            ThreadLocalRandom.current().nextInt(10, 100),
            buy,
            buy ? olhcv.high : olhcv.low,
            buy ? olhcv.low: olhcv.high
        ));
    }

}
