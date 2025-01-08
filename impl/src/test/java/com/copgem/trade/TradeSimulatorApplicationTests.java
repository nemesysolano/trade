package com.copgem.trade;


import java.io.*;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;

import com.copgem.domain.OHLC;
import com.copgem.domain.OHLCFactory;
import com.copgem.domain.Transaction;
import com.copgem.indicator.RandomIndicator;
import com.copgem.indicator.TrendingIndicator;
import com.copgem.simulator.TradingSimulationResults;
import com.copgem.simulator.TradingSimulator;

import org.junit.jupiter.api.Test;

class TradeSimulatorApplicationTests {
	private static Logger log = Logger.getLogger(TradeSimulatorApplicationTests.class.getName());

	@Test
	void genericOrderGeneratorTest() throws FileNotFoundException {
		List<OHLC> olhcList = OHLCFactory.fromPepperStone(new FileInputStream(new File("src\\test\\resources\\pepperstone\\EURUSD_H1_202101040000_202412202300.csv")));
		TradingSimulator simulator = new TradingSimulator();
		TradingSimulationResults results = simulator.execute(olhcList, new TrendingIndicator(24, 16));

		List<Transaction> transactions = results.getTransactions();
		long buyWinners = transactions.stream().filter(t -> t.isBuy() && t.isWinner()).count();
		long sellWinners = transactions.stream().filter(t -> !t.isBuy() && t.isWinner()).count();
		long buyLosers = transactions.stream().filter(t -> t.isBuy() && !t.isWinner()).count();
		long sellLosers = transactions.stream().filter(t -> !t.isBuy() && !t.isWinner()).count();
		long totalWinners = buyWinners + sellWinners;
		long totalLosers = buyLosers + sellLosers;
		double profitLoss = transactions.stream().mapToDouble(t -> t.profit()).sum();
		log.info(String.format("Total transactions: %d, Buy winners: %d, Sell winners: %d, Buy losers: %d, Sell losers: %d", transactions.size(), buyWinners, sellWinners, buyLosers, sellLosers));
		log.info(String.format("Total winners: %d, Total losers: %d", totalWinners, totalLosers));
		log.info(String.format("Profit/Loss: %.2f", profitLoss));
	}
}
