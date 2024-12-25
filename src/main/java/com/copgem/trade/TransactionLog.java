package com.copgem.trade;

import java.util.LinkedList;
import java.util.List;
import com.copgem.domain.Transaction;
public class TransactionLog {
    LinkedList<Transaction> transactions = new LinkedList<>();
    
    public void add(Transaction transaction) {
        transactions.add(transaction);
    }

    public List<Transaction> getTransactions() {
        return transactions.stream().toList();
    }

    public void clear() {
        transactions.clear();
    }

    public double totalWin() {
        return transactions.stream().mapToDouble(Transaction::profit).filter(p -> p > 0).sum();
    }

    public double totalLoss() {
        return transactions.stream().mapToDouble(Transaction::profit).filter(p -> p < 0).sum();
    }

    public long winners() {
        return transactions.stream().filter(t -> t.profit() > 0).count();
    }

    public long losers() {
        return transactions.stream().filter(t -> t.profit() < 0).count();
    }

    public long buyWinners() {
        return transactions.stream().filter(t -> t.buy && t.profit() > 0).count();
    }

    public long sellWinners() {
        return transactions.stream().filter(t -> !t.buy && t.profit() > 0).count();
    }

    public long buyLosers() {
        return transactions.stream().filter(t -> t.buy && t.profit() < 0).count();
    }

    public long sellLosers() {
        return transactions.stream().filter(t -> !t.buy && t.profit() < 0).count();
    }

    public double totalBuyProfit() {
        return transactions.stream().filter(t -> t.buy).mapToDouble(Transaction::profit).sum();
    }

    public double totalSellProfit() {
        return transactions.stream().filter(t -> !t.buy).mapToDouble(Transaction::profit).sum();
    }

    public double totalBuyLoss() {
        return transactions.stream().filter(t -> t.buy).mapToDouble(Transaction::profit).filter(p -> p < 0).sum();
    }

    public double totalSellLoss() {
        return transactions.stream().filter(t -> !t.buy).mapToDouble(Transaction::profit).filter(p -> p < 0).sum();
    }

    public double maxLoss() {
        return transactions.stream().mapToDouble(Transaction::profit).min().orElse(0);  
    }

    public double maxWin() {
        return transactions.stream().mapToDouble(Transaction::profit).max().orElse(0);  
    }

    public long size() {
        return transactions.size();
    }

}
