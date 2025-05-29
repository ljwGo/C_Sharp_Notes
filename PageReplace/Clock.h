#pragma once
#include "AlgorithmBase.h"
#include "SimpleBlockManager.h"
#include <vector>

class Clock
	: public AlgorithmBase
{
public:
	Clock(int blockNum);
	~Clock();
	virtual void Execute(PageAccessSequence sequence);
private:
	SimpleBlockManager* blockManager;
	// 偷懒就用一个vector来代替访问位
	std::vector<bool>* accessFlag;
};

