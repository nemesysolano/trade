// bridge.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "bridge.h"
#include <jni.h>
#include <iostream>
using namespace bridge;
using namespace std;
std::string RANDOM_ORDER_GENERATOR_CLASS_NAME("com/copgem/order/generator/RandomOrderGenerator");

jmethodID getApplyMethodId(JNIEnv* env, jclass jcls) {
	return env->GetMethodID(jcls, "apply", "(Lcom/copgem/order/generator/OHLC;)Lcom/copgem/order/Order;");
}

JVMInterface::JVMInterface(const std::string& class_path){
    JavaVMInitArgs vm_args;
	JavaVMOption* options = new JavaVMOption[1];

    vm_args.version = JNI_VERSION_20;
    vm_args.nOptions = 1;
    vm_args.ignoreUnrecognized = JNI_TRUE; // remove unrecognized options
	vm_args.options = options;
	options[0].optionString = (char *) class_path.c_str();
    int ret = JNI_CreateJavaVM(&javaVM, (void**)&env, &vm_args);

    if (ret < 0) {
        env = nullptr;
        javaVM = nullptr;
#if _DEBUG
		cout << "JVMInterface::JVMInterface() failed to create JVM" << endl;
#endif // DEBUG
	}
	else {
#if _DEBUG 
		cout << "JVMInterface::JVMInterface() created JVM" << endl;
#endif // DEBUG
	}

}

JVMInterface::~JVMInterface() {

    if (javaVM != nullptr) {
       
        javaVM->DestroyJavaVM();
        javaVM = nullptr;
        env = nullptr;

#if _DEBUG 
        cout << "JVMInterface::~JVMInterface() destroyed JVM" << endl;
#endif // DEBUG

		
    }
}
