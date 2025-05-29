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
	// ͵������һ��vector���������λ
	std::vector<bool>* accessFlag;
};

