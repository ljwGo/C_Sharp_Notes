#include "PageManager.h"
#include "SegementManager.h"
#include "LJWCommon.h"
#include <iostream>

int main(void) {
	int choice = -1;

	while (choice != 2) {

		std::cout << "������Ҫѡ��ĵ�ַ�仯��ʽ����0-��ҳ��1-�ֶ�; 2-�˳���" << std::endl;

		std::cin >> choice;

		switch (choice) {
		case 0: 
		{
#pragma region GeneratePageSize
			int size = 0, length = -1, sizeChoice = -1;
			std::cout << "������ÿҳ��С����0-1K��1-2K��2-4K��3-���ѡ��" << std::endl;
			std::cin >> sizeChoice;

			std::cout << "������ҳ�����������5��10֮�����������˵㣩" << std::endl;
			std::cin >> length;

			if (length < 5 || length > 10) {
				std::cout << "ҳ�����������5��10֮��" << std::endl;
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
				// �����1, 2, 4k��ѡ��
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
			
			std::cout << "������ҳ����ÿҳ��Ӧ�Ŀ�ţ���0-�ֶ����룻1-�������0��10֮��ķ��ظ�������Ϊ��ţ�" << std::endl;
			std::cin >> blockChoice;

			switch (blockChoice)
			{
			case 0:
			{
				while (iter < length) {
					std::cout << "�����ǵ�" << iter << "ҳ, " << "�������Ӧ�Ŀ��: " << std::endl;
					std::cin >> blockNumber;

					if (page.SetBlockNumber(blockNumber, conflictNumber)) {
						iter++;
					}
					else {
						std::cout << "������Ŀ���������" << conflictNumber << "��ҳ������Ŀ���ظ��������������" << iter << "��ҳ���Ӧ�Ŀ�ţ�" << std::endl;
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
			std::cout << "�뿪ʼ��ı��ݣ������߼���ַ��" << std::endl;
			std::cin >> addresss;

			size_t pageIx, pageOffset, blockAddress, blockOffset, physicsAddress;

			if (page.Check(addresss, pageIx, pageOffset, blockAddress, blockOffset, physicsAddress)) {
				std::cout << "��ѡ���˷�ҳ��ʽ��������߼���ַΪ " << addresss << \
					"�����Ӧ��ҳ��Ϊ" << pageIx << \
					"��ҳƫ��Ϊ" << pageOffset << \
					", �õ�ַ��Ӧ�Ŀ��Ϊ" << blockAddress << \
					", ��ƫ��Ϊ" << blockOffset << \
					", �����ַΪ" << physicsAddress << std::endl;
			}
			else {
				std::cout << "������ĵ�ַ����������������룡" << std::endl;
			}

#pragma endregion

			break;
		}
		case 1:
		{
			int length = -1;
			std::cout << "������α����������5��10֮�����������˵㣩" << std::endl;
			std::cin >> length;

			SegmentManager segment(length);

			int iter = 0, conflictNumber = -1;
			int baseAddress = -1, segmentLength = -1, blockChoice = -1, segmentLengthChoice = -1;

			std::cout << "������ҳ����ÿ�ζ�Ӧ�Ļ�ַ�Ͷγ�����0-�ֶ����룻1-������ɣ�" << std::endl;
			std::cin >> blockChoice;

			switch (blockChoice)
			{
			case 0:
			{
				while (iter < length) {
					// ����Զλ�ַ�Ͷγ�û�����ϸ�ļ�������
					std::cout << "�����ǵ�" << iter << "��, " << "�������Ӧ�Ļ�ַ(��ַ��1K��100K): " << std::endl;
					std::cin >> baseAddress;

					std::cout << "�����ǵ�" << iter << "��, " << "�������Ӧ�Ķγ�(�γ���1K��2K��4K��8Kѡ��): " << std::endl;
					std::cin >> segmentLength;

					if (segment.SetSegmentInfo(baseAddress, segmentLength, conflictNumber)) {
						iter++;
					}
					else {
						std::cout << "������Ķ��������" << conflictNumber << "�Ŷ��ظ��������������" << iter << "�Ŷζ�Ӧ����Ϣ��" << std::endl;
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
			std::cout << "�뿪ʼ��ı��ݣ������߼���ַ��" << std::endl;
			std::cin >> addresss;

			size_t segmentIx, segmentOffset, baseAddr, physicsAddress;

			if (segment.Check(addresss, segmentIx, segmentOffset, baseAddr, physicsAddress)) {
				std::cout << "��ѡ���˷ֶη�ʽ��������߼���ַΪ " << addresss << \
					"�����Ӧ�Ķκ�Ϊ" << segmentIx << \
					"����ƫ��Ϊ" << segmentOffset << \
					", �öζ�Ӧ�Ļ�ַ" << baseAddr << \
					", ��ƫ��Ϊ" << segmentOffset << \
					", �����ַΪ" << physicsAddress << std::endl;
			}
			else {
				std::cout << "������ĵ�ַ����������������룡" << std::endl;
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