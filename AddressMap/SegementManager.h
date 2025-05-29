#pragma once
#include <vector>
#include <iostream>

constexpr size_t SEGMENT_UNIT = 1024;

class SegmentManager
{
	typedef struct SegmentInfo {

		SegmentInfo() {
			baseAddress = 0;
			segmentSize = 0;
			tailAddress = 0;
		};
		SegmentInfo(size_t baseAddressUnitCount,size_t segmentUnitCount) {
			baseAddress = baseAddressUnitCount * SEGMENT_UNIT;
			segmentSize = segmentUnitCount * SEGMENT_UNIT;

			tailAddress = baseAddress + segmentSize - 1;
		}

		size_t baseAddress;
		size_t segmentSize;
		size_t tailAddress;
	} SegmentInfo;

public:
	SegmentManager(size_t segmentTableLength);
	bool SetSegmentInfo(size_t baseAddressUnitCount, size_t segmentUnitCount, int& conflictNumber);
	bool Check(size_t logicAddress, size_t& segmentIx, size_t& segmentOffset, size_t& baseAddress, size_t& physicsAddress);
	void Show();
private:
	size_t currentIx = 0;
	std::vector<SegmentInfo> segmentTable;
};

