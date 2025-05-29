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
		cout << "��" << i + 1 << "����: " << endl;
		cout << topics[i].content << endl;
		cout << "��: " << topics[i].answer << endl << endl;
	}
}

TopicData Paper::GenerateOneTopic(int resMinValue, int resMaxValue)
{
	int result;
	// ��ͨ��::���ƿռ���ʷ�����
	// ����׸�������, ����"20"
	int initOperateNum = Random::Range(resMinValue, resMaxValue);
	operateNumQueue.EnQueue(initOperateNum);
	
	// �״�ִ��, ��֤������������������һ��������. ����"20+10"
	GenerateNumAndSymbol(initOperateNum, resMinValue, resMaxValue, result);

	// �����������Ͳ�������ĳ���������, ������0.5. ��Ӻ����Ϊ"(20+10)*3"
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
	// ��¼һ��"�������ɲ������Ͳ�����"�����Ƿ�ѡ��
	std::vector<bool> hasBeenChoiceOperator(operators.size());
	for (int i = 0; i < hasBeenChoiceOperator.size(); i++) {
		hasBeenChoiceOperator[i] = false;
	}

	do {
		int choiceIx = Random::Range(0, operators.size());
		// ���ĳ�������Ѿ���ѡ��, ������ѡһ��
		while (hasBeenChoiceOperator[choiceIx]) {
			choiceIx = Random::Range(0, operators.size());
		}
		hasBeenChoiceOperator[choiceIx] = true;

		// ���ɵĲ������Ƿ�Ϸ�. ����10 + 12."+"��"12"�ǺϷ���; ������100 + 0. "+"��"0"���������. 
		// ��ζ�Ŵ�ʱ�ӷ��������Ҳ�Ҳ���һ�����������. �ͻ��������㷨, �������.
		vaild = operators[choiceIx]->GenerateOperateNum(initOperateNum, resMinValue, resMaxValue, operateNum, operateSymbol, answer);
	} while (!vaild);

	// �Ϸ��������Ͳ���������
	operateSymbolQueue.EnQueue(operateSymbol);
	operateNumQueue.EnQueue(operateNum);
	result = answer;
	return true;
}

// �Լ����㷨���ǲ���, �����˳˳������ȼ��ȼӼ�����.
// ���ڿ�������ʱ, �뵱Ȼ����Ϊ�������ȼ��Ǵ���������
string Paper::GenerateContent()
{
	int num;
	char symbol;
	char previouSymbol = '\b';

	ostringstream content;
	ostringstream leftBracket;
	operateNumQueue.DeQueue(num);
	content << num;

	// ������������, �������-,+����*,/ǰ��, ��ô���()��, ��֤���ȼ���������
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
