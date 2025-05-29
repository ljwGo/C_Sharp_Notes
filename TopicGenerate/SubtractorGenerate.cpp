#include "SubtractorGenerate.h"

bool SubtractorGenerate::GenerateOperateNum(int left, int resMinValue, int resMaxValue, int& operateNum, char& operateSymbol, int& result)
{
	int subScope = left - resMinValue;

	if (subScope < 1) {
		return false;
	}

	int sub = Random::Range(1, subScope+1);

	operateSymbol = '-';
	operateNum = sub;
	result = left - sub;

	return true;
}
