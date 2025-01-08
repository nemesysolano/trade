package com.copgem.simulator;

import java.util.List;

import com.copgem.domain.Transaction;

public class TradingSimulationResults {
    List<Transaction> transactions;

    public TradingSimulationResults(List<Transaction> transactions) {
        this.transactions = transactions;
    }
    
    public List<Transaction> getTransactions() {
        return transactions;
    }
}
