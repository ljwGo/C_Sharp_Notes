#include "food.h"
#include "error.h"

// 保质期时间结构体
typedef struct TimeLimit {
	TimeLimit(unsigned int year, unsigned int month, unsigned int day) {
		if (month >= 12 ) {
			throw new NumExceedLimit("月份的范围是0~11.");
		}
		if (day >= 31) {
			throw new NumExceedLimit("日期范围是0~30.");
		}

		this->year = year;
		this->month = month;
		this->day = day;
	}

	unsigned int year;
	unsigned int month;
	unsigned int day;
} TimeLimit;

Food::Food():Goods() {
	timeLimit = new TimeLimit(
		Food::defaultYear, 
		Food::defaultMonth, 
		Food::defaultDay);
}
Food::Food(string name,
	unsigned int quantity,
	unsigned int year,
	unsigned int month,
	unsigned int day)
	:Goods(name, quantity) {
	timeLimit = new TimeLimit(year, month, day);
}
Food::~Food() {
	delete timeLimit;
}
void Food::init(string name,
	unsigned int quantity,
	unsigned int year,
	unsigned int month,
	unsigned int day) {
	Goods::init(name, quantity);
	timeLimit = new TimeLimit(year, month, day);
}
void Food::showMe() {
	cout << "<=====食品=====>" << endl;
	cout << "商品名称: " << name << endl;
	cout << "商品数量: " << quantity << endl;
	cout << "商品保质期: " << timeLimit->year << "年"
		<< timeLimit->month << "月"
		<< timeLimit->day << "天";
	cout << endl;
}
istream& operator >> (istream& in, Food& food) {
	string name;
	unsigned int quantity, year, month, day;
	in >> name >> quantity >> year >> month >> day;

	if (!in.good()) {
		throw new DataFormat("文件流或标准输入流中的数据格式发生错误");
	}

	if (name == "") {
		throw new StrIsEmpty("名称不能为空");
	}

	food.init(name, quantity, year, month, day);
	return in;
}
ostream& operator << (ostream& out, Food& food) {
	out << food.name << " " << food.quantity << " "
		<< food.timeLimit->year << " " << food.timeLimit->month << " "
		<< food.timeLimit->day << endl;
	return out;
}

