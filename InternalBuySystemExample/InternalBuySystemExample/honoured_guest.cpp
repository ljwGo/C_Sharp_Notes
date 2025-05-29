#include "honoured_guest.h"

Honoured_Guest::Honoured_Guest(
	string name,
	string account,
	string password,
	string address,
	CustomerGroup<Buyer*>& customerGroup,
	double money,
	double discount_rate)
	:Buyer(name, account, password, address, money, customerGroup)
	{
	this->discount_rate = discount_rate;
}

void Honoured_Guest::setPayMoney(double orderPayMoney) {
	payMoney = (1 - discount_rate) * orderPayMoney;
}

void Honoured_Guest::display() {
	cout << "****** �������ĸ߼�vip ******" << endl;
	cout << "����: " << name << endl;
	cout << "���: " << id << endl;
	cout << "������" << discount_rate << "���ۿ���" << endl;
	cout << endl;
}
