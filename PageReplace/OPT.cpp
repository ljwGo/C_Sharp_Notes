#include "OPT.h"
#include <map>
#include <sstream>

OPT::OPT(int blockNum) : AlgorithmBase(blockNum)
{
	blockManager = new SimpleBlockManager(blockNum);
}

OPT::~OPT()
{
	delete blockManager;
}

// 创建一个指示数量的计数器, 淘汰时, 淘汰block中数量最少的那一个
void OPT::Execute(PageAccessSequence sequence)
{
	using namespace std;

	std::cout << "您选择了OPT算法，执行结果如下：" << endl;

	// 创建计数器
	map<int, int> counter;

	for (int i = 0; i < sequence.size(); i++) {
		counter[sequence[i]]++;
	}

	int lossPageNum = 0;
	for (int i = 0; i < sequence.size(); ++i) {

		bool lossOfPage = true;
		// 查看是否缺页
		for (int j = 0; j < blockNum; ++j) {
			if (sequence[i] == blockManager->GetVal(j)) {
				lossOfPage = false;
				counter[sequence[i]]--;
				break;
			}
		}

		if (lossOfPage) {
			lossPageNum++;
		}

		// 块没满直接加
		if (lossOfPage && !blockManager->IsFull()) {
			blockManager->Push(sequence[i]);
			counter[sequence[i]]--;
		}
		// 满了, 使用淘汰算法, 这里淘汰后续队列出现次数最少的
		else if (lossOfPage) {
			int minCountIx = 0;
			for (int j = 0; j < blockNum; ++j) {
				if (counter[blockManager->GetVal(j)] < counter[blockManager->GetVal(minCountIx)]) {
					minCountIx = j;
				}
			}
			blockManager->Push(minCountIx, sequence[i]);
			// 出现次数减少一次
			counter[sequence[i]]--;
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

	std::cout << "页面访问序列总长" << sequence.size() << "，OPT算法共发生缺页中断次" << lossPageNum << "，缺页率为" << (float)lossPageNum / sequence.size() * 100 << '%' << endl;
}
