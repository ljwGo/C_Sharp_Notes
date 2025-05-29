#include "Process.h"

Process::Process(size_t arriveAtTime, size_t serverTime, size_t priority, std::string&& name) noexcept 
	:arriveAtTime(arriveAtTime), serverTime(serverTime), priority(priority), name(std::move(name))
{
	Reset();
}

void Process::Reset()
{
	iterServerTime = serverTime;
	startTime = 0;
	completeTime = std::numeric_limits<unsigned int>::max();
	turnOverTime = 0;
	hasWeightTurnOverTime = 0;
}
