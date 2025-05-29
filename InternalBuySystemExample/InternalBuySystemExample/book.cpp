#include "book.h"
#include "order.h"
#include <iostream>
using namespace std;

unsigned int Book::staticBookId = 1;

// 无参构造函数
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
		cout << "书名不能为空!!!" << endl;
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
	cout << "====== 图书信息为 ======" << endl;
	cout << "编号为: " << id << endl;
	cout << "书名为: " << title << endl;
	cout << "价格为: " << price << endl;
	cout << "出版社为: " << publishing << endl;
	cout << "数量为: " << amount << endl;
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
	// 只有重要的属性被作为相同的依据
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

// 重载<<
std::ostream& operator<< (std::ostream& out, Book& book) {
	out << "====== 图书 " << book.id << " ======" << endl;
	out << "书名为: " << book.title << endl;
	out << "价格为: " << book.price << endl;
	out << "出版社为: " << book.publishing << endl;
	out << "数量为: " << book.amount << endl;
	out << endl;
	return out;
}