package com.copgem.domain;


import java.time.LocalDateTime;

public class OHLC {
    public final LocalDateTime date;
    public final double open;
    public final double low;
    public final double high;
    public final double close;
    public final double volume;

    public OHLC(LocalDateTime date, double open, double high, double low, double close, double volume) {
        this.date = date;
        this.open = open;
        this.high = high;
        this.low = low;
        this.close = close;
        this.volume = volume;
    }

    public OHLC(int year, int month, int day, int hour, int minute, int second, double open, double high, double low, double close, double volume) {
        this(LocalDateTime.of(year, month, day, hour, minute, second), open, high, low, close, volume);
    }

    public double getOpen() {
        return open;
    }

    public double getLow() {
        return low;
    }

    public double getHigh() {
        return high;
    }

    public double getClose() {
        return close;
    }

    public double getVolume() {
        return volume;
    }

    public int getYear() {
        return date.getYear();
    }

    public int getMonth() {
        return date.getMonthValue();
    }

    public int getDay() {
        return date.getDayOfMonth();
    }
    public int getHour() {
        return date.getHour();
    }

    public int getMinute() {
        return date.getMinute();
    }

    public int getSecond() {
        return date.getSecond();
    }

    public LocalDateTime getDateTime() {
        return date;
    }
}
