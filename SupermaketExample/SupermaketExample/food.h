#pragma once
#include "goods.h"
#include <string>

struct TimeLimit;

class Food : public Goods {
public:
	Food();
	Food(string name, unsigned int quantity, unsigned int year, unsigned int month, unsigned int day);
	~Food();
	void init(string name, unsigned int quantity, unsigned int year, unsigned int month, unsigned int day);
	void showMe();
	friend istream& operator >> (istream& in, Food& food);
	friend ostream& operator << (ostream& out, Food& food);
protected:
	// Ĭ�ϱ��������
	static const unsigned int defaultYear = 0;
	// Ĭ�ϱ������·�
	static const unsigned int defaultMonth = 1;
	// Ĭ�ϱ���������
	static const unsigned int defaultDay = 0;
	TimeLimit* timeLimit;
};