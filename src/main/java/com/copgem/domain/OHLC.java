package com.copgem.domain;



import lombok.extern.slf4j.Slf4j;
import java.time.LocalDateTime;

@Slf4j
public class OHLC {
    public final LocalDateTime date;
    public final double open;
    public final double low;
    public final double high;
    public final double close;
    public final double volume;

    public OHLC(LocalDateTime date, double open, double low, double high, double close, double volume) {
        this.date = date;
        this.open = open;
        this.low = low;
        this.high = high;
        this.close = close;
        this.volume = volume;
    }

 
}
