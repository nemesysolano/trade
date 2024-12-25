package com.copgem.trade.price;


import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ThreadLocalRandom;
import java.util.function.Function;

import com.copgem.domain.OHLC;

public class GaussianPriceGenerator implements Function<OHLC, List<Double>>{
    final int n;
    public GaussianPriceGenerator(int n) {
        this.n = n;
    }
    @Override
    public List<Double> apply(OHLC t) {
        
       // generate n prices normally distributed around average price
       final var average = (t.open + t.high + t.close + t.low) / 4;
       final var stdDev = Math.sqrt(Math.abs(t.high - t.low) / n);  
       final var prices = new ArrayList<Double>();
       var lastPrice = average;

       prices.add(t.open);


       for(int index = 0; index < n; index ++) {
            var currentPrice = ThreadLocalRandom.current().nextGaussian(lastPrice, stdDev);
            currentPrice = currentPrice < t.low ? t.low : currentPrice;
            currentPrice = currentPrice > t.high ? t.high : currentPrice;
            prices.add(currentPrice);
            lastPrice = currentPrice;
       }

       prices.add(t.high);
       prices.add(t.low);
       prices.add(t.close);

       return prices;

    }
    
}
