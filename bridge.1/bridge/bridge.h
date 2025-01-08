#pragma once
#ifndef __BRIDGE_H__
#define __BRIDGE_H__
#include <memory>
#include <jni.h>	
#include <string>
#include <ctime>
#include <iostream>
#include <string>
#include "datetime.h"
#include "order.h"
namespace bridge {
	
	typedef struct JVMInterface{
		JavaVM* javaVM = nullptr;
		JNIEnv* env = nullptr;
		JVMInterface(const std::string & class_path);
		inline bool is_initialized() { return javaVM != nullptr; }
		~JVMInterface();
	} JVM_INTERFACE, JVM_INTERFACE_PTR;


	typedef struct Order {
		DateTime entryDate;
		double entryPrice;
		int quantity;
		bool buy; // true for buy, false for sell
		double takeProfit;
		double stopLoss;

		inline Order(DateTime entryDate, double entryPrice, int quantity, bool buy, double takeProfit, double stopLoss) :
			entryDate(entryDate), entryPrice(entryPrice), quantity(quantity), buy(buy), takeProfit(takeProfit), stopLoss(stopLoss) { }

		inline Order(DateTime & entryDate, double entryPrice, int quantity, bool buy, double takeProfit, double stopLoss) :
			entryDate(entryDate), entryPrice(entryPrice), quantity(quantity), buy(buy), takeProfit(takeProfit), stopLoss(stopLoss) { }

	} ORDER;


}

#endif
