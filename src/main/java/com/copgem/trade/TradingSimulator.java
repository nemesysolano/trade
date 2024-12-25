package com.copgem.trade;
import java.time.LocalDateTime;
import java.util.*;
import java.util.function.Function;


import com.copgem.domain.OHLC;
import com.copgem.domain.Order;
import com.copgem.domain.Transaction;
import com.copgem.order.OrderGenerator;

public class TradingSimulator {
    List<Order> openOrders = new ArrayList<>();
    List<Order> executedOrders = new ArrayList<>();
    TransactionLog transactionLog = new TransactionLog();
      
    public TradingSimulator(double initialPrice) {
        reset(initialPrice);
    }

    public void placeOrder(Order order) {
        openOrders.add(order);
    }

    public void reset(double initialPrice) {
        openOrders.clear();
        executedOrders.clear();
        transactionLog.clear();
    }

    public void processOrders(LocalDateTime exitDate, double exitPrice, OrderGenerator orderGenerator) {
        List<Order> ordersToRemove = new ArrayList<>();

        for (Order order : openOrders) {
            boolean canRemoveOrder = 
                (order.buy && exitPrice >= order.takeProfit) ||
                (order.buy && exitPrice <= order.stopLoss) ||
                (!order.buy && exitPrice <= order.takeProfit) ||
                (!order.buy && exitPrice >= order.stopLoss);

            if(canRemoveOrder) {
                ordersToRemove.add(order);
            }

        }

        ordersToRemove.forEach(order -> {
            transactionLog.add(new Transaction(order, exitDate, exitPrice));
            orderGenerator.onCloseOrder(order);
            executedOrders.add(order);
            openOrders.remove(order);
        });
        
    }
  
    public void run(
        Iterable<OHLC> olhcvList, 
        Function<OHLC, List<Double>> priceGenerator,
        OrderGenerator orderGenerator
     ) {
        for (OHLC olhc : olhcvList) {
            
            priceGenerator.apply(olhc).forEach(price -> {
                processOrders(olhc.date, price, orderGenerator);
                orderGenerator.apply(olhc).forEach(this::placeOrder);
            });
        }
    }
}


