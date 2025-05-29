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
	// 自增静态编号成员
	static unsigned int staticId;
	// 编号
	unsigned int id;
	Container<Goods*> foodCon;
	Container<Goods*> dailyGoodsCon;
	Container<Goods*> EACon;
};
