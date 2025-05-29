#pragma once
#include <vector>

class SimpleBlockManager
{
public:
	SimpleBlockManager(int size);
	~SimpleBlockManager();
	bool IsFull();
	bool Push(int val);
	bool Push(int ix, int val);
	int GetVal(int ix);

private:
	int eleIx;
	std::vector<int>* elements;
};

