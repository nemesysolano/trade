
#include <iostream>
#include <string>
#include "jni-interface.h"
#include "datetime.h"
#include "ohlc.h"
#include <memory>
#include <cassert>
#include <crtdbg.h>

using namespace std;
using namespace bridge;

void validateDateTime(const JvmDateTime& jvm_datetime, int year, int month, int day, int hour, int minute, int second) {
	cout << "getYear: " << jvm_datetime.getYear() << endl;
	assert(jvm_datetime.getYear() == year);

	cout << "getMonth: " << jvm_datetime.getMonth() << endl;
	assert(jvm_datetime.getMonth() == month);

	cout << "getDay: " << jvm_datetime.getDay() << endl;
	assert(jvm_datetime.getDay() == day);

	cout << "getHour: " << jvm_datetime.getHour() << endl;
	assert(jvm_datetime.getHour() == hour);

	cout << "getMinute: " << jvm_datetime.getMinute() << endl;
	assert(jvm_datetime.getMinute() == minute);

	cout << "getSecond: " << jvm_datetime.getSecond() << endl;
	assert(jvm_datetime.getSecond() == second);
}

void validateDateTime(const unique_ptr<JVMInterface> & jvm) {
	int year = 2021, month = 10, day = 21, hour = 13, minute = 44, second = 59;
	struct JvmDateTime jvm_datetime(jvm, { second, minute, hour, day, month, year, 0, 0, 0 });
	struct JvmDateTime jvm_datetime_copy(jvm_datetime);
	struct JvmDateTime jvm_datetime_copy2 = jvm_datetime;
	validateDateTime(jvm_datetime_copy, year, month, day, hour, minute, second);
	validateDateTime(jvm_datetime, year, month, day, hour, minute, second);
	validateDateTime(jvm_datetime_copy2, year, month, day, hour, minute, second);
}

void validateOHLC(const JvmOHLC & jvm_ohlc, int year, int month, int day, int hour, int minute, int second){
	cout << "Open: " << jvm_ohlc.getOpen() << endl;
	cout << "High: " << jvm_ohlc.getHigh() << endl;
	cout << "Low: " << jvm_ohlc.getLow() << endl;
	cout << "Close: " << jvm_ohlc.getClose() << endl;
	cout << "Volume: " << jvm_ohlc.getVolume() << endl;
	cout << "Year: " << jvm_ohlc.getYear() << endl;
	cout << "Month: " << jvm_ohlc.getMonth() << endl;
	cout << "Day: " << jvm_ohlc.getDay() << endl;
	cout << "Hour: " << jvm_ohlc.getHour() << endl;
	cout << "Minute: " << jvm_ohlc.getMinute() << endl;
	cout << "Second: " << jvm_ohlc.getSecond() << endl;
	assert(jvm_ohlc.getYear() == year);
	assert(jvm_ohlc.getMonth() == month);
	assert(jvm_ohlc.getDay() == day);
	assert(jvm_ohlc.getHour() == hour);
	assert(jvm_ohlc.getMinute() == minute);
	assert(jvm_ohlc.getSecond() == second);

	assert(jvm_ohlc.getOpen() == 1.0);
	assert(jvm_ohlc.getHigh() == 2.0);
	assert(jvm_ohlc.getLow() == 3.0);
	assert(jvm_ohlc.getClose() == 4.0);
	assert(jvm_ohlc.getVolume() == 5.0);

}
void validateOHLC(const unique_ptr<JVMInterface>& jvm) {
	double open = 1.0, high = 2.0, low = 3.0, close = 4.0, volume = 5.0;
	int year = 2021, month = 10, day = 21, hour = 13, minute = 44, second = 59;
	struct JvmOHLC jvm_ohlc(jvm, { open, high, low, close, volume, {second, minute, hour, day, month, year, 0, 0 } });
	struct JvmOHLC jvm_ohlc_copy(jvm_ohlc);
	struct JvmOHLC jvm_ohlc_copy2 = jvm_ohlc;
	validateOHLC(jvm_ohlc_copy, year, month, day, hour, minute, second);
	validateOHLC(jvm_ohlc, year, month, day, hour, minute, second);
	validateOHLC(jvm_ohlc_copy2, year, month, day, hour, minute, second);

}

void runTests(char* argv[]) {
	string class_path = "-Djava.class.path=" + string(argv[1]);
	unique_ptr<JVMInterface> jvm = unique_ptr<JVMInterface>(new JVMInterface(class_path));
	validateDateTime(jvm);
	validateOHLC(jvm);

}
int main(int argc, char * argv[])
{

	if (argc < 2) {
		cout << "Usage: bridge-test <path-to-jar>" << endl;
		return 1;
	}
	
	_CrtMemState sOld;
	_CrtMemState sNew;
	_CrtMemState sDiff;
	_CrtMemCheckpoint(&sOld); //take a snapshot

	runTests(argv);


	_CrtMemCheckpoint(&sNew); //take a snapshot 
	if (_CrtMemDifference(&sDiff, &sOld, &sNew)) // if there is a difference
	{
		cout << "-----------_CrtMemDumpStatistics ---------" << endl;
		_CrtMemDumpStatistics(&sDiff);

		cout << "-----------_CrtMemDumpAllObjectsSince ---------" << endl;
		_CrtMemDumpAllObjectsSince(&sOld);

		cout << "-----------_CrtDumpMemoryLeaks ---------" << endl;
		_CrtDumpMemoryLeaks();

	}

	return 0;
}


