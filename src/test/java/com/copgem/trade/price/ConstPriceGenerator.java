package com.copgem.trade.price;


import java.util.List;
import java.util.function.Function;

import com.copgem.domain.OHLC;

public class ConstPriceGenerator  implements Function<OHLC, List<Double>>{
    

    @Override
    public List<Double> apply(OHLC t) {
       return List.of(t.close);

    }
    
}
