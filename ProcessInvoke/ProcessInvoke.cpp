#include "ProcessInvoke.h"

ProcessInvoke::ProcessInvoke(std::vector<Process>&& ps) noexcept
{
	this->ps = std::move(ps);

	// ����ʱ��Ӻο�ʼ�����Ľ���
	for (auto p : this->ps) {
		sumServerTime += p.serverTime;

		if (p.arriveAtTime < minArriveTime) {
			minArriveTime = p.arriveAtTime;
		}
	}
	// ����������ȹ��̵�"����"
	invokeNameQueue = new std::vector<std::string>(sumServerTime);
}

ProcessInvoke::~ProcessInvoke() {
	delete invokeNameQueue;
}

void ProcessInvoke::SJP()
{
	Reset();

	int currentExecuteIx = -1;
	// ��������ʱ�䵥Ԫ
	for (size_t time = minArriveTime; time < minArriveTime + sumServerTime; time++) {
		size_t minServerTime = std::numeric_limits<size_t>::max();
		int minServerTimeIx = -1;

		// ȷ����ǰʱ�䵥Ԫ���ĸ�����ִ��
		for (size_t j = 0; j < ps.size(); j++) {
			Process& p = ps[j];
			// �����Ƿ���ռʽ����ʱ�н���ִ��
			if (currentExecuteIx != -1) {
				minServerTimeIx = currentExecuteIx;
				break;
			}

			// �������ɻ�δ����
			if (time < p.arriveAtTime || time >= p.completeTime) {
				continue;
			}

			// �̽��̵��ж����ݣ�˭�ķ���ʱ���
			if (p.serverTime < minServerTime) {
				minServerTime = p.serverTime;
				minServerTimeIx = j;
			}
		}
		currentExecuteIx = minServerTimeIx;

		Process& p = ps[currentExecuteIx];

		(*invokeNameQueue)[time - minArriveTime] = p.name;

		p.iterServerTime--;
		if (p.iterServerTime == 0) {
			currentExecuteIx = -1;
			p.completeTime = time + 1;
			p.startTime = p.completeTime - p.serverTime;
			p.turnOverTime = p.completeTime - p.arriveAtTime;
			p.hasWeightTurnOverTime = (float)p.turnOverTime / p.serverTime;
		}
	}

	string name = "�̽�������";
	_PrintInfo(name);
}

void ProcessInvoke::FCFS()
{
	Reset();

	// ��������ʱ�䵥Ԫ
	for (size_t time = minArriveTime; time < minArriveTime + sumServerTime; time++) {
		size_t earliestArrvieIx = -1;
		size_t earliestArrvieTime = std::numeric_limits<size_t>::max();
		
		// ȷ����ǰʱ�䵥Ԫ���ĸ�����ִ��
		for (size_t j = 0; j < ps.size(); j++) {
			Process& p = ps[j];

			// �������ɻ�δ����
			if (time < p.arriveAtTime || time >= p.completeTime) {
				continue;
			}

			// �����ȷ�����ж����ݣ�˭�ĵ���ʱ������
			if (p.arriveAtTime < earliestArrvieTime) {
				earliestArrvieTime = p.arriveAtTime;
				earliestArrvieIx = j;
			}
		}

		Process& p = ps[earliestArrvieIx];

		(* invokeNameQueue)[time - minArriveTime] = p.name;

		p.iterServerTime--;
		if (p.iterServerTime == 0) {
			p.completeTime = time + 1;
			p.startTime = p.completeTime - p.serverTime;
			p.turnOverTime = p.completeTime - p.arriveAtTime;
			p.hasWeightTurnOverTime = (float)p.turnOverTime / p.serverTime;
		}
	}

	string name = "�����ȷ���";
	_PrintInfo(name);
}

// Old process has high priority.
void ProcessInvoke::Timestamp(size_t timeSize)
{
	Reset();

	size_t remainTimeInfinitesimal = 0;
	Process* executeProcessPtr = nullptr;

	for (size_t time = minArriveTime; time < sumServerTime; time++) {
		// Which process will arrive
		for (auto& p : ps) {
			if (p.arriveAtTime == time) {
				invokeQueue.EnQueue(&p);
			}
		}
		
		// Find which process will be execute!
		for (size_t i = 0; i < ps.size(); i++) {
			// Current process not arrive or has been completed.
			if (time < ps[i].arriveAtTime || time >= ps[i].completeTime) {
				continue;
			}
			// If time infinitesimal is not zero. Execute current process
			if (remainTimeInfinitesimal != 0) {
				break;
			}
			// Find next execute process in queue head
			invokeQueue.DeQueue(executeProcessPtr);
			remainTimeInfinitesimal = timeSize;
		}
	
		if (executeProcessPtr == nullptr) {
			throw new string("ptr is nullptr");
		}

		Process& p = *executeProcessPtr;
		(*invokeNameQueue)[time - minArriveTime] = p.name;

		p.iterServerTime--;
		remainTimeInfinitesimal--;

		if (p.iterServerTime == 0){
			remainTimeInfinitesimal = 0;
			
			p.completeTime = time + 1;
			p.startTime = p.completeTime - p.serverTime;
			p.turnOverTime = p.completeTime - p.arriveAtTime;
			p.hasWeightTurnOverTime = (float)p.turnOverTime / p.serverTime;
		}
		else if (remainTimeInfinitesimal == 0){
			invokeQueue.EnQueue(&p);
		}
	}

	string name = "ʱ��Ƭ��ת(�Ͻ������ȵ�)";
	_PrintInfo(name);
	invokeQueue.makeEmpty();
}

void ProcessInvoke::Priority(bool allowRace)
{
	Reset();

	int currentExecuteIx = -1;
	// ��������ʱ�䵥Ԫ
	for (size_t time = minArriveTime; time < minArriveTime + sumServerTime; time++) {
		size_t maxPriority = std::numeric_limits<size_t>::min();
		int maxPriorityIx = -1;

		// ȷ����ǰʱ�䵥Ԫ���ĸ�����ִ��
		for (size_t j = 0; j < ps.size(); j++) {
			Process& p = ps[j];
			// �����Ƿ���ռʽ����ʱ�н���ִ��
			if (!allowRace && currentExecuteIx != -1) {
				maxPriorityIx = currentExecuteIx;
				break;
			}

			// �������ɻ�δ����
			if (time < p.arriveAtTime || time >= p.completeTime) {
				continue;
			}

			// ��̬���ȼ����ж����ݣ�˭�����ȼ���
			if (p.priority > maxPriority) {
				maxPriority = p.priority;
				maxPriorityIx = j;
			}
		}
		currentExecuteIx = maxPriorityIx;

		Process& p = ps[currentExecuteIx];

		(*invokeNameQueue)[time - minArriveTime] = p.name;

		p.iterServerTime--;
		if (p.iterServerTime == 0) {
			currentExecuteIx = -1;
			p.completeTime = time + 1;
			p.startTime = p.completeTime - p.serverTime;
			p.turnOverTime = p.completeTime - p.arriveAtTime;
			p.hasWeightTurnOverTime = (float)p.turnOverTime / p.serverTime;
		}
	}

	string name = allowRace ? "��̬���ȼ�(��ռ)" : "��̬���ȼ�(����ռ)";
	_PrintInfo(name);
}

void ProcessInvoke::Reset()
{
	for (auto& p : ps) {
		p.Reset();
	}
}

void ProcessInvoke::_PrintInfo(string& algorithmName)
{
	using namespace std;

	cout << "�㷨����: " << algorithmName << endl;
	cout << "������ ����ʱ�� ����ʱ�� ��ʼʱ�� ���ʱ�� ��תʱ�� ��Ȩ��תʱ��" << endl;

	float avgTurnOverTime = 0;
	float avgHasWeightTurnOverTime = 0;
	// ʹ��c_str()���Խ�stringת��Ϊc���ַ�
	for (auto& p : ps) {
		printf("%-6s %-8llu %-8llu %-8llu %-8llu %-8llu %-8.2f\n", \
			p.name.c_str(), p.arriveAtTime, p.serverTime, p.startTime, p.completeTime, p.turnOverTime, p.hasWeightTurnOverTime);
		avgTurnOverTime += p.turnOverTime;
		avgHasWeightTurnOverTime += p.hasWeightTurnOverTime;
	}

	avgTurnOverTime /= (float)(ps.size());
	avgHasWeightTurnOverTime /= (float)(ps.size());

	// ���ƽ��ֵ
	cout << "ƽ����תʱ��Ϊ: " << avgTurnOverTime << endl;
	cout << "ƽ����Ȩ��תʱ��Ϊ: " << avgHasWeightTurnOverTime << endl;

	// ������ö���
	ostringstream infoStr;
	infoStr << "���ȶ���Ϊ: ";
	infoStr << (*invokeNameQueue)[0];

	for (int i = 1; i < (*invokeNameQueue).size(); i++) {
		infoStr << "-" << (*invokeNameQueue)[i];
	}
	cout << infoStr.str() << endl << endl;
}
