#include "pch.h"
#include "datetime.h"
#include <iostream>
#include <string>
#include "jni-interface.h"

using namespace std;
using namespace bridge;
const char * JVM_LOCAL_DATE_TIME_CLASS = "java/time/LocalDateTime";
const char * JVM_LOCAL_DATE_TIME_FACTORY_SIGNATURE= "(IIIIII)Ljava/time/LocalDateTime;";
const char * JVM_LOCAL_DATE_TIME_FACTORY = "of";
/*
year - the year to represent, from MIN_YEAR to MAX_YEAR
month - the month-of-year to represent, from 1 (January) to 12 (December)
dayOfMonth - the day-of-month to represent, from 1 to 31
hour - the hour-of-day to represent, from 0 to 23
minute - the minute-of-hour to represent, from 0 to 59
second - the second-of-minute to represent, from 0 to 59
*/
JvmDateTime::JvmDateTime(const std::unique_ptr<bridge::JVMInterface>& jvm_interface, DateTime& local_datetime) {
	if (jvm_interface.get()->is_initialized()) {
		env = jvm_interface.get()->env;
		jclass cls = env->FindClass(JVM_LOCAL_DATE_TIME_CLASS);
		if (cls != nullptr) {
			jmethodID mid = env->GetStaticMethodID(cls, JVM_LOCAL_DATE_TIME_FACTORY, JVM_LOCAL_DATE_TIME_FACTORY_SIGNATURE);
			jobject obj = env->CallStaticObjectMethod (cls, mid, local_datetime.tm_year, local_datetime.tm_mon, local_datetime.tm_mday, local_datetime.tm_hour, local_datetime.tm_min, local_datetime.tm_sec);
				
			// Check for exceptions
			if (env->ExceptionCheck()) {
				env->ExceptionDescribe();
				env->ExceptionClear();
			} else {
				// create global reference
				this->obj = env->NewGlobalRef(obj);
				this->env = env;
			}
		}
	}
}

JvmDateTime::JvmDateTime(const JvmDateTime& source) {
	copy(source);
}

JvmDateTime& JvmDateTime::operator=(const JvmDateTime& source) {
	copy(source);
	return *this;
}

void JvmDateTime::copy(const JvmDateTime& source) {
	if (source.is_initialized()) {
		jclass clazz = source.env->GetObjectClass(source.obj); // check if object is valid (not null	
		jmethodID mid = source.env->GetStaticMethodID(clazz, JVM_LOCAL_DATE_TIME_FACTORY, JVM_LOCAL_DATE_TIME_FACTORY_SIGNATURE);
		jobject obj = source.env->CallStaticObjectMethod(
			clazz, 
			mid,
			source.getYear(),
			source.getMonth(),
			source.getDay(),
			source.getHour(),
			source.getMinute(),
			source.getSecond()
		);
		this->env = source.env;
		this->obj = env->NewGlobalRef(obj);
	}
}

JvmDateTime::JvmDateTime(JvmDateTime&& source) {
	move(source);
}


JvmDateTime& JvmDateTime::operator=(JvmDateTime&& source) {
	move(source);
	return *this;
}

void JvmDateTime::move(JvmDateTime& source) {
	if (source.is_initialized()) {
		this->env = source.env;
		this->obj = source.obj;
		source.env = nullptr;
		source.obj = nullptr;
	}
}


int JvmDateTime::getYear() const{
	if (is_initialized()) {
		jclass cls = env->GetObjectClass(obj);
		jmethodID mid = env->GetMethodID(cls, "getYear", "()I");
		if (mid != nullptr) {
			return env->CallIntMethod(obj, mid);
		}
	}
	return -1;
}

int JvmDateTime::getMonth() const{
	if (is_initialized()) {
		jclass cls = env->GetObjectClass(obj);
		jmethodID mid = env->GetMethodID(cls, "getMonthValue", "()I");
		if (mid != nullptr) {
			return env->CallIntMethod(obj, mid);
		}
	}
	return -1;
}

int JvmDateTime::getDay() const{
	if (is_initialized()) {
		jclass cls = env->GetObjectClass(obj);
		jmethodID mid = env->GetMethodID(cls, "getDayOfMonth", "()I");
		if (mid != nullptr) {
			return env->CallIntMethod(obj, mid);
		}
	}
	return -1;
}

int JvmDateTime::getHour() const{
	if (is_initialized()) {
		jclass cls = env->GetObjectClass(obj);
		jmethodID mid = env->GetMethodID(cls, "getHour", "()I");
		if (mid != nullptr) {
			return env->CallIntMethod(obj, mid);
		}
	}
	return -1;
}

int JvmDateTime::getMinute() const {
	if (is_initialized()) {
		jclass cls = env->GetObjectClass(obj);
		jmethodID mid = env->GetMethodID(cls, "getMinute", "()I");
		if (mid != nullptr) {
			return env->CallIntMethod(obj, mid);
		}
	}
	return -1;
}

int JvmDateTime::getSecond() const{
	if (is_initialized()) {
		jclass cls = env->GetObjectClass(obj);
		jmethodID mid = env->GetMethodID(cls, "getSecond", "()I");
		if (mid != nullptr) {
			return env->CallIntMethod(obj, mid);
		}
	}
	return -1;
}	

JvmDateTime::~JvmDateTime() {
	if (is_initialized()) {
		env->DeleteGlobalRef(obj);
		obj = nullptr;
		env = nullptr;
	}
}

