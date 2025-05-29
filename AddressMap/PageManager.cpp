#include "PageManager.h"
#include <assert.h>

PageManager::PageManager(size_t pageUnitCount, size_t pageTableLength)
{
	pageSize = pageUnitCount * PAGE_UNIT;

	pageTable.resize(pageTableLength);
	assert(pageTable.size() == pageTableLength);
}

bool PageManager::SetBlockNumber(size_t blockNumber, int& conflictNumber)
{
	// if pageTable has full
	if (currentIx == pageTable.size()) {
		conflictNumber = -1;
		return false;
	}

	// check if target blockNumber has been used
	bool hasUsed = false;

	for (int i = 0; i < currentIx; i++) {
		if (blockNumber == pageTable[i]) {
			hasUsed = true;
			conflictNumber = i;
			break;
		}
	}

	if (!hasUsed) {
		pageTable[currentIx++] = blockNumber;
		return true;
	}

	return false;
}

bool PageManager::Check(size_t logicAddress, size_t& pageIx, size_t& pageOffset, size_t& blockAddress, size_t& blockOffset, size_t& physicsAddress)
{
	pageIx = logicAddress / pageSize;
	pageOffset = logicAddress % pageSize;
	
	if (pageIx >= pageTable.size()) {
		return false;
	}

	// We assume block size is equal page size
	blockAddress = pageTable[pageIx];
	blockOffset = pageOffset;

	physicsAddress = blockAddress * pageSize + blockOffset;

	return true;
}

void PageManager::Show()
{
	using namespace std;
	cout << "��ҳ��ʽ���������������:" << endl;
	cout << "ÿҳ��С" << pageSize / 1024 << "K��ҳ��Ϊ" << endl;
	cout << "ҳ��    ���" << endl;
	for (int i = 0; i < pageTable.size(); i++) {
		cout << i << "     " << pageTable[i] << endl;
	}
}
