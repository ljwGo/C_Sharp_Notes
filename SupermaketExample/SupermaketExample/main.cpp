#include "supermarket.h"
#include <iostream>
#include <fstream>

using namespace std;

void showMenu() {
	cout << "====== 功能菜单 ======" << endl;
	cout << "-1: 退出" << endl;
	cout << " 1: 增加商品" << endl;
	cout << " 2: 出售商品" << endl;
	cout << " 3: 查看商品" << endl;
	cout << endl;
}

int main() {
	int choice = -1;
	Supermarket supermarket;

	ofstream oFoodFile;
	ofstream oEAFile;
	ofstream oDailyGoods;

	do {
		system("cls");
		showMenu();
		cout << "请输入功能选项: " << endl;
		cin >> choice;
		if (!cin.good()) {
			cin.clear();
			cin.ignore(1000, '\n');
		}

		system("cls");
		switch (choice) {
		case -1:
			break;
		case 1:
			try {
				supermarket.add();
			}
			catch (NumExceedLimit* error) {
				cout << error->message << endl;
				delete error;
			}
			catch (StrIsEmpty* error) {
				cout << error->message << endl;
				delete error;
			}
			break;
		case 2:
			try {
				supermarket.sale();
			}
			catch (EleNoExist* error) {
				cout << error->message << endl;
				delete error;
			}
			catch (NumExceedLimit* error) {
				cout << error->message << endl;
				delete error;
			}
			break;
		case 3:
			supermarket.search();
			break;
		default:
			cout << "选项不存在!" << endl;
			break;
		}
		if (choice != -1) {
			system("pause");
		}
	} while (choice != -1);
}