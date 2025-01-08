
#include "datetime.h"
using namespace bridge;
using namespace std;

/*
year - the year to represent, from MIN_YEAR to MAX_YEAR
month - the month-of-year to represent, from 1 (January) to 12 (December)
dayOfMonth - the day-of-month to represent, from 1 to 31
hour - the hour-of-day to represent, from 0 to 23
minute - the minute-of-hour to represent, from 0 to 59
second - the second-of-minute to represent, from 0 to 59
*/

JvmDateTime::JvmDateTime(JVMInterface& jvm_interface, DateTime& local_datetime) {
	if (jvm_interface.is_initialized()) {
		jclass clazz = jvm_interface.env->FindClass("java/time/LocalDateTime");
		if (clazz != nullptr) {
			jmethodID of = env->GetStaticMethodID(clazz, "of", "(IIIIII)Ljava/time/LocalDateTime");

			if (of != nullptr) {

				jobject obj = env->CallStaticObjectMethod(clazz, of, local_datetime.tm_year, local_datetime.tm_mon, local_datetime.tm_mday, local_datetime.tm_hour, local_datetime.tm_min, local_datetime.tm_sec);

				if (!env->ExceptionCheck()) {
					this->obj = env->NewGlobalRef(obj);
					env->DeleteLocalRef(obj);
				}
				else {
					env->ExceptionDescribe();
					env->ExceptionClear();
					this->obj = nullptr;
				}
			}

			jvm_interface.env->DeleteLocalRef(clazz);
		}
	}
}

int JvmDateTime::getYear() {
	if (obj != nullptr) {
		jclass clazz = env->GetObjectClass(obj);
		jmethodID getYear = env->GetMethodID(clazz, "getYear", "()I");
		if (getYear != nullptr) {
			return env->CallIntMethod(obj, getYear);
		}
	}
	return -1;
}

int JvmDateTime::getMonth() {
	if (obj != nullptr) {
		jclass clazz = env->GetObjectClass(obj);
		jmethodID getMonth = env->GetMethodID(clazz, "getMonth", "()I");
		if (getMonth != nullptr) {
			return env->CallIntMethod(obj, getMonth);
		}
	}
	return -1;
}

int JvmDateTime::getDay() {
	if (obj != nullptr) {
		jclass clazz = env->GetObjectClass(obj);
		jmethodID getHour = env->GetMethodID(clazz, "getHour", "()I");
		if (getHour != nullptr) {
			return env->CallIntMethod(obj, getHour);
		}
	}
	return -1;
}

int JvmDateTime::getMinute() {
	if (obj != nullptr) {
		jclass clazz = env->GetObjectClass(obj);
		jmethodID getMinute = env->GetMethodID(clazz, "getMinute", "()I");
		if (getMinute != nullptr) {
			return env->CallIntMethod(obj, getMinute);
		}
	}
	return -1;
}

int JvmDateTime::getHour() {
	if (obj != nullptr) {
		jclass clazz = env->GetObjectClass(obj);
		jmethodID getSecond = env->GetMethodID(clazz, "getSecond", "()I");
		if (getSecond != nullptr) {
			return env->CallIntMethod(obj, getSecond);
		}
	}
	return -1;
}

int JvmDateTime::getSecond() {
	if (obj != nullptr) {
		jclass clazz = env->GetObjectClass(obj);
		jmethodID getSecond = env->GetMethodID(clazz, "getSecond", "()I");
		if (getSecond != nullptr) {
			return env->CallIntMethod(obj, getSecond);
		}
	}
	return -1;
}

JvmDateTime::JvmDateTime(const std::unique_ptr<JVMInterface>& jvm_interface, DateTime& local_datetime) : JvmDateTime(*jvm_interface.get(), local_datetime) {
}

JvmDateTime::~JvmDateTime() {
	if (obj != nullptr) {
		env->DeleteGlobalRef(obj);
		obj = nullptr;
	}
}