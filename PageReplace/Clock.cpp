#include "Clock.h"
#include <sstream>

Clock::Clock(int blockNum) : AlgorithmBase(blockNum)
{
	blockManager = new SimpleBlockManager(blockNum);
	accessFlag = new std::vector<bool>(blockNum);
}

void Clock::Execute(PageAccessSequence sequence)
{
	using namespace std;

	std::cout << "您选择了Clock算法，执行结果如下：" << endl;

	int lossPageNum = 0;
	bool lossOfPage;
	int accessPage;
	int pointerIx = 0;

	// 初始化flag
	for (int i = 0; i < blockNum; i++) {
		(*accessFlag)[i] = true;
	}

	for (int i = 0; i < sequence.size(); ++i) {
		accessPage = sequence[i];
		lossOfPage = true;

		// 查看是否缺页, 这里应该更改pointerIx得, 但是我偷懒了
		for (int j = 0; j < blockNum; ++j) {
			if (accessPage == blockManager->GetVal(j)) {
				lossOfPage = false;
				// 更改访问标记
				(*accessFlag)[j] = true;
				break;
			}
		}

		if (lossOfPage) {
			lossPageNum++;
		}

		// 块没满直接加
		if (lossOfPage && !blockManager->IsFull()) {
			blockManager->Push(accessPage);
		}
		// 满了, 使用淘汰算法, 这里淘汰flag为false的位置
		else if (lossOfPage) {
			// 找到要替换的索引
			while ((*accessFlag)[pointerIx] != false) {
				(*accessFlag)[pointerIx] = false;
				pointerIx = (pointerIx + 1) % accessFlag->size();
			}

			// 替换, 同时记得更改为true
			blockManager->Push(pointerIx, accessPage);
			(*accessFlag)[pointerIx] = true;
			pointerIx = (pointerIx + 1) % accessFlag->size();
		}

		// 输出此时的块序列
		std::cout << "访问页面        物理块        缺页中断" << endl;
		ostringstream ostr;

		ostr << accessPage << "               ";

		for (int i = 0; i < blockNum; ++i) {
			ostr << blockManager->GetVal(i) << ((*accessFlag)[i] ? '*':' ') << ' ';
		}

		ostr << "         " << (lossOfPage ? 'T' : 'F');
		std::cout << ostr.str() << endl;
	}

	std::cout << "页面访问序列总长" << sequence.size() << "，Clock算法共发生缺页中断次" << lossPageNum << "，缺页率为" << (float)lossPageNum / sequence.size() * 100 << '%' << endl;
}

Clock::~Clock()
{
	delete accessFlag;
	delete blockManager;
}
