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
	tables.clear(); // ���map�е��鼮
	orderPrice = 0;
	_isChange = false;
}
void Order::calcPrice() {
	// ����������ݷ����ı�
	if (_isChange) {
		orderPrice = 0;
		for (map<Book*, unsigned int>::iterator it = this->tables.begin(); it != this->tables.end(); it++) {
			orderPrice += it->first->getPrice() * it->second;
		}
		_isChange = false; 	// �ı䱻������, ��Ϊfalse
	}
}
void Order::showOrderInfo() {
	// �ȼ�����۸�
	calcPrice();
	// ��ӡ������Ϣ
	cout << "====== ������Ϣ ======" << endl;
	cout << "������: " << id << endl;
	cout << "�µ��߱��: " << buyerId << endl;

	cout << "�鼮��Ϣ:=============" << endl;
	for (map<Book*, unsigned int>::iterator it = tables.begin(); it != tables.end(); it++) {
		const Book* book = it->first;
		const unsigned int buyAmount = it->second;

		cout << "����: " << book->getTitle() << '\t';
		cout << "��ı��: " << book->getId()<< '\t';
		cout << "��ĵ���: " << book->getPrice() << '\t';
		cout << "����������: " << buyAmount << '\t';
		cout << "�����ܼ�: " << book->getPrice() * buyAmount << endl;
	}
	cout << "�ܼ۸�: " << orderPrice << endl;
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

	out << "====== ������Ϣ ======" << endl;
	out << "������: " << order.id << endl;
	out << "�µ��߱��: " << order.buyerId << endl;

	out << "�鼮��Ϣ:=============" << endl;
	for (map<Book*, unsigned int>::iterator it = order.tables.begin(); it != order.tables.end(); it++) {
		const Book* pBook = it->first;
		const unsigned int buyAmount = it->second;

		out << "����: " << pBook->getTitle() << '\t';
		out << "��ı��: " << pBook->getId() << '\t';
		out << "��ĵ���: " << pBook->getPrice() << '\t';
		out << "����������: " << buyAmount << '\t';
		out << "�����ܼ�: " << pBook->getPrice() * buyAmount << '\t';
	}
	out << "�ܼ۸�: " << endl;
	out << endl;
	return out;
}
map<Book*, unsigned int>::iterator Order::begin() {
	return tables.begin();
}
map<Book*, unsigned int>::iterator Order::end() {
	return tables.end();
}
