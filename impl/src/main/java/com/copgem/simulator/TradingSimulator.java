package com.copgem.simulator;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;
import java.util.concurrent.ThreadLocalRandom;

import com.copgem.domain.OHLC;
import com.copgem.domain.Order;
import com.copgem.domain.Signal;
import com.copgem.domain.Transaction;
import com.copgem.indicator.Indicator;

public class TradingSimulator {
  public TradingSimulationResults execute(List<OHLC> ohlcList, Indicator indicator) {
    ArrayList<Order> placedOrders = new ArrayList<>(); // New limit orders whose limit prices have not been met 
    ArrayList<Order> pendingOrders = new ArrayList<>(); // Limit orders whose limit prices have been met
    ArrayList<Order> closedOrders = new ArrayList<>(); // Orders that have been closed
    ArrayList<Transaction> transactions = new ArrayList<>();


    for (OHLC ohlc : ohlcList) {
        // Close pending orders
        for (Order order : pendingOrders) {
            if (order.isBuy() && ohlc.getHigh() >= order.getTakeProfit()) {
                transactions.add(new Transaction(order, ohlc.getDateTime(), order.getTakeProfit()));
                closedOrders.add(order);
            } else if (order.isBuy() && ohlc.getLow() <= order.getStopLoss()) {
                transactions.add(new Transaction(order, ohlc.getDateTime(), order.getStopLoss()));
                closedOrders.add(order);
            } else if (!order.isBuy() && ohlc.getLow() <= order.getTakeProfit()) {
                transactions.add(new Transaction(order, ohlc.getDateTime(), order.getTakeProfit()));
                closedOrders.add(order);
            } else if (!order.isBuy() && ohlc.getHigh() >= order.getStopLoss()) {
                transactions.add(new Transaction(order, ohlc.getDateTime(), order.getStopLoss()));
                closedOrders.add(order);
            }
        }
        pendingOrders.removeAll(closedOrders);

        if(pendingOrders.size()  == 0) {
            // Fulfill placed orders when limit price is met
            for (Order order : placedOrders) {
                if (order.isBuy() && ohlc.getLow() <= order.getLimitPrice()) {
                    pendingOrders.add(order);
                } else if (!order.isBuy() && ohlc.getHigh() >= order.getLimitPrice()) {
                    pendingOrders.add(order);
                }
            }
            placedOrders.removeAll(pendingOrders);

            if(pendingOrders.size()  == 0) {
                Optional<Signal> optional = indicator.apply(ohlc);
                if(optional.isPresent()) {
                    Signal signal = optional.get();
                    placedOrders.add(new Order(ohlc.getDateTime(), signal.getEntryPrice(), signal.getQuantity(), signal.isBuy(), signal.getTakeProfit(), signal.getStopLoss()   ));
                }
            }

        }
    }

    return new TradingSimulationResults(transactions);
  }

  double randomPrice(double lower, double upperExclusive) {
    return ThreadLocalRandom.current().nextDouble(0, 1) * (upperExclusive - lower) + lower;
  }

}
