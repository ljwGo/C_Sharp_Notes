#include "SegementManager.h"

SegmentManager::SegmentManager(size_t segmentTableLength) {
	segmentTable.resize(segmentTableLength);
}

bool SegmentManager::SetSegmentInfo(size_t baseAddressUnitCount, size_t segmentUnitCount, int& conflictNumber)
{
	if (currentIx >= segmentTable.size()) {
		conflictNumber = -1;
		return false;
	}

	bool hasUsed = false;
	// segment space has repeat used

	for (int i = 0; i < currentIx; i++) {
		size_t baseAddress = baseAddressUnitCount * SEGMENT_UNIT;
		size_t tailAddress = baseAddress + segmentUnitCount * SEGMENT_UNIT - 1;
	
		if (baseAddress >= segmentTable[i].baseAddress && baseAddress <= segmentTable[i].tailAddress) {
			conflictNumber = i;
			hasUsed = true;
			break;
		}

		if (tailAddress >= segmentTable[i].baseAddress && tailAddress <= segmentTable[i].tailAddress) {
			conflictNumber = i;
			hasUsed = true;
			break;
		}
	}

	if (!hasUsed) {
		segmentTable[currentIx++] = SegmentInfo(baseAddressUnitCount, segmentUnitCount);
		return true;
	}

	return false;
}

bool SegmentManager::Check(size_t logicAddress, size_t& segmentIx, size_t& segmentOffset, size_t& baseAddress, size_t& physicsAddress)
{
	size_t logicAddressIter = logicAddress;
	for (int i = 0; i < segmentTable.size(); i++) {
		if (logicAddressIter < segmentTable[i].segmentSize) {
			segmentIx = i;
			segmentOffset = logicAddressIter;
			baseAddress = segmentTable[i].baseAddress;
			physicsAddress = baseAddress + segmentOffset;
			return true;
		}
		logicAddressIter -= segmentTable[i].segmentSize;
	}

	return false;
}

void SegmentManager::Show()
{
	using namespace std;
	cout << "分段方式，输入的数据如下:" << endl;
	cout << "段号    基址    段长" << endl;
	for (int i = 0; i < segmentTable.size(); i++) {
		cout << i << "     " << segmentTable[i].baseAddress / 1024 << "K     " << segmentTable[i].segmentSize / 1024 << "K" << endl;
	}
}
