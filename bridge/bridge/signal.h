#pragma once
#ifndef BRIDGE_ORDER_H
#define BRIDGE_ORDER_H
#include <memory>
#include "jni-interface.h"
#include "datetime.h"
#include "ohlc.h"

namespace bridge {
	typedef struct Signal {
        DateTime entryDate;
        double entryPrice;
        double entryPriceStDev;
        int quantity;
        bool buy; // true for buy, false for sell
        double takeProfit;
        double stopLoss;
	} Signal;

	typedef struct JvmSignal {
		JNIEnv* env = nullptr;
		jobject obj = nullptr;
		bool jvmOwned = false;

		// Foundation Constructors
		JvmSignal(const std::unique_ptr<bridge::JVMInterface>& jvm_interface, jobject obj_); // Just a wrapper for signal returned from Java. Used only for local variables.
		JvmSignal(const std::unique_ptr<bridge::JVMInterface>& jvm_interface, const Signal& signal);// Used to create signals in C++ and pass them to Java. Safe as class/instance/global variable

        // Copy Constructor and assign copy operator
		JvmSignal(const JvmSignal& source);
		JvmSignal& operator=(const JvmSignal& source);
        void copy(const JvmSignal& source);

        // Move constructor and assign move operator
        JvmSignal(JvmSignal&& source);
		JvmSignal& operator=(JvmSignal&& source);
        void move(JvmSignal& source);

		bool is_initialized() const { return obj != nullptr; }
        int getYear() const;
        int getMonth() const;
        int getDay() const;
        int getHour() const;
        int getMinute() const;
        int getSecond() const;
		double getEntryPrice() const;
		double getEntryPriceStDev() const;
        int getQuantity() const;
        bool isBuy() const;
        double getTakeProfit() const;
        double getStopLoss() const;

        ~JvmSignal();
	};
}
#endif
