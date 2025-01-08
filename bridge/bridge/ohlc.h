#pragma once
#ifndef BRIDGE_OHLC_H
#define BRIDGE_OHLC_H
#include <memory>
#include "jni-interface.h"
#include "datetime.h"

namespace bridge {
	typedef struct OHLC {
		double open;
		double high;
		double low;
		double close;
		double volume;
		bridge::DateTime datetime;
	} OHLC;

	typedef struct JvmOHLC {
		JNIEnv* env = nullptr;
		jobject obj = nullptr;

		// Foundation Constructors
		JvmOHLC(const std::unique_ptr<bridge::JVMInterface>& jvm_interface, OHLC& ohlc);
		JvmOHLC(const std::unique_ptr<bridge::JVMInterface>& jvm_interface, OHLC&& ohlc) : JvmOHLC(jvm_interface, ohlc) {};

		// Copy Constructor and assign copy operator
		JvmOHLC(const JvmOHLC&);
		JvmOHLC& operator=(const JvmOHLC&);
		void copy(const JvmOHLC& source);

		// Move constructor and assign move operator
		JvmOHLC(JvmOHLC&& source);
		JvmOHLC& operator=(JvmOHLC&& source);
		void move(JvmOHLC& source);

		inline bool is_initialized() const { return obj != nullptr; }

		double getOpen() const;
		double getLow() const;
		double getHigh() const;
		double getClose() const;
		double getVolume() const;
		int getYear() const;
		int getMonth() const;
		int getDay() const;
		int getHour() const;
		int getMinute() const;
		int getSecond() const;

		~JvmOHLC();

	};
}
#endif

