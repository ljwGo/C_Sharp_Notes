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

// ���ｫִ�к������ϵ�һ����, û��ʹ�ö���Ĵ洢��������̵�����
void FIFO::Execute(PageAccessSequence sequence)
{
	using namespace std;

	std::cout << "��ѡ����FIFO�㷨��ִ�н�����£�" << endl;

	int firstEnterIx = 0;
	int lossPageNum = 0;
	for (int i = 0; i < sequence.size(); ++i) {

		bool lossOfPage = true;
		// �鿴�Ƿ�ȱҳ
		for (int j = 0; j < blockNum; ++j) {
			if (sequence[i] == blockManager->GetVal(j)) {
				lossOfPage = false;
				break;
			}
		}

		if (lossOfPage) {
			lossPageNum++;
		}

		// ��û��ֱ�Ӽ�
		if (lossOfPage && !blockManager->IsFull()) {
			blockManager->Push(sequence[i]);
		}
		// ����, ʹ����̭�㷨, ʹ��һ��ָ�����Ƚ�����λ��
		else if (lossOfPage) {
			blockManager->Push(firstEnterIx, sequence[i]);
			firstEnterIx = (firstEnterIx + 1) % blockNum;
		}

		// �����ʱ�Ŀ�����
		std::cout << "����ҳ��        �����        ȱҳ�ж�" << endl;
		ostringstream ostr;

		ostr << sequence[i] << "               ";
		
		for (int i = 0; i < blockNum; ++i) {
			ostr << blockManager->GetVal(i) << ' ';
		}

		ostr << "         " << (lossOfPage ? 'T' : 'F');
		std::cout << ostr.str() << endl;
	}
	
	std::cout << "ҳ����������ܳ�" << sequence.size() << "��FIFO�㷨������ȱҳ�жϴ�" << lossPageNum << "��ȱҳ��Ϊ" << (float)lossPageNum / sequence.size() * 100 << '%' << endl;
}
