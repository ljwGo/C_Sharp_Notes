#pragma once
#include "AlgorithmBase.h"
#include "SimpleBlockManager.h"

class FIFO : public AlgorithmBase{
public:
	FIFO(int blockNum);
	~FIFO();
	virtual void Execute(PageAccessSequence sequence);
private:
	SimpleBlockManager* blockManager;
};