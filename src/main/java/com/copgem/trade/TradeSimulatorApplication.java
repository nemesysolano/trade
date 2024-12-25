package com.copgem.trade;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.autoconfigure.jdbc.DataSourceAutoConfiguration;

@SpringBootApplication(exclude = {DataSourceAutoConfiguration.class})
public class TradeSimulatorApplication {

	public static void main(String[] args) {
		SpringApplication.run(TradeSimulatorApplication.class, args);
	}

}
