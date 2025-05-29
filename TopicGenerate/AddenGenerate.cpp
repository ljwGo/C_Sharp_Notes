#include "AddenGenerate.h"

bool AddenGenerate::GenerateOperateNum(int left, int resMinValue, int resMaxValue, int& operateNum, char& operateSymbol, int& result)
{
	int addenScope = resMaxValue - left;

	if (addenScope < 1) {
		return false;
	}

	int adden = Random::Range(1, addenScope+1);

	operateSymbol = '+';
	operateNum = adden;
	result = left + adden;

	return true;
}
