#include "Paper.h"
#include "Random.h"
#include <sstream>

Paper::Paper(int topicAmount, int resMinValue, int resMaxValue, std::vector<Operator*> operators)
{
	this->operators = operators;

	for (int i = 0; i < topicAmount; i++) {
		topics.emplace_back(GenerateOneTopic(resMinValue, resMaxValue));
	}
}

void Paper::ShowPaper() const
{
	for (int i = 0; i < topics.size(); i++) {
		cout << "第" << i + 1 << "道题: " << endl;
		cout << topics[i].content << endl;
		cout << "答案: " << topics[i].answer << endl << endl;
	}
}

TopicData Paper::GenerateOneTopic(int resMinValue, int resMaxValue)
{
	int result;
	// 得通过::名称空间访问符访问
	// 添加首个操作数, 比如"20"
	int initOperateNum = Random::Range(resMinValue, resMaxValue);
	operateNumQueue.EnQueue(initOperateNum);
	
	// 首次执行, 保证至少有两个操作数和一个操作符. 比如"20+10"
	GenerateNumAndSymbol(initOperateNum, resMinValue, resMaxValue, result);

	// 后续操作数和操作符以某个概率添加, 这里是0.5. 添加后可能为"(20+10)*3"
	while (Random::Happen(NEW_NUMBER_AND_SYMBOL_POSSIBLE)) {
		GenerateNumAndSymbol(result, resMinValue, resMaxValue, result);
	}

	TopicData newTopic;
	newTopic.content = GenerateContent();
	newTopic.answer = result;
	return newTopic;
}

bool Paper::GenerateNumAndSymbol(int initOperateNum, int resMinValue, int resMaxValue, int& result)
{
	int operateNum;
	char operateSymbol;
	int answer;

	bool vaild;
	// 记录一个"用于生成操作符和操作数"方法是否被选过
	std::vector<bool> hasBeenChoiceOperator(operators.size());
	for (int i = 0; i < hasBeenChoiceOperator.size(); i++) {
		hasBeenChoiceOperator[i] = false;
	}

	do {
		int choiceIx = Random::Range(0, operators.size());
		// 如果某个方法已经被选过, 则重新选一个
		while (hasBeenChoiceOperator[choiceIx]) {
			choiceIx = Random::Range(0, operators.size());
		}
		hasBeenChoiceOperator[choiceIx] = true;

		// 生成的操作数是否合法. 比如10 + 12."+"和"12"是合法的; 但对于100 + 0. "+"和"0"是无意义的. 
		// 意味着此时加法无论如何也找不到一个合理的算数. 就换用其它算法, 比如减法.
		vaild = operators[choiceIx]->GenerateOperateNum(initOperateNum, resMinValue, resMaxValue, operateNum, operateSymbol, answer);
	} while (!vaild);

	// 合法操作数和操作符入列
	operateSymbolQueue.EnQueue(operateSymbol);
	operateNumQueue.EnQueue(operateNum);
	result = answer;
	return true;
}

// 自己对算法考虑不周, 忘记了乘除法优先级比加减法高.
// 我在考虑问题时, 想当然的认为符号优先级是从左往右了
string Paper::GenerateContent()
{
	int num;
	char symbol;
	char previouSymbol = '\b';

	ostringstream content;
	ostringstream leftBracket;
	operateNumQueue.DeQueue(num);
	content << num;

	// 补丁是这样的, 如果出现-,+号在*,/前边, 那么添加()号, 保证优先级从左往右
	while (operateNumQueue.DeQueue(num) && operateSymbolQueue.DeQueue(symbol)) {
		if ((symbol == '*' || symbol == '/')
			&& (previouSymbol == '+' || previouSymbol == '-')) {
			content << ')';
			leftBracket << '(';
		}
		content << " " << symbol << " " << num;

		previouSymbol = symbol;
	}

	return leftBracket.str() + content.str();
}
