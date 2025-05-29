#include "electricalAppliance.h"
#include "error.h"

ElectricalAppliance::ElectricalAppliance(): Goods() {
	color = "";
}
ElectricalAppliance::ElectricalAppliance(string name, unsigned int quantity, string color) : Goods(name, quantity) {
	this->color = color;
}
void ElectricalAppliance::init(string name, unsigned int quantity, string color) {
	// ���ø���ĳ�ʼ������
	Goods::init(name, quantity);
	this->color = color;
}
void ElectricalAppliance::showMe() {
	cout << "<=====���õ���=====>" << endl;
	cout << "��Ʒ����: " << name << endl;
	cout << "��Ʒ����: " << quantity << endl;
	cout << "��Ʒ��ɫ: " << color << endl;
	cout << endl;
}
istream& operator >> (istream& in, ElectricalAppliance& EA) {
	string name;
	string color;
	unsigned int quantity;
	in >> name >> quantity >> color;

	if (!in.good()) {
		throw new DataFormat("�ļ������׼�������е����ݸ�ʽ��������");
	}

	if (name == "" || color == "") {
		throw new StrIsEmpty("���ƻ�����ɫ����Ϊ��");
	}

	EA.init(name, quantity, color);
	return in;
}
ostream& operator << (ostream& out, ElectricalAppliance& EA) {
	out << EA.name << " " << EA.quantity
		<< EA.color << endl;
	return out;
}
