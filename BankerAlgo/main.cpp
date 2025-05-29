#include "Process.h"
#include "Binker.h"
#include "global.h"

void showMenu() {
	using namespace std;
	cout << "�����빦�����(0-5): " << endl;
	cout << "0: �˳�" << endl;
	cout << "1: ��ȫ�Լ��" << endl;
	cout << "2: ��ǰʱ�̽�����Ϣ" << endl;
	cout << "3: ָ��ʱ�̵Ľ�����Ϣ" << endl;
	cout << "4: �ص�ָ��ʱ��" << endl;
	cout << "5: ������Դ" << endl;
	cout << "�����빦��ѡ��: ";
};

int main() {
	std::vector<Process> ps = std::vector<Process>{
	Process(source{ 7, 5, 3 }, source{ 0, 1, 0 }),
	Process(source{ 3, 2, 2 }, source{ 2, 0, 0 }),
	Process(source{ 9, 0, 2 }, source{ 3, 0, 2 }),
	Process(source{ 2, 2, 2 }, source{ 2, 1, 1 }),
	Process(source{ 4, 3, 3 }, source{ 0, 0, 2 }),
	};

	Binker bink(source{ 10, 5, 7 }, std::move(ps));

	int choice = -1;

	while (choice) {
		showMenu();

		std::cin >> choice;

		switch (choice) {
		case 0: break;
		case 1:
		{
			bink.SecurityDetect();
			break;
		}
		case 2:
		{
			bink.CurrentTimestampInfo();
			break;
		}
		case 3:
		{
			std::cout << "������ʱ������" << std::endl;
			int timestampIx;
			std::cin >> timestampIx;
			bink.ShowTimestampInfo(timestampIx);
			break;
		}
		case 4:
		{
			std::cout << "������ʱ������" << std::endl;
			int timestampIx;
			std::cin >> timestampIx;
			bink.ReturnTimestamp(timestampIx);
			break;
		}
		case 5:
		{
			int processIx;
			int sourceNum = 0;
			source giveSource;

			std::cout << "��������Ҫ������Դ�Ľ��̺�(0-" 
				<< bink.GetCurrentStampProcessSize()-1 << ")" << std::endl;
			std::cin >> processIx;
			std::cout << "��������Ҫ�������Դ��(һ������һ��, -1�˳�): " << std::endl;
			
			while (sourceNum != -1) {
				std::cin >> sourceNum;
				giveSource.push_back(sourceNum);
			}
			// ��֪��Ϊʲô, giveSource�Ĵ�С�ܻ����ӵĸ�����һ, �㲻����
			giveSource.resize(giveSource.size() - 1);
			bink.GiveSource(processIx, std::move(giveSource));
			break;
		}
		}
	}
}

int main_test() {

	std::vector<Process> ps = std::vector<Process>{
		Process(source{ 7, 5, 3 }, source{ 0, 1, 0 }),
		Process(source{ 3, 2, 2 }, source{ 2, 0, 0 }),
		Process(source{ 9, 0, 2 }, source{ 3, 0, 2 }),
		Process(source{ 2, 2, 2 }, source{ 2, 1, 1 }),
		Process(source{ 4, 3, 3 }, source{ 0, 0, 2 }),
	};

	Binker bink(source{ 10, 5, 7 }, std::move(ps));
	//bink.SecurityDetect();
	bink.CurrentTimestampInfo();

	bink.GiveSource(1, source{2, 2, 2});  // giveSource is more than need
	bink.GiveSource(2, source{6, 0, 0});  // giveSource is more than available
	bink.GiveSource(0, source{3, 3, 2});  // due to unsecurity sequence

	bink.GiveSource(1, source{1, 2, 2});  // can allocate
	//bink.SecurityDetect();
	bink.CurrentTimestampInfo();

	bink.ReturnTimestamp(100);  // return no exist timestamp
	bink.ReturnTimestamp(0);
	bink.CurrentTimestampInfo();
	bink.GiveSource(1, source{ 1, 1, 1 });
	bink.CurrentTimestampInfo();
	return 0;
}