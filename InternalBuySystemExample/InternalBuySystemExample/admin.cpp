#include <iostream>
#include "admin.h"
#include "book.h"
#include "bookShelf.h"
#include "adminGroup.h"


using namespace std;

unsigned int Admin::staticAdminId = 1; // 设置静态id号

// 无参构造函数
//Admin::Admin() {
//	name = "";
//	account = "";
//	password = "";
//	id = Admin::staticAdminId++;
//	//_isInit = false;
//}
Admin::Admin(string name, string account, string password, AdminGroup<Admin*> &adminGroup) {
	if (account == "") {
		cout << "账号不能为空!!!" << endl;
		throw 0;
	}
	if (adminGroup.isAccountExist(account)){
		cout << "账号已经存在了!!!" << endl;
		throw 0;
	}
	this->name = name;
	this->account = account;
	this->password = password;
	id = Admin::staticAdminId++;
	//_isInit = true;
}
void Admin::addBook(BookShelf<Book*>& bookShelf) {
	string title;
	string publishing;
	string author;
	double price;
	unsigned int amount;
	
	cout << "请输入书的名称, 作者, 出版社, 价格, 库存:" << endl;
	cin >> title;
	cin >> author;
	cin >> publishing;
	/* 
	对于整型浮点型这种数据类型, 还是确保输入错误的数据类型(如字符串时)能够顺利运行
	不过现在只能简单处理了, 输入字符串类型, price和amount会被默认置为0
	没有友好提示(提示输入错误的数据类型)
	*/
	cin >> price;
	if (!cin.good()) {
		cin.clear();
		cin.ignore(1000, '\n');
	}
	cin >> amount;
	if (!cin.good()) {
		cin.clear();
		cin.ignore(1000, '\n');
	}

	Book* pNewBook = new Book(title, author, publishing, price, amount);
	if (pNewBook != NULL) {
		bookShelf.push(pNewBook);
	}
}
bool Admin::removeBook(BookShelf<Book*>& bookShelf, unsigned int id) {
	return bookShelf.removeEleById(id);
}
bool Admin::removeBook(BookShelf<Book*>& bookShelf, string title) {
	return bookShelf.removeEleByTitle(title);
}
void Admin::setBook(BookShelf<Book*>& bookShelf, unsigned int id) {
	Book* pBook = bookShelf.getEleById(id);
	if (pBook) {
		string title;
		string author;
		string publishing;
		double price;
		unsigned int amount;

		cout << "原书名: " << pBook->getTitle() << endl;
		cout << "请输入书名: ";
		cin >> title;
		cout << endl;

		cout << "原作者: " << pBook->getAuthor() << endl;
		cout << "请输入作者: ";
		cin >> author;
		cout << endl;

		cout << "原出版社: " << pBook->getPublishing() << endl;
		cout << "请输入出版社: ";
		cin >> publishing;
		cout << endl;

		cout << "原价格: " << pBook->getPrice() << endl;
		cout << "请输入价格: ";
		cin >> price;
		cout << endl;

		cout << "原数量: " << pBook->getAmount() << endl;
		cout << "请输入数量: ";
		cin >> amount;
		cout << endl;

		pBook->init(title, author, publishing, price, amount);
	}
	// 这里最好不要打印, 而是抛出异常, 让上层处理
	else {
		cout << "id为" << id << "的书不存在" << endl;
	}
}
void Admin::setBook(BookShelf<Book*>& bookShelf, string title) {
	Book* pBook = bookShelf.getEleByTitle(title);
	if (pBook) {
		string title;
		string author;
		string publishing;
		double price;
		unsigned int amount;

		cout << "原书名: " << pBook->getTitle() << endl;
		cout << "请输入书名: ";
		cin >> title;
		cout << endl;

		cout << "原作者: " << pBook->getAuthor() << endl;
		cout << "请输入作者: ";
		cin >> author;
		cout << endl;

		cout << "原出版社: " << pBook->getPublishing() << endl;
		cout << "请输入出版社: ";
		cin >> publishing;
		cout << endl;

		cout << "原价格: " << pBook->getPrice() << endl;
		cout << "请输入价格: ";
		cin >> price;
		cin.clear();
		cin.ignore(1000, '\n');
		cout << endl;

		cout << "原数量: " << pBook->getAmount() << endl;
		cout << "请输入数量: ";
		cin >> amount;
		cin.clear();
		cin.ignore(1000, '\n');
		cout << endl;

		pBook->init(title, author, publishing, price, amount);
	}
	else {
		cout << "书名为" << title << "的书不存在" << endl;
	}
}
void Admin::display() const{
	cout << "====== 管理员信息" << id << " ======" << endl;
	cout << "姓名: " << name << endl;
	cout << "账号: " << account << endl;
	cout << endl;
}
string Admin::getName() const{
	return name;
}
string Admin::getAccount() const{
	return account;
}
bool Admin::passwordVaild(string password) const {
	return !password.compare(this->password);
}
//bool Admin::hasInit() {
//	return _isInit;
//}

// 重载<<插入运算符和Admin类
std::ostream& operator<< (std::ostream& out, Admin& admin) {
	out << "====== 管理员信息" << admin.id << " ======" << endl;
	out << "姓名: " << admin.name << endl;
	out << "账号: " << admin.account << endl;
	out << endl;
	return out;
}