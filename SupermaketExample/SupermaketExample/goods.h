#pragma once
#include <iostream>
#include <string>

using namespace std;

class Goods {
public:
	Goods();
	Goods(string name, unsigned int quantity);
	void decrease(unsigned int less);
	void increase(unsigned int more);
	string getName();
	unsigned int getId();
	unsigned int getQuantity();
	virtual void init(string name, unsigned int quantity);
	virtual void showMe()=0;
protected:
	static unsigned int staticGoodId;
	unsigned int id;
	unsigned int quantity;
	string name;
};
