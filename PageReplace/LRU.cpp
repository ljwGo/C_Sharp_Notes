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

	std::cout << "��ѡ����LRU�㷨��ִ�н�����£�" << endl;

	for (int i = 0; i < sequence.size(); ++i) {

		accessPage = sequence[i];
		lossOfPage = true;

		// ����ҳ�Ѿ�����,������������ͷ��
		if (blockLink->IsExist(accessPage, existIx)) {
			blockLink->Swap2Head(existIx);
			lossOfPage = false;
		}

		if (lossOfPage) {
			lossOfPageNum++;
		}

		// ������, ��Ҫ������ҳ
		if (lossOfPage && !blockLink->IsFull()) {
			blockLink->Insert(accessPage);
		}
		else if (lossOfPage){
			// ��̭�㷨, ��̭��βԪ��
			blockLink->SwapTailVal(accessPage);
			// �����Ǹü����, Ҫ������Ϊ���¼����
			blockLink->SwapTail2Head();
		}

		std::cout << "����ҳ��        �����        ȱҳ�ж�" << endl;
		ostringstream ostr;

		ostr << accessPage << "               ";

		for (int i = 0; i < blockNum; ++i) {
			ostr << blockLink->GetVal(i) << ' ';
		}

		ostr << "         " << (lossOfPage ? 'T' : 'F');
		std::cout << ostr.str() << endl;
	}

	std::cout << "ҳ����������ܳ�" << sequence.size() << "��LRU�㷨������ȱҳ�жϴ�" << lossOfPageNum << "��ȱҳ��Ϊ" << (float)lossOfPageNum / sequence.size() * 100 << '%' << endl;
}
