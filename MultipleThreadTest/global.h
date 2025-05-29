#pragma once
#include <chrono>
// 只支持一个参数(如果想要使用多个参数, 请用一个结构体将他们再封装一层)
template <typename Duration, typename Fn, typename Repeat, typename Args>
double avgTime(Fn& const fn, Repeat&& count, Args&& args) {
	using namespace std::chrono;

	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	// repeat execute to make time avg and exact
	for (int i = 0; i < count; ++i) {
		fn(std::forward<Args>(args));  // 不是调用拷贝函数不应该用forward, 不过问题不大
	}
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	return duration_cast<Duration>(t2 - t1).count() / (double)count;
}
