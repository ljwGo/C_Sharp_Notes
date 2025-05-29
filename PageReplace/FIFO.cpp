#include "FIFO.h"
#include <iostream>
#include <sstream>

FIFO::FIFO(int blockNum) : AlgorithmBase(blockNum)
{
	blockManager = new SimpleBlockManager(blockNum);
}

FIFO::~FIFO()
{
	delete blockManager;
}

// 这里将执行和输出混合到一起了, 没有使用额外的存储来保存过程的数据
void FIFO::Execute(PageAccessSequence sequence)
{
	using namespace std;

	std::cout << "您选择了FIFO算法，执行结果如下：" << endl;

	int firstEnterIx = 0;
	int lossPageNum = 0;
	for (int i = 0; i < sequence.size(); ++i) {

		bool lossOfPage = true;
		// 查看是否缺页
		for (int j = 0; j < blockNum; ++j) {
			if (sequence[i] == blockManager->GetVal(j)) {
				lossOfPage = false;
				break;
			}
		}

		if (lossOfPage) {
			lossPageNum++;
		}

		// 块没满直接加
		if (lossOfPage && !blockManager->IsFull()) {
			blockManager->Push(sequence[i]);
		}
		// 满了, 使用淘汰算法, 使用一个指向最先进来的位置
		else if (lossOfPage) {
			blockManager->Push(firstEnterIx, sequence[i]);
			firstEnterIx = (firstEnterIx + 1) % blockNum;
		}

		// 输出此时的块序列
		std::cout << "访问页面        物理块        缺页中断" << endl;
		ostringstream ostr;

		ostr << sequence[i] << "               ";
		
		for (int i = 0; i < blockNum; ++i) {
			ostr << blockManager->GetVal(i) << ' ';
		}

		ostr << "         " << (lossOfPage ? 'T' : 'F');
		std::cout << ostr.str() << endl;
	}
	
	std::cout << "页面访问序列总长" << sequence.size() << "，FIFO算法共发生缺页中断次" << lossPageNum << "，缺页率为" << (float)lossPageNum / sequence.size() * 100 << '%' << endl;
}
