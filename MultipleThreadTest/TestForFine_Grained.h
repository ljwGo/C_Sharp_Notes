#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include "global.h"

// 6线程, 执行细颗粒度任务, 线程每次处理数组100个元素
// 6线程, 执行非细颗粒度任务, 线程每次处理数组100e3的元素

inline size_t numEntities = 100e4;
inline size_t numThreads = 6;
inline std::vector<double> v;

inline void ThreadWork(int startIx, int endIx){
	// simple work. sum all value between startIx and endIx
	double sum = 0L;
	for (int i = startIx; i <= endIx; i++) {
		sum += v[i];
	}
}

inline void LaunchThread(size_t numPerThread) {
	int curIx = 0;
	while (curIx < numEntities) {
		std::vector<std::thread> threads;
		threads.reserve(numThreads);

		// per thread handle 'numPerThread' value at once
		for (int i = 0; i < numThreads; i++) {

			int endIx = (curIx + numPerThread - 1);
			std::thread t;

			// Cannot cross the index scope
			if (endIx >= numEntities) {
				endIx = numEntities - 1;

				t = std::thread(ThreadWork, curIx, endIx);
				threads.push_back(std::move(t));
				curIx += numPerThread;

				break;
			}

			t = std::thread(ThreadWork, curIx, endIx);
			threads.push_back(std::move(t));
			curIx += numPerThread;
		}

		for (int i = 0; i < threads.size(); i++) {
			threads[i].join();
		}
	}
}

inline void SingleThreadWork(std::vector<double>& v) {
	double sum = 0;
	for (int i = 0; i < v.size(); ++i) {
		sum += v[i];
	}
}

inline void TestForGrained(){

	using namespace std;
	typedef chrono::microseconds ms;

	for (int i=0; i< numEntities; ++i){
		v.push_back(i);
	}

	double avgFineGrained = 0, avgNoFineGrained = 0 , avgSingleThread = 0;

	// execute many time in order to imporve resolution.
	// fine-grained 细颗粒度线程(执行任务过于简单)
	avgFineGrained = avgTime<ms>(LaunchThread, 100, 1000);
	// less fine-grained 
	avgNoFineGrained = avgTime<ms>(LaunchThread, 100, 100e3);
	// single thread
	avgSingleThread = avgTime<ms>(SingleThreadWork, 100, v);

	cout << "avgFineGrained finished in " << avgFineGrained << "milliseconds\n";
	cout << "avgNoFineGrained finished in " << avgNoFineGrained << "milliseconds\n";
	cout << "avgSingleThread finished in " << avgSingleThread << "microseconds\n";

}