package com.copgem.indicator;

import java.util.Optional;
import java.util.concurrent.ThreadLocalRandom;

import com.copgem.domain.OHLC;
import com.copgem.domain.Signal;

public class TrendingIndicator extends LookbackIndicator {
    int stdDevFactor;
    public TrendingIndicator(int lookbackSize, int stdDevFactor) {
        super(lookbackSize);
        this.stdDevFactor = stdDevFactor;
    }
    
    @Override
    protected Optional<Signal> createSignal(OHLC ohlc) {

        double maxHigh = lookback[0].high;
        double minLow = lookback[0].low;
        double averagePriceTrend = 0;
        double priceTrend = 0;
        double maxPriceTrend = 0;
        double maxVolumeTrend = 0;
        double volumeTrend = 0;
        double averageVolumeTrend = 0;
        int weightSum = 0;

        for (int i = 1; i < lookbackIndex; i++) {
            double weight = i;
            weightSum += weight;
            maxHigh = Math.max(maxHigh, lookback[i].high);
            minLow = Math.min(minLow, lookback[i].low);

            priceTrend = (
                (lookback[i].close - lookback[i - 1].close) + 
                (lookback[i].low - lookback[i - 1].low) +  
                (lookback[i].high - lookback[i - 1].high) + 
                (lookback[i].open - lookback[i - 1].open)
            );
            maxPriceTrend = Math.max(maxPriceTrend, priceTrend);
            averagePriceTrend += (weight * priceTrend);

            
            volumeTrend =  (lookback[i].volume - lookback[i - 1].volume);
            maxVolumeTrend = Math.max(maxVolumeTrend, volumeTrend);
            averageVolumeTrend += (weight * volumeTrend);
        }

        averagePriceTrend /= weightSum;
        averageVolumeTrend /= weightSum;

        double trendStrength = Math.min(1.0, Math.abs(averagePriceTrend/maxPriceTrend));   
        double volumeStrength = Math.min(1.0, Math.abs(averageVolumeTrend / maxVolumeTrend));
        double averageStrength = Math.min(1, trendStrength + volumeStrength);
        double signedAverageStrength = averagePriceTrend/maxPriceTrend + averageVolumeTrend / maxVolumeTrend;
        boolean buy =  ohlc.low - minLow > 0 && signedAverageStrength > 0;
        boolean sell = ohlc.high - maxHigh < 0 && signedAverageStrength < 0;

        if((buy || sell)) {
            double entryPriceStDev =  stdevOpen() * stdDevFactor;
            double entryPrice = buy ? minLow - entryPriceStDev :maxHigh + entryPriceStDev;
            int quantity = (int)(100 * (1 +  averageStrength ));
            double takeProfit = buy ? maxHigh :minLow;
            double stopLoss = buy ? minLow : maxHigh;
            return Optional.of(new Signal(ohlc.date, entryPrice, entryPriceStDev, quantity, buy, takeProfit , stopLoss ));
        }

        return Optional.empty();
    }

    public double stdevOpen() {
        double sum = 0;
        double mean;
        for(int i = 0; i < lookbackIndex; i++) {
            sum += (lookback[i].open + lookback[i].high + lookback[i].low + lookback[i].close)/4;
        }

        mean = sum / lookbackIndex;
        sum = 0;

        for(int i = 0; i < lookbackIndex-1; i++) {
            sum += Math.pow( (lookback[i].open + lookback[i].high + lookback[i].low + lookback[i].close)/4 - mean, 2);
        }

        return Math.sqrt(sum / (lookbackIndex-1));
    }
}
