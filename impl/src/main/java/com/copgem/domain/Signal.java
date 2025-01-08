package com.copgem.domain;

import java.time.LocalDateTime;

public class Signal {
    public final LocalDateTime entryDate;
    public final double entryPrice;
    public final double entryPriceStDev;
    public final int quantity;
    public final boolean buy; // true for buy, false for sell
    public final double takeProfit;
    public final double stopLoss;

    public Signal(LocalDateTime entryDate, double entryPrice, double entryPriceStDev, int quantity, boolean buy, double takeProfit, double stopLoss) {
        this.entryDate = entryDate;
        this.entryPrice = entryPrice;
        this.entryPriceStDev = entryPriceStDev;
        this.quantity = quantity;
        this.buy = buy;
        this.takeProfit = takeProfit;
        this.stopLoss = stopLoss;
    }

    public Signal(int year, int month, int day, int hour, int minute, int second, double entryPrice, double entryPriceStDev, int quantity, boolean buy, double takeProfit, double stopLoss ) {
        this.entryDate = LocalDateTime.of(year, month, day, hour, minute, second);
        this.entryPrice = entryPrice;
        this.entryPriceStDev = entryPriceStDev;
        this.quantity = quantity;
        this.buy = buy;
        this.takeProfit = takeProfit;
        this.stopLoss = stopLoss;

    }

    public int getYear() {
        return entryDate.getYear();
    }

    public int getMonth() {
        return entryDate.getMonthValue();
    }

    public int getDay() {
        return entryDate.getDayOfMonth();
    }

    public int getHour() {
        return entryDate.getHour();
    }

    public int getMinute() {
        return entryDate.getMinute();
    }

    public int getSecond() {
        return entryDate.getSecond();
    }

    public double getEntryPrice() {
        return entryPrice;
    }

    public int getQuantity() {
        return quantity;
    }

    public boolean isBuy() {
        return buy;
    }

    public double getTakeProfit() {
        return takeProfit;
    }

    public double getStopLoss() {
        return stopLoss;
    }

    public double getEntryPriceStDev() {
        return entryPriceStDev;
    }

    public LocalDateTime getEntryDate() {
        return entryDate;
    }
}