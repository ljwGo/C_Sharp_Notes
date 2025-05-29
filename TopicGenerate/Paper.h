#pragma once
#include <vector>
#include "Operator.h"
#include "TopicData.h"
#include "LinkedQueue.h"
#include "Random.h"

#define NEW_NUMBER_AND_SYMBOL_POSSIBLE 0.6

inline LinkedQueue<int> operateNumQueue;
inline LinkedQueue<char> operateSymbolQueue;
inline std::vector<TopicData> topics;

class Paper
{
public:
	Paper(int topicAmount, int resMinValue, int resMaxValue, std::vector<Operator *> operators);
	void ShowPaper() const;
private:
	TopicData GenerateOneTopic(int resMinValue, int resMaxValue);
	bool GenerateNumAndSymbol(int initOperateNum, int resMinValue, int resMaxValue, int& result);
	string GenerateContent();
	std::vector<Operator*> operators;
};

