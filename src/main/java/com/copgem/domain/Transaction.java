package com.copgem.domain;

import java.time.LocalDateTime;

public class Transaction {
    public final LocalDateTime entryDate;
    public final double entryPrice;
    public final int quantity;
    public final boolean buy; 
    public final double takeProfit;
    public final double stopLoss;
    public final LocalDateTime exitDate;
    public final double exitPrice;

    public Transaction(LocalDateTime entryDate, double entryPrice, int quantity, boolean buy, double takeProfit, double stopLoss, LocalDateTime exitDate, double exitPrice) {
        this.entryDate = entryDate;
        this.entryPrice = entryPrice;
        this.quantity = quantity;
        this.buy = buy;
        this.takeProfit = takeProfit;
        this.stopLoss = stopLoss;
        this.exitDate = exitDate;
        this.exitPrice = exitPrice;
    }

    public Transaction(Order order, LocalDateTime exitDate, double exitPrice) {
        this.entryDate = order.entryDate;
        this.entryPrice = order.entryPrice;
        this.quantity = order.quantity;
        this.buy = order.buy;
        this.takeProfit = order.takeProfit;
        this.stopLoss = order.stopLoss;
        this.exitDate = exitDate;
        this.exitPrice = exitPrice;
    }   

    public double profit() {
        return (buy ? (exitPrice - entryPrice) : (entryPrice - exitPrice)) * quantity;
    }

    public String toCSVString() {

        return String.format("%s, %s, %f, %f, %d, %s, %f, %f, %f", entryDate, exitDate, entryPrice, exitPrice, quantity, buy ? "BUY": "SELL", takeProfit, stopLoss, profit());
    } 
}
