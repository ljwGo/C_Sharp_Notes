#include "layfolk.h"

LayFolk::LayFolk(
	string name,
	string account,
	string password,
	string address,
	CustomerGroup<Buyer*>& customerGroup,
	double money)
	:Buyer(name, account, password, address, money, customerGroup) {
	;
}

void LayFolk::setPayMoney(double orderPayMoney) {
	payMoney = orderPayMoney;
}

void LayFolk::display() {
	cout << "我是普通顾客, 我不配拥有**" << endl;
	cout << "姓名: " << name << endl;
	cout << "编号: " << id << endl;
	cout << endl;
}