#include <iostream>
#include "admin.h"
#include "book.h"
#include "bookShelf.h"
#include "adminGroup.h"


using namespace std;

unsigned int Admin::staticAdminId = 1; // ���þ�̬id��

// �޲ι��캯��
//Admin::Admin() {
//	name = "";
//	account = "";
//	password = "";
//	id = Admin::staticAdminId++;
//	//_isInit = false;
//}
Admin::Admin(string name, string account, string password, AdminGroup<Admin*> &adminGroup) {
	if (account == "") {
		cout << "�˺Ų���Ϊ��!!!" << endl;
		throw 0;
	}
	if (adminGroup.isAccountExist(account)){
		cout << "�˺��Ѿ�������!!!" << endl;
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
	
	cout << "�������������, ����, ������, �۸�, ���:" << endl;
	cin >> title;
	cin >> author;
	cin >> publishing;
	/* 
	�������͸�����������������, ����ȷ������������������(���ַ���ʱ)�ܹ�˳������
	��������ֻ�ܼ򵥴�����, �����ַ�������, price��amount�ᱻĬ����Ϊ0
	û���Ѻ���ʾ(��ʾ����������������)
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

		cout << "ԭ����: " << pBook->getTitle() << endl;
		cout << "����������: ";
		cin >> title;
		cout << endl;

		cout << "ԭ����: " << pBook->getAuthor() << endl;
		cout << "����������: ";
		cin >> author;
		cout << endl;

		cout << "ԭ������: " << pBook->getPublishing() << endl;
		cout << "�����������: ";
		cin >> publishing;
		cout << endl;

		cout << "ԭ�۸�: " << pBook->getPrice() << endl;
		cout << "������۸�: ";
		cin >> price;
		cout << endl;

		cout << "ԭ����: " << pBook->getAmount() << endl;
		cout << "����������: ";
		cin >> amount;
		cout << endl;

		pBook->init(title, author, publishing, price, amount);
	}
	// ������ò�Ҫ��ӡ, �����׳��쳣, ���ϲ㴦��
	else {
		cout << "idΪ" << id << "���鲻����" << endl;
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

		cout << "ԭ����: " << pBook->getTitle() << endl;
		cout << "����������: ";
		cin >> title;
		cout << endl;

		cout << "ԭ����: " << pBook->getAuthor() << endl;
		cout << "����������: ";
		cin >> author;
		cout << endl;

		cout << "ԭ������: " << pBook->getPublishing() << endl;
		cout << "�����������: ";
		cin >> publishing;
		cout << endl;

		cout << "ԭ�۸�: " << pBook->getPrice() << endl;
		cout << "������۸�: ";
		cin >> price;
		cin.clear();
		cin.ignore(1000, '\n');
		cout << endl;

		cout << "ԭ����: " << pBook->getAmount() << endl;
		cout << "����������: ";
		cin >> amount;
		cin.clear();
		cin.ignore(1000, '\n');
		cout << endl;

		pBook->init(title, author, publishing, price, amount);
	}
	else {
		cout << "����Ϊ" << title << "���鲻����" << endl;
	}
}
void Admin::display() const{
	cout << "====== ����Ա��Ϣ" << id << " ======" << endl;
	cout << "����: " << name << endl;
	cout << "�˺�: " << account << endl;
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

// ����<<�����������Admin��
std::ostream& operator<< (std::ostream& out, Admin& admin) {
	out << "====== ����Ա��Ϣ" << admin.id << " ======" << endl;
	out << "����: " << admin.name << endl;
	out << "�˺�: " << admin.account << endl;
	out << endl;
	return out;
}