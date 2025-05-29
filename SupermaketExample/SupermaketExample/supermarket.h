#pragma once
#include "error.h"
#include "food.h"
#include "dailyGoods.h"
#include "electricalAppliance.h"
#include "container.h"

class Supermarket {
	friend class Model;
public:
	Supermarket();
	void add();
	void showClassify();
	void sale();
	void search();
private:
	// ������̬��ų�Ա
	static unsigned int staticId;
	// ���
	unsigned int id;
	Container<Goods*> foodCon;
	Container<Goods*> dailyGoodsCon;
	Container<Goods*> EACon;
};
