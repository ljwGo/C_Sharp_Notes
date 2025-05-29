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

// ����һ��ָʾ�����ļ�����, ��̭ʱ, ��̭block���������ٵ���һ��
void OPT::Execute(PageAccessSequence sequence)
{
	using namespace std;

	std::cout << "��ѡ����OPT�㷨��ִ�н�����£�" << endl;

	// ����������
	map<int, int> counter;

	for (int i = 0; i < sequence.size(); i++) {
		counter[sequence[i]]++;
	}

	int lossPageNum = 0;
	for (int i = 0; i < sequence.size(); ++i) {

		bool lossOfPage = true;
		// �鿴�Ƿ�ȱҳ
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

		// ��û��ֱ�Ӽ�
		if (lossOfPage && !blockManager->IsFull()) {
			blockManager->Push(sequence[i]);
			counter[sequence[i]]--;
		}
		// ����, ʹ����̭�㷨, ������̭�������г��ִ������ٵ�
		else if (lossOfPage) {
			int minCountIx = 0;
			for (int j = 0; j < blockNum; ++j) {
				if (counter[blockManager->GetVal(j)] < counter[blockManager->GetVal(minCountIx)]) {
					minCountIx = j;
				}
			}
			blockManager->Push(minCountIx, sequence[i]);
			// ���ִ�������һ��
			counter[sequence[i]]--;
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

	std::cout << "ҳ����������ܳ�" << sequence.size() << "��OPT�㷨������ȱҳ�жϴ�" << lossPageNum << "��ȱҳ��Ϊ" << (float)lossPageNum / sequence.size() * 100 << '%' << endl;
}
