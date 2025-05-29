#pragma once
#include "Operator.h"

class SubtractorGenerate : public Operator {
public:
	bool GenerateOperateNum(int left, int resMinValue, int resMaxValue, int& operateNum, char& operateSymbol, int& result);
};