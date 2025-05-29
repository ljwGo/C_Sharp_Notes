#include "dailyGoods.h"

DailyGoods::DailyGoods() :Goods() {
	;
}
DailyGoods::DailyGoods(string name, unsigned int quantity) : Goods(name, quantity) {
	;
}
void DailyGoods::showMe() {
	cout << "<=====日用品=====>" << endl;
	cout << "商品名称: " << name << endl;
	cout << "商品数量: " << quantity << endl;
	cout << endl;
}
istream& operator >> (istream& in, DailyGoods& dailyGoods) {
	string name;
	unsigned int quantity;
	in >> name >> quantity;

	if (!in.good()) {
		throw new DataFormat("文件流或标准输入流中的数据格式发生错误");
	}

	if (name == "") {
		throw new StrIsEmpty("名称不能为空");
	}

	dailyGoods.init(name, quantity);
	return in;
}
ostream& operator << (ostream& out, DailyGoods& dailyGoods) {
	out << dailyGoods.name << " " << dailyGoods.quantity << endl;
	return out;
}
