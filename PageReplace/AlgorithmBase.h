#pragma once
#include <iostream>
#include <vector>
#include "SimpleBlockManager.h"

typedef std::vector<int> PageAccessSequence;

class AlgorithmBase {
protected:
	AlgorithmBase(int blockNum);
	virtual void Execute(PageAccessSequence sequence) = 0;

	int blockNum;
};