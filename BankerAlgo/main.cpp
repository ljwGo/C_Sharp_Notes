#include "Process.h"
#include "Binker.h"
#include "global.h"

void showMenu() {
	using namespace std;
	cout << "请输入功能序号(0-5): " << endl;
	cout << "0: 退出" << endl;
	cout << "1: 安全性检测" << endl;
	cout << "2: 当前时刻进程信息" << endl;
	cout << "3: 指定时刻的进程信息" << endl;
	cout << "4: 回到指定时刻" << endl;
	cout << "5: 分配资源" << endl;
	cout << "请输入功能选项: ";
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
			std::cout << "请输入时刻索引" << std::endl;
			int timestampIx;
			std::cin >> timestampIx;
			bink.ShowTimestampInfo(timestampIx);
			break;
		}
		case 4:
		{
			std::cout << "请输入时刻索引" << std::endl;
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

			std::cout << "请输入需要申请资源的进程号(0-" 
				<< bink.GetCurrentStampProcessSize()-1 << ")" << std::endl;
			std::cin >> processIx;
			std::cout << "请输入需要申请的资源数(一次输入一个, -1退出): " << std::endl;
			
			while (sourceNum != -1) {
				std::cin >> sourceNum;
				giveSource.push_back(sourceNum);
			}
			// 不知道为什么, giveSource的大小总会比添加的个数多一, 搞不明白
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