#include "order.h"	
using namespace bridge;
using namespace std;

JvmOrderGenerator::JvmOrderGenerator(JVMInterface& jvm_interface, const string& clazz) {
	if (jvm_interface.is_initialized()) {
		jcls = jvm_interface.env->FindClass(clazz.c_str());
		if (jcls != nullptr) {
			jcls = (jclass)jvm_interface.env->NewGlobalRef(jcls);
#ifdef _DEBUG	
			cout << "JvmOrderGenerator::JvmOrderGenerator() created jcls (" << clazz << ')' << endl;
#endif
		}
#ifdef _DEBUG
		else {
			cout << "JvmOrderGenerator::JvmOrderGenerator() failed to create jcls (" << clazz << ')' << endl;
		}
#endif		
		this->env = jvm_interface.env;
	}

}

JvmOrderGenerator::JvmOrderGenerator(const std::unique_ptr<JVMInterface>& jvm_interface, const std::string& clazz) :JvmOrderGenerator(*jvm_interface.get(), clazz) {
}

JvmOrderGenerator::~JvmOrderGenerator() {
	if (obj != nullptr) {
		env->DeleteGlobalRef(obj);
		obj = nullptr;
#ifdef _DEBUG
		cout << "JvmOrderGenerator::~JvmOrderGenerator() deleted obj" << endl;
#endif
	}
	if (jcls != nullptr) {
		env->DeleteGlobalRef(jcls);
		jcls = nullptr;
#ifdef _DEBUG
		cout << "JvmOrderGenerator::~JvmOrderGenerator() deleted jcls" << endl;
#endif
	}
}

JvmRandomOrderGenerator::JvmRandomOrderGenerator(const std::unique_ptr<JVMInterface>& jvm_interface) :JvmRandomOrderGenerator(*jvm_interface.get()) {

}

JvmRandomOrderGenerator::JvmRandomOrderGenerator(JVMInterface& jvm_interface) : JvmOrderGenerator(jvm_interface, RANDOM_ORDER_GENERATOR_CLASS_NAME) {
	if (jcls != nullptr) {
		jmethodID mid = env->GetMethodID(jcls, "<init>", "()V");
		if (mid != nullptr) {
			this->obj = env->NewGlobalRef(env->NewObject(jcls, mid));
#ifdef _DEBUG
			cout << "JvmRandomOrderGenerator::JvmRandomOrderGenerator() created obj" << endl;
#endif
			if (this->obj != nullptr) {
				this->applyMethodId = getApplyMethodId(env, jcls);
			}
			else {
#ifdef _DEBUG
				cout << "JvmRandomOrderGenerator::JvmRandomOrderGenerator() failed to create" << endl;
#endif
			}
		}
	}
}


std::unique_ptr<Order> JvmRandomOrderGenerator::apply(OHLC& olhcv) {
	return nullptr;
}

JvmRandomOrderGenerator::~JvmRandomOrderGenerator() {
	JvmOrderGenerator::~JvmOrderGenerator();
}

