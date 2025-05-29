#pragma once
#include "goods.h"
#include <string>
#include "error.h"

class DailyGoods: public Goods {
public:
	DailyGoods();
	DailyGoods(string name, unsigned int quantity);
	void showMe();
	friend istream& operator >> (istream& in, DailyGoods& dailyGoods);
	friend ostream& operator << (ostream& out, DailyGoods& dailyGoods);
};