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
	cout << "������ͨ�˿�, �Ҳ���ӵ��**" << endl;
	cout << "����: " << name << endl;
	cout << "���: " << id << endl;
	cout << endl;
}