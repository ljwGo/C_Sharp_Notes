#include "electricalAppliance.h"
#include "error.h"

ElectricalAppliance::ElectricalAppliance(): Goods() {
	color = "";
}
ElectricalAppliance::ElectricalAppliance(string name, unsigned int quantity, string color) : Goods(name, quantity) {
	this->color = color;
}
void ElectricalAppliance::init(string name, unsigned int quantity, string color) {
	// 调用父类的初始化方法
	Goods::init(name, quantity);
	this->color = color;
}
void ElectricalAppliance::showMe() {
	cout << "<=====家用电器=====>" << endl;
	cout << "商品名称: " << name << endl;
	cout << "商品数量: " << quantity << endl;
	cout << "商品颜色: " << color << endl;
	cout << endl;
}
istream& operator >> (istream& in, ElectricalAppliance& EA) {
	string name;
	string color;
	unsigned int quantity;
	in >> name >> quantity >> color;

	if (!in.good()) {
		throw new DataFormat("文件流或标准输入流中的数据格式发生错误");
	}

	if (name == "" || color == "") {
		throw new StrIsEmpty("名称或者颜色不能为空");
	}

	EA.init(name, quantity, color);
	return in;
}
ostream& operator << (ostream& out, ElectricalAppliance& EA) {
	out << EA.name << " " << EA.quantity
		<< EA.color << endl;
	return out;
}
