#include "ProcessInvoke.h"

ProcessInvoke::ProcessInvoke(std::vector<Process>&& ps) noexcept
{
	this->ps = std::move(ps);

	// 计算时间从何开始，到哪结束
	for (auto p : this->ps) {
		sumServerTime += p.serverTime;

		if (p.arriveAtTime < minArriveTime) {
			minArriveTime = p.arriveAtTime;
		}
	}
	// 用于输出调度过程的"队列"
	invokeNameQueue = new std::vector<std::string>(sumServerTime);
}

ProcessInvoke::~ProcessInvoke() {
	delete invokeNameQueue;
}

void ProcessInvoke::SJP()
{
	Reset();

	int currentExecuteIx = -1;
	// 遍历所有时间单元
	for (size_t time = minArriveTime; time < minArriveTime + sumServerTime; time++) {
		size_t minServerTime = std::numeric_limits<size_t>::max();
		int minServerTimeIx = -1;

		// 确定当前时间单元由哪个进程执行
		for (size_t j = 0; j < ps.size(); j++) {
			Process& p = ps[j];
			// 由于是非抢占式，此时有进程执行
			if (currentExecuteIx != -1) {
				minServerTimeIx = currentExecuteIx;
				break;
			}

			// 如果已完成或未到达
			if (time < p.arriveAtTime || time >= p.completeTime) {
				continue;
			}

			// 短进程的判断依据：谁的服务时间短
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

	string name = "短进程优先";
	_PrintInfo(name);
}

void ProcessInvoke::FCFS()
{
	Reset();

	// 遍历所有时间单元
	for (size_t time = minArriveTime; time < minArriveTime + sumServerTime; time++) {
		size_t earliestArrvieIx = -1;
		size_t earliestArrvieTime = std::numeric_limits<size_t>::max();
		
		// 确定当前时间单元由哪个进程执行
		for (size_t j = 0; j < ps.size(); j++) {
			Process& p = ps[j];

			// 如果已完成或未到达
			if (time < p.arriveAtTime || time >= p.completeTime) {
				continue;
			}

			// 先来先服务的判断依据：谁的到达时间最早
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

	string name = "先来先服务";
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

	string name = "时间片轮转(老进程优先的)";
	_PrintInfo(name);
	invokeQueue.makeEmpty();
}

void ProcessInvoke::Priority(bool allowRace)
{
	Reset();

	int currentExecuteIx = -1;
	// 遍历所有时间单元
	for (size_t time = minArriveTime; time < minArriveTime + sumServerTime; time++) {
		size_t maxPriority = std::numeric_limits<size_t>::min();
		int maxPriorityIx = -1;

		// 确定当前时间单元由哪个进程执行
		for (size_t j = 0; j < ps.size(); j++) {
			Process& p = ps[j];
			// 由于是非抢占式，此时有进程执行
			if (!allowRace && currentExecuteIx != -1) {
				maxPriorityIx = currentExecuteIx;
				break;
			}

			// 如果已完成或未到达
			if (time < p.arriveAtTime || time >= p.completeTime) {
				continue;
			}

			// 静态优先级的判断依据：谁的优先级高
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

	string name = allowRace ? "静态优先级(抢占)" : "静态优先级(非抢占)";
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

	cout << "算法名称: " << algorithmName << endl;
	cout << "进程名 到达时间 服务时间 开始时间 完成时间 周转时间 带权周转时间" << endl;

	float avgTurnOverTime = 0;
	float avgHasWeightTurnOverTime = 0;
	// 使用c_str()可以将string转换为c的字符
	for (auto& p : ps) {
		printf("%-6s %-8llu %-8llu %-8llu %-8llu %-8llu %-8.2f\n", \
			p.name.c_str(), p.arriveAtTime, p.serverTime, p.startTime, p.completeTime, p.turnOverTime, p.hasWeightTurnOverTime);
		avgTurnOverTime += p.turnOverTime;
		avgHasWeightTurnOverTime += p.hasWeightTurnOverTime;
	}

	avgTurnOverTime /= (float)(ps.size());
	avgHasWeightTurnOverTime /= (float)(ps.size());

	// 输出平均值
	cout << "平均周转时间为: " << avgTurnOverTime << endl;
	cout << "平均带权周转时间为: " << avgHasWeightTurnOverTime << endl;

	// 输出调用队列
	ostringstream infoStr;
	infoStr << "调度队列为: ";
	infoStr << (*invokeNameQueue)[0];

	for (int i = 1; i < (*invokeNameQueue).size(); i++) {
		infoStr << "-" << (*invokeNameQueue)[i];
	}
	cout << infoStr.str() << endl << endl;
}
