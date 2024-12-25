package com.copgem.trade.order.generator;

import java.util.List;

import com.copgem.domain.OHLC;
import com.copgem.domain.Order;
import com.copgem.order.OrderGenerator;

import lombok.extern.slf4j.Slf4j;

// https://www.mtsocketapi.com/doc5/introduction.html
@Slf4j
public abstract class LookbackOrderGenerator extends OrderGenerator {
    public final static int MIN_LOOKBACK_SIZE = 8;
    protected OHLC[] lookback;
    protected int lookbackSize = 0;
    protected int lookbackIndex = 0;

    public LookbackOrderGenerator(int lookbackSize) {
        
        this.lookbackSize = lookbackSize;
        this.lookback = new OHLC[lookbackSize];
        this.lookbackIndex = lookbackSize - 1;
        this.reset();
    }

    void updateLookback(OHLC olhcv) {
        for (int i = 0; i < lookbackIndex; i++) {
            lookback[i] = lookback[i + 1];
        }
        lookback[lookbackIndex] = olhcv;
    }
    

    @Override
    public List<Order> apply(OHLC olhcv) {
        updateLookback(olhcv);
        if(lookback[0] == null) {
            return List.of();
        }   

        List<Order> orders = createOrders(olhcv);
        ordersPlaced += orders.size();
        return orders;
    }

    protected abstract List<Order> createOrders(OHLC olhcv);

}
