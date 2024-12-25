package com.copgem.domain;

import java.time.LocalDateTime;

public class Order {
    public final LocalDateTime entryDate;
    public final double entryPrice;
    public final int quantity;
    public final boolean buy; // true for buy, false for sell
    public final double takeProfit;
    public final double stopLoss;

    public Order(LocalDateTime entryDate, double entryPrice, int quantity, boolean buy, double takeProfit, double stopLoss) {
        this.entryDate = entryDate;
        this.entryPrice = entryPrice;
        this.quantity = quantity;
        this.buy = buy;
        this.takeProfit = takeProfit;
        this.stopLoss = stopLoss;
    }
}