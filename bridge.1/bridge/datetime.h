#pragma once
#ifndef __DATETIME_H__
#define __DATETIME_H__
#include <memory>
#include <jni.h>	
#include <string>
#include <ctime>
#include <iostream>
#include <string>
#include "bridge.h"
namespace jvmtypes {

	typedef struct tm DateTime;

	typedef struct JvmDateTime {
		JNIEnv* env = nullptr;
		jobject obj = nullptr;


		inline bool is_initialized() { return obj != nullptr; }
		JvmDateTime(bridge::JVMInterface& jvm_interface, DateTime& local_datetime);
		JvmDateTime(const std::unique_ptr<bridge::JVMInterface>& jvm_interface, DateTime& local_datetime);
		int getYear();
		int getMonth();
		int getDay();
		int getHour();
		int getMinute();
		int getSecond();
		virtual ~JvmDateTime();
	} JVM_DATETIME;

}
#endif
