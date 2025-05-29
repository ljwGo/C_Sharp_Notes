#pragma once
#include "goods.h"
#include <string>

using namespace std;

class ElectricalAppliance: public Goods {
public:
	ElectricalAppliance();
	ElectricalAppliance(string name, unsigned int quantity, string color);
	void init(string name, unsigned int quantity, string color);
	void showMe();
	friend istream& operator >> (istream& in, ElectricalAppliance& food);
	friend ostream& operator << (ostream& out, ElectricalAppliance& food);
protected:
	string color;
};