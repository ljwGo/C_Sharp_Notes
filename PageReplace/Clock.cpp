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

	std::cout << "��ѡ����Clock�㷨��ִ�н�����£�" << endl;

	int lossPageNum = 0;
	bool lossOfPage;
	int accessPage;
	int pointerIx = 0;

	// ��ʼ��flag
	for (int i = 0; i < blockNum; i++) {
		(*accessFlag)[i] = true;
	}

	for (int i = 0; i < sequence.size(); ++i) {
		accessPage = sequence[i];
		lossOfPage = true;

		// �鿴�Ƿ�ȱҳ, ����Ӧ�ø���pointerIx��, ������͵����
		for (int j = 0; j < blockNum; ++j) {
			if (accessPage == blockManager->GetVal(j)) {
				lossOfPage = false;
				// ���ķ��ʱ��
				(*accessFlag)[j] = true;
				break;
			}
		}

		if (lossOfPage) {
			lossPageNum++;
		}

		// ��û��ֱ�Ӽ�
		if (lossOfPage && !blockManager->IsFull()) {
			blockManager->Push(accessPage);
		}
		// ����, ʹ����̭�㷨, ������̭flagΪfalse��λ��
		else if (lossOfPage) {
			// �ҵ�Ҫ�滻������
			while ((*accessFlag)[pointerIx] != false) {
				(*accessFlag)[pointerIx] = false;
				pointerIx = (pointerIx + 1) % accessFlag->size();
			}

			// �滻, ͬʱ�ǵø���Ϊtrue
			blockManager->Push(pointerIx, accessPage);
			(*accessFlag)[pointerIx] = true;
			pointerIx = (pointerIx + 1) % accessFlag->size();
		}

		// �����ʱ�Ŀ�����
		std::cout << "����ҳ��        �����        ȱҳ�ж�" << endl;
		ostringstream ostr;

		ostr << accessPage << "               ";

		for (int i = 0; i < blockNum; ++i) {
			ostr << blockManager->GetVal(i) << ((*accessFlag)[i] ? '*':' ') << ' ';
		}

		ostr << "         " << (lossOfPage ? 'T' : 'F');
		std::cout << ostr.str() << endl;
	}

	std::cout << "ҳ����������ܳ�" << sequence.size() << "��Clock�㷨������ȱҳ�жϴ�" << lossPageNum << "��ȱҳ��Ϊ" << (float)lossPageNum / sequence.size() * 100 << '%' << endl;
}

Clock::~Clock()
{
	delete accessFlag;
	delete blockManager;
}
