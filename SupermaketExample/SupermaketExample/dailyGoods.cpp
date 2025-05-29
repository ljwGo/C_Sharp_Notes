#include "dailyGoods.h"

DailyGoods::DailyGoods() :Goods() {
	;
}
DailyGoods::DailyGoods(string name, unsigned int quantity) : Goods(name, quantity) {
	;
}
void DailyGoods::showMe() {
	cout << "<=====����Ʒ=====>" << endl;
	cout << "��Ʒ����: " << name << endl;
	cout << "��Ʒ����: " << quantity << endl;
	cout << endl;
}
istream& operator >> (istream& in, DailyGoods& dailyGoods) {
	string name;
	unsigned int quantity;
	in >> name >> quantity;

	if (!in.good()) {
		throw new DataFormat("�ļ������׼�������е����ݸ�ʽ��������");
	}

	if (name == "") {
		throw new StrIsEmpty("���Ʋ���Ϊ��");
	}

	dailyGoods.init(name, quantity);
	return in;
}
ostream& operator << (ostream& out, DailyGoods& dailyGoods) {
	out << dailyGoods.name << " " << dailyGoods.quantity << endl;
	return out;
}
