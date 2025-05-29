#include "Clock.h"
#include "FIFO.h"
#include "LRU.h"
#include "OPT.h"
#include "LJWCommon.h"

#define BLOCK_SIZE 3

int main(void) {

	int sequenceSize;
	int blockNum;

	std::cout << "请输入页面访问序列长度（15 - 25，含端点）：" << std::endl;
	while (!LJWCode::LJWCommon::Instance()->LimitNumericalCin(15, 26, sequenceSize)) {
		std::cout << "您输入的页面访问序列长度超出给定范围，请重新输入15-25（含端点）的数字：" << std::endl;
	}

	std::cout << "请输入物理块个数（3-5，含端点）：" << std::endl;
	while (!LJWCode::LJWCommon::Instance()->LimitNumericalCin(3, 6, blockNum)) {
		std::cout << "您输入的物理块个数超出给定范围，请重新输入3-5（含端点）的数字：" << std::endl;
	}

	int choice = -1;
	std::cout << "请选择页面访问序列生成方式：1、用户输入；2、随机生成" << std::endl;
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
			std::cout << "请输入0-5数字组成的无规律字符串作为页面访问序列，长度为" << remainSize << std::endl;
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

				// 序列已满
				if (sequenceIter >= sequenceSize) {
					std::cout << "已成功获取足够的合法访问序列页" << std::endl;
					ready = true;
					break;
				}
			}
			// 输入序列个数不足
			if (sequenceIter < sequenceSize) {
				remainSize = sequenceSize - sequenceIter;
				std::cout << "您已输入" << sequenceIter << "长度的有效字符串，还需输入" << remainSize << "长度的字符串" << std::endl;
			}
		}

		break;
	case 2:
		for (int i = 0; i < sequenceSize; ++i) {
			sequence[i] = LJWCode::LJWCommon::Instance()->Random(0, 6);
		}
		break;
	}

	std::cout << "页面访问序列为: ";
	for (int i = 0; i < sequenceSize; i++) {
		std::cout << sequence[i] << ' ';
	}
	std::cout << std::endl;

	std::cout << "物理块个数为" << blockNum << std::endl;

	FIFO fifo(blockNum);
	Clock clock(blockNum);
	LRU lru(blockNum);
	OPT opt(blockNum);

	while (choice) {
		std::cout << "请选择要执行的页面选择算法：0.退出; 1、OPT；2、FIFO；3、LRU；4、CLOCK" << std::endl;
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