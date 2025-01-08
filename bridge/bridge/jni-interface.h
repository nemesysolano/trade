#pragma once
#ifndef BRIDGE_JNDI_INTERFACE_H
#include <string>
#include <jni.h>
namespace bridge {

	typedef struct JVMInterface {
		JavaVM* javaVM = nullptr;
		JNIEnv* env = nullptr;
		JVMInterface(const std::string& class_path);
		bool is_initialized() const;
		~JVMInterface();
	} JVM_INTERFACE, JVM_INTERFACE_PTR;
}
#endif