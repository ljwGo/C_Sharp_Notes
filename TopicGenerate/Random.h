#pragma once
#include <random>
#include <assert.h>

class Random
{
public:
	static int Range(int left, int right);  // value scope: left close, right open
	static float Range(float left, float right);
	static bool Happen(float possible);
private:
	static float __Random0To1();
	static std::random_device dev;
	static std::mt19937 rng;
	static std::uniform_real_distribution<float> dist; // distribution in range [1, 6]
};

