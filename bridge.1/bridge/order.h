#pragma once
#ifndef __ORDER_H__
#define __ORDER_H__
#include "datetime.h"
#include "bridge.h"

namespace bridge {
	typedef struct OHLC {
		DateTime date;
		double open;
		double high;
		double low;
		double close;
		int volume;

		inline OHLC(DateTime date, double open, double high, double low, double close, int volume) :
			date(date), open(open), high(high), low(low), close(close), volume(volume) { }

		inline OHLC(DateTime& date, double open, double high, double low, double close, int volume) :
			date(date), open(open), high(high), low(low), close(close), volume(volume) { }

	} OHLC;

	typedef struct JvmOrderGenerator {
		JNIEnv* env = nullptr;
		jobject obj = nullptr;
		jclass jcls = nullptr;
		jmethodID applyMethodId = nullptr;
		inline bool is_initialized() { return obj != nullptr; }
		JvmOrderGenerator(const std::unique_ptr<JVMInterface>& jvn_interface, const std::string& clazz);
		JvmOrderGenerator(JVMInterface& jvn_interface, const std::string& clazz);
		virtual std::unique_ptr<Order> apply(OHLC& olhcv) = 0;
		virtual ~JvmOrderGenerator();
	}ORDER_GENERATOR;

	typedef struct JvmRandomOrderGenerator : public JvmOrderGenerator {
		JvmRandomOrderGenerator(const std::unique_ptr<JVMInterface>& jvm_interface);
		JvmRandomOrderGenerator(JVMInterface& jvm_interface);
		virtual std::unique_ptr<Order> apply(OHLC& olhcv);
		virtual ~JvmRandomOrderGenerator();
	}RANDOM_ORDER_GENERATOR;
}

#endif