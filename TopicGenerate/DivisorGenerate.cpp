#include "DivisorGenerate.h"

bool DivisorGenerate::GenerateOperateNum(int left, int resMinValue, int resMaxValue, int& operateNum, char& operateSymbol, int& result)
{
    static const int division[]{ 2, 3, 5, 7, 11, 13, 17, 19, 23 };  // ����
    for (int i = 0; i < sizeof(division) / sizeof(int); i++) {
        // �ܹ�����
        if (left % division[i] == 0) {
            operateNum = division[i];
            result = left / division[i];
            operateSymbol = '/';
            return true;
        }
    }
    return false;
}
