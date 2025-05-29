#pragma once
#include <vector>
#include <iostream>

constexpr size_t PAGE_UNIT = 1024;

class PageManager
{
public:
	PageManager(size_t pageUnitCount, size_t pageTableLength);
	bool SetBlockNumber(size_t number, int& conflictNumber);
	bool Check(size_t logicAddress, size_t& pageIx, size_t& pageOffset, size_t& blockAddress, size_t& blockOffset, size_t& physicsAddress);
	void Show();

private:
	size_t currentIx = 0;
	size_t pageSize;
	std::vector<size_t> pageTable;
};

