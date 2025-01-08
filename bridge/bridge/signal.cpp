#include "pch.h"
#include "signal.h"
#include <string>
#include <iostream>
#include <memory>


using namespace bridge;
using namespace std;

const char* JVM_SIGNAL_CLASS = "com/copgem/domain/Signal";

JvmSignal::JvmSignal(const std::unique_ptr<bridge::JVMInterface>& jvm_interface, jobject obj_) : 
	env(jvm_interface.get()->env), 
	obj(obj_), 
	jvmOwned(true) {
}

JvmSignal::JvmSignal(const std::unique_ptr<bridge::JVMInterface>& jvm_interface, const Signal& signal) {
	if (jvm_interface.get()->is_initialized()) {
		env = jvm_interface.get()->env;
		jclass clazz = env->FindClass(JVM_SIGNAL_CLASS);
		if (clazz != nullptr) {
			jmethodID constructor = env->GetMethodID(clazz, "<init>", "(IIIIIIDDIBDD)V");
			jobject obj = env->NewObject(
				clazz,
				constructor,
				signal.entryDate.tm_year,
				signal.entryDate.tm_mon,
				signal.entryDate.tm_mday,
				signal.entryDate.tm_hour,
				signal.entryDate.tm_min,
				signal.entryDate.tm_sec,
				signal.entryPrice,
				signal.entryPriceStDev,
				signal.quantity,
				signal.buy,
				signal.takeProfit,
				signal.stopLoss
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
JvmSignal::JvmSignal(const JvmSignal& source) {
	copy(source);
}

JvmSignal& JvmSignal::operator=(const JvmSignal& source) {
	copy(source);
	return *this;
}	

void JvmSignal::copy(const JvmSignal& source) {
	
	if (source.is_initialized()) {
		env = source.env;
		jclass clazz = source.env->GetObjectClass(source.obj); // check if object is valid (not null	
		jmethodID constructor = source.env->GetMethodID(clazz, "<init>", "(IIIIIIDDIBDD)V");
		jobject obj = source.env->NewObject(
			clazz,
			constructor,
			source.getYear(),
			source.getMonth(),
			source.getDay(),
			source.getHour(),
			source.getMinute(),
			source.getSecond(),
			source.getEntryPrice(),
			source.getEntryPriceStDev(),
			source.getQuantity(),
			source.isBuy(),
			source.getTakeProfit(),
			source.getStopLoss()
		);
	}
}



// Move constructor and assign move operator
JvmSignal::JvmSignal(JvmSignal&& source) {
	move(source);
}

JvmSignal& JvmSignal::operator=(JvmSignal&& source) {
	move(source);
	return *this;
}
void JvmSignal::move(JvmSignal& source) { 
	if (source.is_initialized()) { //
		if (!source.jvmOwned) { // if source.obj was created in C++ (not returned from Java), then we can just move the pointers
			env = source.env;
			obj = source.obj;
			source.env = nullptr;
			source.obj = nullptr;
		}
		else { // if source.obj was returned from Java, then we need to create a new object in C++ and copy the values
			copy(source);
		}
	}
}

JvmSignal::~JvmSignal() {
	if (!jvmOwned) {
		env->DeleteGlobalRef(obj);
	}
	obj = nullptr;
	env = nullptr;
}