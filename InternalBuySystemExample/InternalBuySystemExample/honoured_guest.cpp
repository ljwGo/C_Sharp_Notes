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
	cout << "****** 我是尊贵的高级vip ******" << endl;
	cout << "姓名: " << name << endl;
	cout << "编号: " << id << endl;
	cout << "我享有" << discount_rate << "的折扣率" << endl;
	cout << endl;
}
