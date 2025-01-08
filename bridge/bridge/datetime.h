#pragma once
#ifndef BRIDGE_DATETIME_H
#define BRIDGE_DATETIME_H
#include <memory>
#include "jni-interface.h"

namespace bridge {
	typedef struct tm DateTime;

	typedef struct JvmDateTime {
		JNIEnv* env = nullptr;
		jobject obj = nullptr;
		// Foundation Constructors
		JvmDateTime(const std::unique_ptr<bridge::JVMInterface> & jvm_interface, DateTime & local_datetime);
		JvmDateTime(const std::unique_ptr<bridge::JVMInterface> & jvm_interface, DateTime&& local_datetime): JvmDateTime(jvm_interface, local_datetime) {};
		
		// Copy Constructor and assign copy operator
		JvmDateTime(const JvmDateTime&);
		JvmDateTime& operator=(const JvmDateTime&);
		void copy(const JvmDateTime& source);

		// Move constructor and assign move operator
		JvmDateTime(JvmDateTime &&);
		JvmDateTime& operator=(JvmDateTime &&);
		void move(JvmDateTime& source);


		inline bool is_initialized() const { return obj != nullptr; }

		int getYear() const;
		int getMonth() const;
		int getDay() const;
		int getHour() const;
		int getMinute() const;
		int getSecond() const;
		virtual ~JvmDateTime();
	} JVM_DATETIME;
}

#endif