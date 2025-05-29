#include "food.h"
#include "error.h"

// ������ʱ��ṹ��
typedef struct TimeLimit {
	TimeLimit(unsigned int year, unsigned int month, unsigned int day) {
		if (month >= 12 ) {
			throw new NumExceedLimit("�·ݵķ�Χ��0~11.");
		}
		if (day >= 31) {
			throw new NumExceedLimit("���ڷ�Χ��0~30.");
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
	cout << "<=====ʳƷ=====>" << endl;
	cout << "��Ʒ����: " << name << endl;
	cout << "��Ʒ����: " << quantity << endl;
	cout << "��Ʒ������: " << timeLimit->year << "��"
		<< timeLimit->month << "��"
		<< timeLimit->day << "��";
	cout << endl;
}
istream& operator >> (istream& in, Food& food) {
	string name;
	unsigned int quantity, year, month, day;
	in >> name >> quantity >> year >> month >> day;

	if (!in.good()) {
		throw new DataFormat("�ļ������׼�������е����ݸ�ʽ��������");
	}

	if (name == "") {
		throw new StrIsEmpty("���Ʋ���Ϊ��");
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

