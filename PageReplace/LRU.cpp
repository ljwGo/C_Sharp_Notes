#include "LRU.h"
#include <iostream>
#include <sstream>

LRU::LRU(int blockNum) : AlgorithmBase(blockNum)
{
	blockLink = new TwowayLink(blockNum);
}

LRU::~LRU()
{
	delete blockLink;
}

void LRU::Execute(PageAccessSequence sequence)
{
	int lossOfPageNum = 0;
	int accessPage = 0;
	int existIx = 0;
	bool lossOfPage;

	using namespace std;

	std::cout << "您选择了LRU算法，执行结果如下：" << endl;

	for (int i = 0; i < sequence.size(); ++i) {

		accessPage = sequence[i];
		lossOfPage = true;

		// 访问页已经存在,将它调到队列头部
		if (blockLink->IsExist(accessPage, existIx)) {
			blockLink->Swap2Head(existIx);
			lossOfPage = false;
		}

		if (lossOfPage) {
			lossOfPageNum++;
		}

		// 不存在, 则要调度新页
		if (lossOfPage && !blockLink->IsFull()) {
			blockLink->Insert(accessPage);
		}
		else if (lossOfPage){
			// 淘汰算法, 淘汰队尾元素
			blockLink->SwapTailVal(accessPage);
			// 由于是该加入的, 要将它改为最新加入的
			blockLink->SwapTail2Head();
		}

		std::cout << "访问页面        物理块        缺页中断" << endl;
		ostringstream ostr;

		ostr << accessPage << "               ";

		for (int i = 0; i < blockNum; ++i) {
			ostr << blockLink->GetVal(i) << ' ';
		}

		ostr << "         " << (lossOfPage ? 'T' : 'F');
		std::cout << ostr.str() << endl;
	}

	std::cout << "页面访问序列总长" << sequence.size() << "，LRU算法共发生缺页中断次" << lossOfPageNum << "，缺页率为" << (float)lossOfPageNum / sequence.size() * 100 << '%' << endl;
}
