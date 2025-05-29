#pragma once
#include <chrono>
// ֻ֧��һ������(�����Ҫʹ�ö������, ����һ���ṹ�彫�����ٷ�װһ��)
template <typename Duration, typename Fn, typename Repeat, typename Args>
double avgTime(Fn& const fn, Repeat&& count, Args&& args) {
	using namespace std::chrono;

	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	// repeat execute to make time avg and exact
	for (int i = 0; i < count; ++i) {
		fn(std::forward<Args>(args));  // ���ǵ��ÿ���������Ӧ����forward, �������ⲻ��
	}
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	return duration_cast<Duration>(t2 - t1).count() / (double)count;
}
