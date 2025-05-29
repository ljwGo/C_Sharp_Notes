#pragma once
#include "Random.h"

class Operator
{
public:
	virtual bool GenerateOperateNum(int left, int resMinValue, int resMaxValue, int& operateNum, char& operateSymbol, int& result)=0;
};

