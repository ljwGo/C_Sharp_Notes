#include <thread>
#include <iostream>
#include <vector>
#include <mutex>

inline int num = 0;
inline std::vector<int> vn(1);
inline std::mutex myMutex;

// num+=1不是原子操作
inline void OperateN() {
	for (int i = 0; i < 10e7; ++i) {
		num += 1;
	}
}

// vector也不带锁
inline void OperateVN() {
	for (int i = 0; i < 10e7; ++i) {
		vn[0] += 1;
	}
}

inline void OperateNLock() {
	std::lock_guard<std::mutex> guard(myMutex);
	for (int i = 0; i < 10e7; ++i) {
		num += 1;
	}
}

inline void TestForOperateN() {
	std::thread t01 = std::thread(OperateN);
	std::thread t02 = std::thread(OperateN);

	t01.join();
	t02.join();

	std::cout << "The value of num is: " << num << std::endl;

	vn[0] = 0;
	t01 = std::thread(OperateVN);
	t02 = std::thread(OperateVN);
	t01.join();
	t02.join();

	std::cout << "The value of vn[0] is: " << vn[0] << std::endl;

	num = 0;
	t01 = std::thread(OperateNLock);
	t02 = std::thread(OperateNLock);

	t01.join();
	t02.join();

	std::cout << "The value of num is: " << num << std::endl;
}