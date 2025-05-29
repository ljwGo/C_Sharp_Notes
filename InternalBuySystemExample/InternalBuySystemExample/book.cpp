#include "book.h"
#include "order.h"
#include <iostream>
using namespace std;

unsigned int Book::staticBookId = 1;

// �޲ι��캯��
//Book::Book() {
//	amount = 0;
//	price = 0;
//	publishing = "";
//	title = "";
//	author = "";
//	id = Book::staticBookId++;
//	//_isInit = false;
//}
Book::Book(string title, string author, string publishing, double price, unsigned int amount) {
	if (title == "") {
		cout << "��������Ϊ��!!!" << endl;
		throw 0;
	}
	this->amount = amount;
	this->price = price;
	this->publishing = publishing;
	this->title = title;
	this->author = author;
	id = Book::staticBookId++;
	//_isInit = true;
}
void Book::display() const  {
	cout << "====== ͼ����ϢΪ ======" << endl;
	cout << "���Ϊ: " << id << endl;
	cout << "����Ϊ: " << title << endl;
	cout << "�۸�Ϊ: " << price << endl;
	cout << "������Ϊ: " << publishing << endl;
	cout << "����Ϊ: " << amount << endl;
	cout << endl;
}
void Book::setAmount(unsigned int amount) {
	this->amount = amount;
}
void Book::decreaseBook(unsigned int n) {
	amount = amount < n  ? 0 : amount - n;
}
void Book::setPrice(double price) {
	this->price = price;
}
void Book::setPublishing(string publishing) {
	this->publishing = publishing;
}
void Book::setTitle(string title) {
	this->title = title;
}
void Book::setAuthor(string author) {
	this->author = author;
}
void Book::init(string title, string author, string publishing, double price, unsigned int amount) {
	this->title = title;
	this->price = price;
	this->publishing = publishing;
	this->amount = amount;
	this->author = author;
	//_isInit = true;
}
//bool Book::operator< (const Book& book) const {
//	return this->id < book.id;
//}
//bool Book::operator== (const Book& book) const {
	// ֻ����Ҫ�����Ա���Ϊ��ͬ������
//	return book.getId() == this->id &&
//		book.getPrice() == this->price &&
//		book.getTitle() == this->title;
//}
string Book::getTitle() const {
	return title;
}
string Book::getPublishing() const {
	return publishing;
}
string Book::getAuthor() const {
	return author;
};
double Book::getPrice() const {
	return price;
}
unsigned int Book::getId() const{
	return id;
}
unsigned int Book::getAmount() const {
	return amount;
}
//bool Book::hasInit() {
//	return _isInit;
//}

// ����<<
std::ostream& operator<< (std::ostream& out, Book& book) {
	out << "====== ͼ�� " << book.id << " ======" << endl;
	out << "����Ϊ: " << book.title << endl;
	out << "�۸�Ϊ: " << book.price << endl;
	out << "������Ϊ: " << book.publishing << endl;
	out << "����Ϊ: " << book.amount << endl;
	out << endl;
	return out;
}