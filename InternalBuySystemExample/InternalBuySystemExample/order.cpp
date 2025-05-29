#include "order.h"
#include <iostream>
#include <map>

using namespace std;

unsigned int Order::orderId = 1;

//Order::Order() {
//	id = Order::orderId++;
//	buyerId = 0;
//	orderPayMoney = 0;
//	_isChange = false;
//	//_isInit = false;
//}
Order::Order(unsigned int buyerId) {
	this->id = Order::orderId++;
	this->buyerId = buyerId;
	this->orderPrice = 0;
	_isChange = false;
	//_isInit = true;
}
void Order::reset() {
	tables.clear(); // 清空map中的书籍
	orderPrice = 0;
	_isChange = false;
}
void Order::calcPrice() {
	// 如果订单内容发生改变
	if (_isChange) {
		orderPrice = 0;
		for (map<Book*, unsigned int>::iterator it = this->tables.begin(); it != this->tables.end(); it++) {
			orderPrice += it->first->getPrice() * it->second;
		}
		_isChange = false; 	// 改变被处理了, 置为false
	}
}
void Order::showOrderInfo() {
	// 先计算出价格
	calcPrice();
	// 打印订单信息
	cout << "====== 订单信息 ======" << endl;
	cout << "订单号: " << id << endl;
	cout << "下单者编号: " << buyerId << endl;

	cout << "书籍信息:=============" << endl;
	for (map<Book*, unsigned int>::iterator it = tables.begin(); it != tables.end(); it++) {
		const Book* book = it->first;
		const unsigned int buyAmount = it->second;

		cout << "书名: " << book->getTitle() << '\t';
		cout << "书的编号: " << book->getId()<< '\t';
		cout << "书的单价: " << book->getPrice() << '\t';
		cout << "欲购买数量: " << buyAmount << '\t';
		cout << "子项总价: " << book->getPrice() * buyAmount << endl;
	}
	cout << "总价格: " << orderPrice << endl;
	cout << endl;
}
double Order::getOrderPrice() {
	calcPrice();
	return orderPrice;
}
unsigned int Order::getBuyerId() const {
	return buyerId;
}
void Order::addBook(Book* pBook, unsigned int amount) {
	if (amount != 0) {
		tables[pBook] += amount;
		_isChange = true;
	}
}
void Order::removeBook(Book* pBook, unsigned int amount) {
	if (amount != 0) {
		tables[pBook] = tables[pBook] < amount ? 0 : tables[pBook] - amount;
		_isChange = true;
	}
}
void Order::setBook(Book* pBook, unsigned int amount) {
	if (amount != pBook->getAmount()) {
		tables[pBook] = amount;
		_isChange = true;
	}
}
unsigned int Order::getBookAmount(Book* pBook){
	return tables[pBook];
}

std::ostream& operator<< (std::ostream& out, Order& order) {
	order.calcPrice();

	out << "====== 订单信息 ======" << endl;
	out << "订单号: " << order.id << endl;
	out << "下单者编号: " << order.buyerId << endl;

	out << "书籍信息:=============" << endl;
	for (map<Book*, unsigned int>::iterator it = order.tables.begin(); it != order.tables.end(); it++) {
		const Book* pBook = it->first;
		const unsigned int buyAmount = it->second;

		out << "书名: " << pBook->getTitle() << '\t';
		out << "书的编号: " << pBook->getId() << '\t';
		out << "书的单价: " << pBook->getPrice() << '\t';
		out << "欲购买数量: " << buyAmount << '\t';
		out << "子项总价: " << pBook->getPrice() * buyAmount << '\t';
	}
	out << "总价格: " << endl;
	out << endl;
	return out;
}
map<Book*, unsigned int>::iterator Order::begin() {
	return tables.begin();
}
map<Book*, unsigned int>::iterator Order::end() {
	return tables.end();
}
