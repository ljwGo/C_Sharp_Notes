#include "Clock.h"
#include "FIFO.h"
#include "LRU.h"
#include "OPT.h"
#include "LJWCommon.h"

#define BLOCK_SIZE 3

int main(void) {

	int sequenceSize;
	int blockNum;

	std::cout << "������ҳ��������г��ȣ�15 - 25�����˵㣩��" << std::endl;
	while (!LJWCode::LJWCommon::Instance()->LimitNumericalCin(15, 26, sequenceSize)) {
		std::cout << "�������ҳ��������г��ȳ���������Χ������������15-25�����˵㣩�����֣�" << std::endl;
	}

	std::cout << "����������������3-5�����˵㣩��" << std::endl;
	while (!LJWCode::LJWCommon::Instance()->LimitNumericalCin(3, 6, blockNum)) {
		std::cout << "�������������������������Χ������������3-5�����˵㣩�����֣�" << std::endl;
	}

	int choice = -1;
	std::cout << "��ѡ��ҳ������������ɷ�ʽ��1���û����룻2���������" << std::endl;
	std::cin >> choice;

	PageAccessSequence sequence(sequenceSize);
	int sequenceIter;
	char charSeq[100];
	bool ready = false;
	int remainSize;

	switch (choice)
	{
	case 1:
		remainSize = sequenceSize;
		sequenceIter = 0;
		while (!ready) {
			std::cout << "������0-5������ɵ��޹����ַ�����Ϊҳ��������У�����Ϊ" << remainSize << std::endl;
			std::cin >> charSeq;

			for (char* pchar = charSeq; *pchar != '\0'; pchar++) {
				switch (*pchar)
				{
				case '0':
					sequence[sequenceIter++] = 0;
					break;
				case '1':
					sequence[sequenceIter++] = 1;
					break;
				case '2':
					sequence[sequenceIter++] = 2;
					break;
				case '3':
					sequence[sequenceIter++] = 3;
					break;
				case '4':
					sequence[sequenceIter++] = 4;
					break;
				case '5':
					sequence[sequenceIter++] = 5;
					break;
				}

				// ��������
				if (sequenceIter >= sequenceSize) {
					std::cout << "�ѳɹ���ȡ�㹻�ĺϷ���������ҳ" << std::endl;
					ready = true;
					break;
				}
			}
			// �������и�������
			if (sequenceIter < sequenceSize) {
				remainSize = sequenceSize - sequenceIter;
				std::cout << "��������" << sequenceIter << "���ȵ���Ч�ַ�������������" << remainSize << "���ȵ��ַ���" << std::endl;
			}
		}

		break;
	case 2:
		for (int i = 0; i < sequenceSize; ++i) {
			sequence[i] = LJWCode::LJWCommon::Instance()->Random(0, 6);
		}
		break;
	}

	std::cout << "ҳ���������Ϊ: ";
	for (int i = 0; i < sequenceSize; i++) {
		std::cout << sequence[i] << ' ';
	}
	std::cout << std::endl;

	std::cout << "��������Ϊ" << blockNum << std::endl;

	FIFO fifo(blockNum);
	Clock clock(blockNum);
	LRU lru(blockNum);
	OPT opt(blockNum);

	while (choice) {
		std::cout << "��ѡ��Ҫִ�е�ҳ��ѡ���㷨��0.�˳�; 1��OPT��2��FIFO��3��LRU��4��CLOCK" << std::endl;
		std::cin >> choice;

		switch (choice)
		{
		case 0:
			break;
		case 1:
			opt.Execute(sequence);
			break;
		case 2:
			fifo.Execute(sequence);
			break;
		case 3:
			lru.Execute(sequence);
			break;
		case 4:
			clock.Execute(sequence);
			break;
		}
	}

	return 0;
}

int main_test(void) {

	PageAccessSequence sequence{ 0, 1, 2, 3, 0, 1, 2, 0, 1, 0};
	FIFO fifo(BLOCK_SIZE);
	Clock clock(BLOCK_SIZE);
	LRU lru(BLOCK_SIZE);
	OPT opt(BLOCK_SIZE);

	fifo.Execute(sequence);
	opt.Execute(sequence);
	lru.Execute(sequence);
	clock.Execute(sequence);


	return 0;
}