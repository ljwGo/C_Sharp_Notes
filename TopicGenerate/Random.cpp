#include "Random.h"

// 静态成员定义总是记不住
std::random_device Random::dev;
std::mt19937 Random::rng(dev());
std::uniform_real_distribution<float> Random::dist(0.f, 1.f);

int Random::Range(int left, int right)
{
	float f = Range((float)left, (float)right);
	int i = std::floor(f);

	i == right ? i -= 1 : i = i;
	return i;
}

float Random::Range(float left, float right)
{
	return left + __Random0To1() * (right - left);
}

bool Random::Happen(float possible)
{
	return __Random0To1() < possible;
}

float Random::__Random0To1()
{
	float f = dist(rng);
	assert(0. <= f && f <= 1.);
	return f;
}
