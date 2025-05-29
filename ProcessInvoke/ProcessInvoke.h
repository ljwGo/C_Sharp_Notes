#pragma once
#include <vector>
#include <iostream>
#include <sstream>
#include "Process.h"
#include "LinkedQueue.h"

#define MAX_TIME_SIZE 10

class ProcessInvoke
{
public:
	ProcessInvoke(std::vector<Process>&& ps) noexcept;
	~ProcessInvoke();
	void SJP();
	void FCFS();
	void Timestamp(size_t timeSize);
	void Priority(bool allowRace);
private:
	void Reset();
	void _PrintInfo(string& algorithmName);
	size_t sumServerTime = 0;
	size_t minArriveTime = std::numeric_limits<size_t>::max();
	std::vector<Process> ps;
	std::vector<std::string>* invokeNameQueue;
	LinkedQueue<Process*> invokeQueue; 	// 用于时间片轮转的队列
};

