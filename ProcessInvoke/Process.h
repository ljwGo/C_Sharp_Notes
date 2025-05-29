#pragma once
#include <string>
class Process
{
public:

	Process(size_t arriveAtTime, size_t serverTime, size_t priority, std::string&& name) noexcept;
	void Reset();

	size_t arriveAtTime;
	size_t serverTime;
	size_t priority;
	size_t startTime;
	size_t completeTime;
	size_t turnOverTime;
	size_t iterServerTime;
	float hasWeightTurnOverTime;
	std::string name;
};

