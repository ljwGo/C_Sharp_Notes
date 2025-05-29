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
	// �ȼ�����ʹ��ö�����ʹ���, �пո�
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
	cout << "### ���ǵȼ�Ϊ" << leaguer_grade << "����ͨvip ###" << endl;
	cout << "����: " << name << endl;
	cout << "���: " << id << endl;
	cout << endl;
}