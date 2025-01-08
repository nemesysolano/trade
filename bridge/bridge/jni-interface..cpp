// bridge.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "jni-interface.h"
#include <string>
#include <iostream>
using namespace std;
using namespace bridge;

JVMInterface::JVMInterface(const std::string& class_path) {
    JavaVMInitArgs vm_args;
    JavaVMOption options[1];

    vm_args.version = JNI_VERSION_20;
    vm_args.nOptions = 1;
    vm_args.ignoreUnrecognized = JNI_TRUE; // remove unrecognized options
    vm_args.options = options;
    options[0].optionString = (char*)class_path.c_str();
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

bool JVMInterface::is_initialized() const {
	return env != nullptr;
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
