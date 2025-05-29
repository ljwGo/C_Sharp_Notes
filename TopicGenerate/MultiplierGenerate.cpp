#include "MultiplierGenerate.h"

bool MultiplierGenerate::GenerateOperateNum(int left, int resMinValue, int resMaxValue, int& operateNum, char& operateSymbol, int& result)
{
	int multiScope = resMaxValue / left;
	if (multiScope < 2) {
		return false;
	}

	int multi = Random::Range(2, multiScope+1);
	
	operateSymbol = '*';
	operateNum = multi;
	result = left * multi;
	return true;
}
