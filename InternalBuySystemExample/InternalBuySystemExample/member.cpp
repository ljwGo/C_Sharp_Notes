#include "member.h"

Member::Member(
	string name,
	string account,
	string password,
	string address,
	CustomerGroup<Buyer*>& customerGroup,
	double money,
	unsigned int leaguer_grade)
	:Buyer(name, account, password, address, money, customerGroup)
{
	// 等级可以使用枚举类型代替, 有空改
	this->leaguer_grade = leaguer_grade;
}

void Member::setPayMoney(double orderPayMoney) {
	switch (leaguer_grade) {
	case 1u:
		payMoney = 0.95 * orderPayMoney; break;
	case 2u:
		payMoney = 0.9 * orderPayMoney; break;
	case 3u:
		payMoney = 0.8 * orderPayMoney; break;
	default:
		payMoney = orderPayMoney; break;
	}
}

void Member::display() {
	cout << "### 我是等级为" << leaguer_grade << "的普通vip ###" << endl;
	cout << "姓名: " << name << endl;
	cout << "编号: " << id << endl;
	cout << endl;
}