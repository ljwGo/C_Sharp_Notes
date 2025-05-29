#include <thread>
#include <chrono>
#include <iostream>
#include <vector>
#include "global.h"

inline long long b[1024] = { 1 };
inline std::vector<std::thread> threads(10);

inline int SimpleTask(int ix) {
	for (int i = 0; i < 10e6; i++) {
		b[ix] += i;
	}
	return b[ix];
}

// 同步问题
inline void IfSynchronization(int elementSpace){
	for (int i = 0; i < threads.size(); ++i) {
		threads[i] = std::thread(SimpleTask, i * elementSpace);
	}
	for (int i = 0; i < threads.size(); ++i) {
		threads[i].join();
	}
}

inline void TestForSync() {

	using namespace std;
	typedef chrono::milliseconds ms;

	double time, time02, time03;
	
	// 导致缓存行同步
	time = avgTime<ms>(IfSynchronization, 100, 1);
	cout << "01 finished in " << time << "milliseconds\n";
	// 不导致缓存行同步
	time02 = avgTime<ms>(IfSynchronization, 100, 16);
	cout << "02 finished in " << time02 << "milliseconds\n";
	// 共享资源
	time03 = avgTime<ms>(IfSynchronization, 100, 0);
	cout << "03 finished in " << time03 << "milliseconds\n";
}