#include "pch.h"
#include "ohlc.h"
#include "datetime.h"
#include "jni-interface.h"
#include "memory"
#include <string>
#include <iostream>

using namespace bridge;
const char* JVM_OHLC_CLASS = "com/copgem/domain/OHLC";

JvmOHLC::JvmOHLC(const std::unique_ptr<JVMInterface>& jvm_interface, OHLC& ohlc) {
	if (jvm_interface.get()->is_initialized()) {
		env = jvm_interface.get()->env;
		jclass clazz = env->FindClass(JVM_OHLC_CLASS);
		if (clazz != nullptr) {
			jmethodID constructor = env->GetMethodID(clazz, "<init>", "(IIIIIIDDDDD)V");
			jobject obj = env->NewObject(
				clazz, 
				constructor,
				ohlc.datetime.tm_year, 
				ohlc.datetime.tm_mon, 
				ohlc.datetime.tm_mday, 
				ohlc.datetime.tm_hour, 
				ohlc.datetime.tm_min, 
				ohlc.datetime.tm_sec, 
				ohlc.open, 
				ohlc.high, 
				ohlc.low, 
				ohlc.close, 
				ohlc.volume
			);
		
			// Check for exceptions
			if (env->ExceptionCheck()) {
				env->ExceptionDescribe();
				env->ExceptionClear();
			}
			else {
				// create global reference
				this->obj = env->NewGlobalRef(obj);
				this->env = env;
			}
		}
	}
}

// Copy Constructor and assign copy operator
JvmOHLC::JvmOHLC(const JvmOHLC& source) {
	copy(source);
}

JvmOHLC& JvmOHLC::operator=(const JvmOHLC& source) {
	copy(source);
	return *this;
}

void JvmOHLC::copy(const JvmOHLC& source) {
	if (source.is_initialized()) {
		jclass clazz = source.env->GetObjectClass(source.obj); // check if object is valid (not null	
		jmethodID constructor = source.env->GetMethodID(clazz, "<init>", "(IIIIIIDDDDD)V");
		jobject obj = source.env->NewObject(
			clazz,
			constructor,
			source.getYear(),
			source.getMonth(),
			source.getDay(),
			source.getHour(),
			source.getMinute(),
			source.getSecond(),
			source.getOpen(),
			source.getHigh(),
			source.getLow(),
			source.getClose(),
			source.getVolume()
		);
		this->env = source.env;
		this->obj = env->NewGlobalRef(obj);
	}
}

// Move constructor and assign move operator
JvmOHLC::JvmOHLC(JvmOHLC&& source) {
	move(source);
}

JvmOHLC& JvmOHLC::operator=(JvmOHLC&& source) {
	move(source);
	return *this;
}

void JvmOHLC::move(JvmOHLC& source) {
	if (source.is_initialized()) {
		this->env = source.env;
		this->obj = source.obj;
		source.env = nullptr;
		source.obj = nullptr;
	}
}


double JvmOHLC::getOpen() const {
	if (is_initialized()) {
		jclass clazz = env->GetObjectClass(obj);
		jmethodID mid = env->GetMethodID(clazz, "getOpen", "()D");
		return env->CallDoubleMethod(obj, mid);
	}
	return NAN;
}

double JvmOHLC::getLow() const {
	if (is_initialized()) {
		jclass clazz = env->GetObjectClass(obj);
		jmethodID mid = env->GetMethodID(clazz, "getLow", "()D");
		return env->CallDoubleMethod(obj, mid);
	}
	return NAN;
}

double JvmOHLC::getHigh() const {
	if (is_initialized()) {
		jclass clazz = env->GetObjectClass(obj);
		jmethodID mid = env->GetMethodID(clazz, "getHigh", "()D");
		return env->CallDoubleMethod(obj, mid);
	}
	return NAN;
}

double JvmOHLC::getClose() const {
	if (is_initialized()) {
		jclass clazz = env->GetObjectClass(obj);
		jmethodID mid = env->GetMethodID(clazz, "getClose", "()D");
		return env->CallDoubleMethod(obj, mid);
	}
	return NAN;
}

double JvmOHLC::getVolume() const {
	if (is_initialized()) {
		jclass clazz = env->GetObjectClass(obj);
		jmethodID mid = env->GetMethodID(clazz, "getVolume", "()D");
		return env->CallDoubleMethod(obj, mid);
	}
	return NAN;
}

int JvmOHLC::getYear() const {
	if (is_initialized()) {
		jclass clazz = env->GetObjectClass(obj);
		jmethodID mid = env->GetMethodID(clazz, "getYear", "()I");
		if (mid != nullptr) {
			return env->CallIntMethod(obj, mid);
		}
	}
	return -1;
}

int JvmOHLC::getMonth() const {
	if (is_initialized()) {
		jclass clazz = env->GetObjectClass(obj);
		jmethodID mid = env->GetMethodID(clazz, "getMonth", "()I");
		if (mid != nullptr) {
			return env->CallIntMethod(obj, mid);
		}
	}
	return -1;
}

int JvmOHLC::getDay() const {
	if (is_initialized()) {
		jclass clazz = env->GetObjectClass(obj);
		jmethodID mid = env->GetMethodID(clazz, "getDay", "()I");
		if (mid != nullptr) {
			return env->CallIntMethod(obj, mid);
		}
	}
	return -1;
}

int JvmOHLC::getHour() const {
	if (is_initialized()) {
		jclass clazz = env->GetObjectClass(obj);
		jmethodID mid = env->GetMethodID(clazz, "getHour", "()I");
		if (mid != nullptr) {
			return env->CallIntMethod(obj, mid);
		}
	}
	return -1;
}

int JvmOHLC::getMinute() const {
	if (is_initialized()) {
		jclass clazz = env->GetObjectClass(obj);
		jmethodID mid = env->GetMethodID(clazz, "getMinute", "()I");
		if (mid != nullptr) {
			return env->CallIntMethod(obj, mid);
		}
	}
	return -1;
}

int JvmOHLC::getSecond() const {
	if (is_initialized()) {
		jclass clazz = env->GetObjectClass(obj);
		jmethodID mid = env->GetMethodID(clazz, "getSecond", "()I");
		if (mid != nullptr) {
			return env->CallIntMethod(obj, mid);
		}
	}
	return -1;
}

JvmOHLC::~JvmOHLC() {
	if (is_initialized()) {
		env->DeleteGlobalRef(obj);
		obj = nullptr;
		env = nullptr;
	}
}