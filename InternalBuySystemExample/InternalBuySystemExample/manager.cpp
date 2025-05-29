#include <iostream>
#include <string>
#include "manager.h"
#include "layfolk.h"

using namespace std;

extern AdminGroup<Admin*> adminGroup;
extern CustomerGroup<Buyer*> customerGroup;
extern BookShelf<Book*> bookShelf;

Admin* Manager::loginedAdmin = NULL;
Buyer* Manager::loginedBuyer = NULL;

void Manager::showMenu() {
	cout << "========功能菜单========" << endl;
	cout << "-1: 退出" << endl;
	cout << "1: 管理员登陆" << endl;
	cout << "2: 顾客登录" << endl;
	cout << "3: 管理员注册" << endl;
	cout << "4: 顾客注册" << endl;
	cout << endl;
}
// login和adminLogin的逻辑很类似, 但是有些微不同, 只有两个类似函数, 就不使用函数模板了
bool Manager::adminLogin() {
	string account;
	string password;
	Admin* pAdmin = NULL;

	cout << "请输入账号: ";
	cin >> account;
	cout << endl;
	cout << "请输入密码: ";
	cin >> password;
	cout << endl;

	// 在管理员容器中找到指定账号的管理员
	pAdmin = adminGroup.getEleByAccount(account);
	if (pAdmin == NULL) {
		cout << "账号不存在" << endl;
	}
	else {
		// 密码正确
		if (pAdmin->passwordVaild(password)) {
			cout << "登录成功" << endl;
			// 设置当前登录人员
			Manager::loginedAdmin = pAdmin;
			Manager::loginedBuyer = NULL;
			return true;
		}
		else {
			cout << "密码错误" << endl;
		}
	}
	return false;
}
bool Manager::login() {
	string account;
	string password;
	Buyer* pBuyer = NULL;

	cout << "请输入账号: ";
	cin >> account;
	cout << endl;
	cout << "请输入密码: ";
	cin >> password;
	cout << endl;

	pBuyer = customerGroup.getEleByAccount(account);
	if (pBuyer == NULL) {
		cout << "账号不存在" << endl;
	}
	else {
		if (pBuyer->passwordVaild(password)) {
			cout << "登录成功" << endl;
			// 这里之前写错了, 将loginedBuyer置为空指针, 居然也是能够调用到loginedBuyer的成员函数
			Manager::loginedBuyer = pBuyer;
			Manager::loginedAdmin = NULL;
			return true;
		}
		else {
			cout << "密码错误" << endl;
		}
	}
	return false;
}
void Manager::signIn() {
	string account;
	string password;
	string confirmPassword;
	string address;
	string name;
	Buyer* pBuyer = NULL;

	cout << "请输入账号: ";
	cin >> account;
	cout << endl;
	cout << "请输入密码: ";
	cin >> password;
	cout << endl;
	cout << "请确认密码 ";
	cin >> confirmPassword;
	cout << endl;
	cout << "请输入地址: ";
	cin >> address;
	cout << endl;
	cout << "请输入姓名: ";
	cin >> name;
	cout << endl;

	if (password.compare(confirmPassword)) {
		cout << "两次密码不一致" << endl;
		return;
	}
	else {
		try {
			pBuyer = new LayFolk(name, account, password, address, customerGroup, 0);
			customerGroup.push(pBuyer);
			cout << "注册成功" << endl;
		}
		catch (int i) { ; }
	}
}
void Manager::signInAdmin() {
	string account;
	string password;
	string confirmPassword;
	string name;
	Admin* pAdmin = NULL;

	cout << "请输入账号: ";
	cin >> account;
	cout << endl;
	cout << "请输入密码: ";
	cin >> password;
	cout << endl;
	cout << "请确认密码 ";
	cin >> confirmPassword;
	cout << endl;
	cout << "请输入姓名: ";
	cin >> name;
	cout << endl;

	if (password.compare(confirmPassword)) {
		cout << "两次密码不一致" << endl;
		return;
	}
	else {
		try {
			pAdmin = new Admin(name, account, password, adminGroup);
			adminGroup.push(pAdmin);
			cout << "注册成功" << endl;
		}
		catch (int i) { ;  }
	}
}
void Manager::runBase() {
	int choice = -1;
	do {
		system("cls");

		Manager::showMenu();

		cout << endl;
		cout << "请输入功能选项(-1表示退出):";
		cin >> choice;
		cin.clear();
		cin.ignore(1000, '\n');
		system("cls");
		cout << endl;

		switch (choice) {
			case -1: break;
			case 1: 
				if (adminLogin()) {
					Manager::runAdminFunc();
				}
				break;
			case 2:
				if (login()) {
					Manager::runBuyerFunc();
				}
				break;
			case 3:
				signInAdmin();
				break;
			case 4:
				signIn();
				break;
			default:
				cout << "请输入正确选项: " << endl;
				break;
		}

		if (choice != -1) {
			system("pause");
		}
	} while (choice != -1);
}
void Manager::showCurPerson() {
	if (Manager::loginedAdmin != NULL) {
		Manager::loginedAdmin->display();
	}
	else if (Manager::loginedBuyer != NULL) {
		Manager::loginedBuyer->display();
	}
}
void Manager::runAdminFunc() {
	int choice = -1;
	unsigned int id;
	string title;

	do {
		system("cls");
		Manager::showAdminMenu();

		cout << endl;
		cout << "请输入功能选项(-1表示退出): ";
		cin >> choice;
		cin.clear();
		cin.ignore(1000, '\n');
		system("cls");
		cout << endl;

		switch (choice) {
		case -1: 
			// 返回上层, 注销登录的管理员
			Manager::loginedAdmin = NULL;
			break;
		case 1:
			Manager::loginedAdmin->addBook(bookShelf);
			break;
		case 2:
			cout << "请输入书本id: ";
			cin >> id;
			cin.clear();
			cin.ignore(1000, '\n');
			cout << endl;
			// 这里不应该使用返回bool值的方式,判断函数是否执行成功. 最好使用抛出错误的方式
			Manager::loginedAdmin->removeBook(bookShelf, id) ?
				cout << "删除成功" << endl : cout << "id为" << id << "的书不存在" << endl;
 			break;
		case 3:
			cout << "请输入书本书名: ";
			cin >> title;
			cout << endl;
			Manager::loginedAdmin->removeBook(bookShelf, title) ?
				cout << "删除成功" << endl : cout << "本书为" << title << "的书不存在" << endl;
			title = "";
			break;
		case 4:
			cout << "请输入书本id: ";
			cin >> id;
			cin.clear();
			cin.ignore(1000, '\n');
			cout << endl;
			Manager::loginedAdmin->setBook(bookShelf, id);
			break;
		case 5:
			cout << "请输入书本书名: ";
			cin >> title;
			cout << endl;
			Manager::loginedAdmin->setBook(bookShelf, title);
			break;
		case 6:
			showCurPerson();
			break;
		case 7:
			bookShelf.display();
			break;
		default:
			cout << "请输入正确选项: " << endl;
			break;
		}
		
		if (choice != -1) {
			system("pause");
		}
	} while (choice != -1);
}
void Manager::showAdminMenu() {
	cout << "========管理员功能列表========" << endl;
	cout << "-1: 回到上一层" << endl;
	cout << "1: 新增书籍" << endl;
	cout << "2: 通过id删除书籍" << endl;
	cout << "3: 通过书名删除书籍" << endl;
	cout << "4: 通过id修改书籍信息" << endl;
	cout << "5: 通过书名修改书籍信息" << endl;
	cout << "6: 显示当前登录管理员信息" << endl;
	cout << "7: 显示所有书籍" << endl;
	cout << endl;
}
void Manager::runBuyerFunc() {
	int choice = -1;
	unsigned int amount;
	unsigned int id;
	unsigned int money;
	string title;

	do {
		system("cls");
		Manager::showBuyerMenu();

		cout << endl;
		cout << "请输入功能选项(-1表示退出):";
		cin >> choice;
		// 重置cin状态标记
		cin.clear();
		// 清空标准输入流中的字符
		cin.ignore(1000, '\n');
		// 清空命令行内容
		system("cls");
		cout << endl;

		switch (choice) {
		case -1: 
			Manager::loginedBuyer = NULL;
			break;
		case 1:
			bookShelf.display();
			break;
		case 2:
			cout << "请输入书本id: ";
			cin >> id;
			cin.clear();
			cin.ignore(1000, '\n');
			cout << endl;

			cout << "请输入购买数量: ";
			cin >> amount;
			cin.clear();
			cin.ignore(1000, '\n');
			Manager::loginedBuyer->buyBookById(id, amount, bookShelf);
			break;
		case 3:
			cout << "请输入书本id: ";
			cin >> id;
			cin.clear();
			cin.ignore(1000, '\n');
			cout << endl;

			cout << "请输入删除数量: ";
			cin >> amount;
			cin.clear();
			cin.ignore(1000, '\n');
			Manager::loginedBuyer->removeBookById(id, amount);
			break;
		case 4:
			cout << "请输入书本id: ";
			cin >> id;
			cin.clear();
			cin.ignore(1000, '\n');
			cout << endl;

			cout << "请设置新数量: ";
			cin >> amount;
			cin.clear();
			cin.ignore(1000, '\n');
			Manager::loginedBuyer->setBookById(id, amount, bookShelf);
			break;
		case 5:
			cout << "请输入书名: ";
			cin >> title;
			cout << endl;
			cout << "请输入购买数量: ";
			cin >> amount;
			cin.clear();
			cin.ignore(1000, '\n');
			Manager::loginedBuyer->buyBookByTitle(title, amount, bookShelf);
			break;
		case 6:
			cout << "请输入书名: ";
			cin >> title;
			cout << endl;
			cout << "请输入删除数量: ";
			cin >> amount;
			cin.clear();
			cin.ignore(1000, '\n');
			Manager::loginedBuyer->removeBookByTitle(title, amount);
			break;
		case 7:
			cout << "请输入书名: ";
			cin >> title;
			cout << endl;
			cout << "请设置新数量: ";
			cin >> amount;
			cin.clear();
			cin.ignore(1000, '\n');
			Manager::loginedBuyer->setBookByTitle(title, amount, bookShelf);
			break;
		case 8:
			Manager::loginedBuyer->showOrder();
			break;
		case 9:
			Manager::loginedBuyer->showMoney();
			break;
		case 10:
			cout << "请输入充值金额: " << endl;
			cin >> money;
			cin.clear();
			cin.ignore(1000, '\n');
			cout << endl;
			Manager::loginedBuyer->recharge(money);
			break;
		case 11:
			Manager::loginedBuyer->resetOrder();
			break;
		case 12:
			Manager::loginedBuyer->pay(bookShelf);
			break;
		case 13:
			Manager::loginedBuyer->display();
			break;
		default:
			cout << "请输入正确选项: " << endl;
			break;
		}

		if (choice != -1) {
			system("pause");
		}
	} while (choice != -1);
}
void Manager::showBuyerMenu() {
	cout << "========购买者功能菜单========" << endl;
	cout << "-1: 退回上一层" << endl;
	cout << "1: 查看所有书籍" << endl;
	cout << "2: 通过id< 订购 >指定数量的书籍" << endl;
	cout << "3: 通过id< 删除 >订单中的书籍数量" << endl;
	cout << "4: 通过id< 修改 >订单中的书籍数量(订单中不存在时, 请先添加书籍到订单)" << endl;
	cout << "5: 通过书名< 订购 >指定数量的书籍" << endl;
	cout << "6: 通过书名< 删除 >订单中的书籍数量" << endl;
	cout << "7: 通过书名< 修改 >订单中的书籍数量(订单中不存在时, 请先添加书籍到订单)" << endl;
	cout << "8: 查看订单" << endl;
	cout << "9: 查看余额" << endl;
	cout << "10: 充值金额" << endl;
	cout << "11: 清空购物清单" << endl;
	cout << "12: 付款" << endl;
	cout << "13: 显示本人信息" << endl;
	cout << endl;
}

