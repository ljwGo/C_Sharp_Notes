#include "PageManager.h"
#include "SegementManager.h"
#include "LJWCommon.h"
#include <iostream>

int main(void) {
	int choice = -1;

	while (choice != 2) {

		std::cout << "请输入要选择的地址变化方式：（0-分页；1-分段; 2-退出）" << std::endl;

		std::cin >> choice;

		switch (choice) {
		case 0: 
		{
#pragma region GeneratePageSize
			int size = 0, length = -1, sizeChoice = -1;
			std::cout << "请输入每页大小：（0-1K；1-2K；2-4K；3-随机选择）" << std::endl;
			std::cin >> sizeChoice;

			std::cout << "请输入页表项个数：（5到10之间整数，含端点）" << std::endl;
			std::cin >> length;

			if (length < 5 || length > 10) {
				std::cout << "页表个数必须在5到10之间" << std::endl;
				break;
			}

			switch (sizeChoice)
			{
			case 0:
			{
				size = 1;
				break;
			}
			case 1:
			{
				size = 2;
				break;
			}
			case 2:
			{
				size = 4;
				break;
			}
			case 3:
			{
				// 随机在1, 2, 4k中选择
				int randomInt = LJWCode::LJWCommon::Instance()->Random(0, 3);

				switch (randomInt)
				{
				case 0:
				{
					size = 1;
					break;
				}
				case 1:
				{
					size = 2;
					break;
				}
				case 2:
				{
					size = 4;
					break;
				}
				}
				break;
			}
			}

			if (size == 0) {
				break;
			}
#pragma endregion

			PageManager page(size, length);

#pragma region GenerateBlockMap
			int iter = 0, conflictNumber = -1;
			int blockNumber = -1, blockChoice = -1;
			
			std::cout << "请输入页表中每页对应的块号：（0-手动输入；1-随机生成0至10之间的非重复整数作为块号）" << std::endl;
			std::cin >> blockChoice;

			switch (blockChoice)
			{
			case 0:
			{
				while (iter < length) {
					std::cout << "现在是第" << iter << "页, " << "请输入对应的块号: " << std::endl;
					std::cin >> blockNumber;

					if (page.SetBlockNumber(blockNumber, conflictNumber)) {
						iter++;
					}
					else {
						std::cout << "您输入的块号有误，与第" << conflictNumber << "号页面输入的块号重复，请重新输入第" << iter << "号页面对应的块号！" << std::endl;
					}
				}
				break;
			}
			case 1:
			{
				while (iter < length) {
					blockNumber = LJWCode::LJWCommon::Instance()->Random(0, length * 10);
					
					if (page.SetBlockNumber(blockNumber, conflictNumber)) {
						iter++;
					}
				}
				break;
			}
			}
#pragma endregion

#pragma region ShowPageInfo
			page.Show();
#pragma endregion

#pragma region AddressCheck
			size_t addresss;
			std::cout << "请开始你的表演（输入逻辑地址）" << std::endl;
			std::cin >> addresss;

			size_t pageIx, pageOffset, blockAddress, blockOffset, physicsAddress;

			if (page.Check(addresss, pageIx, pageOffset, blockAddress, blockOffset, physicsAddress)) {
				std::cout << "您选择了分页方式，输入的逻辑地址为 " << addresss << \
					"，其对应的页号为" << pageIx << \
					"，页偏移为" << pageOffset << \
					", 该地址对应的块号为" << blockAddress << \
					", 块偏移为" << blockOffset << \
					", 物理地址为" << physicsAddress << std::endl;
			}
			else {
				std::cout << "您输入的地址已溢出，请重新输入！" << std::endl;
			}

#pragma endregion

			break;
		}
		case 1:
		{
			int length = -1;
			std::cout << "请输入段表项个数：（5到10之间整数，含端点）" << std::endl;
			std::cin >> length;

			SegmentManager segment(length);

			int iter = 0, conflictNumber = -1;
			int baseAddress = -1, segmentLength = -1, blockChoice = -1, segmentLengthChoice = -1;

			std::cout << "请输入页表中每段对应的基址和段长：（0-手动输入；1-随机生成）" << std::endl;
			std::cin >> blockChoice;

			switch (blockChoice)
			{
			case 0:
			{
				while (iter < length) {
					// 这里对段基址和段长没有做严格的检查和限制
					std::cout << "现在是第" << iter << "段, " << "请输入对应的基址(基址从1K至100K): " << std::endl;
					std::cin >> baseAddress;

					std::cout << "现在是第" << iter << "段, " << "请输入对应的段长(段长从1K，2K，4K，8K选择): " << std::endl;
					std::cin >> segmentLength;

					if (segment.SetSegmentInfo(baseAddress, segmentLength, conflictNumber)) {
						iter++;
					}
					else {
						std::cout << "您输入的段有误，与第" << conflictNumber << "号段重复，请重新输入第" << iter << "号段对应的信息！" << std::endl;
					}
				}
				break;
			}
			case 1:
			{
				while (iter < length) {
					baseAddress = LJWCode::LJWCommon::Instance()->Random(0, 100);
					segmentLengthChoice = LJWCode::LJWCommon::Instance()->Random(0, 4);

					switch (segmentLengthChoice)
					{
					case 0:
						segmentLength = 1;
						break;
					case 1:
						segmentLength = 2;
						break;
					case 2:
						segmentLength = 4;
						break;
					case 3:
						segmentLength = 8;
						break;
					default:
						segmentLength = 0;
						break;
					}

					if (segment.SetSegmentInfo(baseAddress, segmentLength, conflictNumber)) {
						iter++;
					}
				}
				break;
			}
			}

			segment.Show();

			size_t addresss;
			std::cout << "请开始你的表演（输入逻辑地址）" << std::endl;
			std::cin >> addresss;

			size_t segmentIx, segmentOffset, baseAddr, physicsAddress;

			if (segment.Check(addresss, segmentIx, segmentOffset, baseAddr, physicsAddress)) {
				std::cout << "您选择了分段方式，输入的逻辑地址为 " << addresss << \
					"，其对应的段号为" << segmentIx << \
					"，段偏移为" << segmentOffset << \
					", 该段对应的基址" << baseAddr << \
					", 段偏移为" << segmentOffset << \
					", 物理地址为" << physicsAddress << std::endl;
			}
			else {
				std::cout << "您输入的地址已溢出，请重新输入！" << std::endl;
			}

			break;
		}
		case 2:
		{
			break;
		}
		}
	}
}

int test_main(void) {

	PageManager page(1, 4);
	SegmentManager segment(10);

	int conflictNumber = -1;
	page.SetBlockNumber(1, conflictNumber);
	page.SetBlockNumber(3, conflictNumber);
	page.SetBlockNumber(10, conflictNumber);
	page.SetBlockNumber(10, conflictNumber);
	page.SetBlockNumber(11, conflictNumber);
	page.SetBlockNumber(8, conflictNumber);

	size_t pageIx, pageOffset, blockAddress, blockOffset, physicsAddress;
	page.Check(0, pageIx, pageOffset, blockAddress, blockOffset, physicsAddress);
	page.Check(1023, pageIx, pageOffset, blockAddress, blockOffset, physicsAddress);
	page.Check(1024, pageIx, pageOffset, blockAddress, blockOffset, physicsAddress);
	page.Check(4092, pageIx, pageOffset, blockAddress, blockOffset, physicsAddress);
	page.Check(5000, pageIx, pageOffset, blockAddress, blockOffset, physicsAddress);

	segment.SetSegmentInfo(1, 2, conflictNumber);
	segment.SetSegmentInfo(3, 4, conflictNumber);
	//segment.SetSegmentInfo(5, 2, conflictNumber);
	segment.SetSegmentInfo(10, 2, conflictNumber);

	size_t segmentIx, segmentOffset, baseAddress;
	segment.Check(0, segmentIx, segmentOffset, baseAddress, physicsAddress);
	segment.Check(1024, segmentIx, segmentOffset, baseAddress, physicsAddress);
	segment.Check(2056, segmentIx, segmentOffset, baseAddress, physicsAddress);
	segment.Check(10242, segmentIx, segmentOffset, baseAddress, physicsAddress);

	return 0;
}