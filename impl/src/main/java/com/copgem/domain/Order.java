package com.copgem.domain;

import java.time.LocalDateTime;

public class Order {
    LocalDateTime entryDate;
    double limitPrice;
    int quantity;
    boolean buy; // When true is a Buy Limit order, otherwise is a Sell Limit order
    double takeProfit;
    double stopLoss;

    public Order(LocalDateTime entryDate, double limitPrice, int quantity, boolean buy, double takeProfit, double stopLoss) {
        this.entryDate =entryDate;
        this.limitPrice = limitPrice;
        this.quantity = quantity;
        this.buy = buy;
        this.takeProfit = takeProfit;
        this.stopLoss = stopLoss;
    }

    public LocalDateTime getEntryDate() {
        return entryDate;
    }

    public double getLimitPrice() {
        return limitPrice;
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

    public double profitLoss(double price) {
        if (buy) {
            return (price - limitPrice) * quantity;
        } else {
            return (limitPrice - price) * quantity;
        }
    }
    
}
