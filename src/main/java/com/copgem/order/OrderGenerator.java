package com.copgem.order;

import java.util.List;
import java.util.function.Function;

import com.copgem.domain.OHLC;
import com.copgem.domain.Order;

public abstract class OrderGenerator implements Function<OHLC, List<Order>> {
    protected int ordersPlaced = 0;
    public OrderGenerator() {
        reset();
    }

    protected void reset() {
        ordersPlaced = 0;
    }

    public abstract List<Order> apply(OHLC olhcv);

    public void onCloseOrder(Order order) {
        ordersPlaced --;
    }
}
