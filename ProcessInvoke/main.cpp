#include "process.h"
#include "ProcessInvoke.h"
#include <vector>

void showMenu() {
	using namespace std;
	cout << "�����빦�����(0-5): " << endl;
	cout << "0: �˳�" << endl;
	cout << "1: �����ȷ���" << endl;
	cout << "2: �̽�������" << endl;
	cout << "3: ��̬���ȼ�" << endl;
	cout << "4: ʱ��Ƭ��ת" << endl;
	cout << "�����빦��ѡ��: ";
};

int main(void) {
	std::vector<Process> ps{
		{0, 4, 4, "A"},
		{1, 3, 2, "B"},
		{2, 5, 3, "C"},
		{3, 2, 5, "D"},
		{4, 4, 1, "E"},
	};

	ProcessInvoke pInvoke(std::move(ps));

	int choice = -1;

	while (choice) {
		showMenu();

		std::cin >> choice;

		switch (choice) {
		case 0: break;
		case 1:
		{
			pInvoke.FCFS();
			break;
		}
		case 2:
		{
			pInvoke.SJP();
			break;
		}
		case 3:
		{
			std::cout << "�Ƿ�������ռ(����0������, ������������):" << std::endl;
			int allowRace;
			std::cin >> allowRace;

			pInvoke.Priority(allowRace);
			break;
		}
		case 4:
		{
			std::cout << "������ʱ��Ƭ��С(1-" << MAX_TIME_SIZE << ")" << std::endl;
			int timeInfinitesimal;
			std::cin >> timeInfinitesimal;
			pInvoke.Timestamp(timeInfinitesimal);
			break;
		}
		}
	}
}

int main_test(void) {
	std::vector<Process> ps{
		{0, 4, 4, "A"},
		{1, 3, 2, "B"},
		{2, 5, 3, "C"},
		{3, 2, 5, "D"},
		{4, 4, 1, "E"},
	};

	ProcessInvoke pInvoke(std::move(ps));

	pInvoke.FCFS();
	pInvoke.SJP();
	pInvoke.Priority(true);
	pInvoke.Priority(false);
	pInvoke.Timestamp(2);
	pInvoke.Timestamp(3);

	return 0;
}
