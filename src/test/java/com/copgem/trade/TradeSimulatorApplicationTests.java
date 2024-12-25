package com.copgem.trade;


import java.io.*;
import org.junit.jupiter.api.Test;
import org.springframework.boot.test.context.SpringBootTest;

import com.copgem.domain.OHLCFactory;
import com.copgem.trade.order.generator.TrendingOrderGenerator;
import com.copgem.trade.price.ConstPriceGenerator;

import lombok.extern.slf4j.Slf4j;

@SpringBootTest
@Slf4j
class TradeSimulatorApplicationTests {
	

	@Test
	void genericOrderGeneratorTest() throws FileNotFoundException {
		final var olhcList = OHLCFactory.fromForexSB(new FileInputStream(new File("src/test/resources/pepperstone/EURUSD_M1_202404221928_202412202354.csv")));
		TradingSimulator tradingSimulator = new TradingSimulator(olhcList.get(0).open);
		TransactionLog transactionLog = tradingSimulator.transactionLog;
		tradingSimulator.run(olhcList, new ConstPriceGenerator(), new TrendingOrderGenerator(8));	

		log.info("fromForexSBTest -> Total win= {}", transactionLog.totalWin());
		log.info("fromForexSBTest -> Max win= {}", transactionLog.maxWin());
		log.info("fromForexSBTest -> Winners = {}, buy = {}, sell = {}", transactionLog.winners(), transactionLog.buyWinners(), transactionLog.sellWinners());
		log.info("fromForexSBTest -> Total loss = {} ", transactionLog.totalLoss());
		log.info("fromForexSBTest -> Max loss= {}", transactionLog.maxLoss());
		log.info("fromForexSBTest -> Losers = {}, buy = {}, sell = {}", transactionLog.losers(), transactionLog.buyLosers(), transactionLog.sellLosers());
		log.info("fromForexSBTest -> Total profit = {}", transactionLog.totalWin() + transactionLog.totalLoss());
	}
}
