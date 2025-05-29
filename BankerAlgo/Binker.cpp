#include "Binker.h"
#include <sstream>

Binker::Binker(source&& remainSource, std::vector<Process>&& ps) noexcept
{
	Timestamp initStamp = Timestamp(std::move(remainSource), std::move(ps));
	timestamps.push_back(std::move(initStamp));
}

void Binker::__PrintInfo() const
{
	using namespace std;
	ostringstream str;
	str << "n|  id  |   work   |   need   |   allo   |   workAndAllo   |\n";
	for (int i = 0; i < infos.size(); i++) {
		Info& info = infos[i];
		str << "|  P" << info.pIx << "  | "
			<< info.work << " |"
			<< info.need << " |"
			<< info.alloc << " |"
			<< info.workAndAlloc << " | \n";
	}

	str << "该时刻是安全的, 因为存在安全序列: ";
	for (int i = 0; i < infos.size(); i++) {
		str << "P" << infos[i].pIx << " ";
	}
	cout << str.str() << endl;
}

void Binker::SecurityDetect()
{
	std::cout << "\nT" << currentTimestampIx << "安全检测中......" << std::endl;
	if (timestamps[currentTimestampIx].SecurityDetect()) {
		__PrintInfo();
	}
	else {
		std::cout << "T" << currentTimestampIx << "时刻是不安全的, 因为找不到一个安全序列" << std::endl;
	}
}

bool Binker::GiveSource(size_t processIx, source&& toSource) noexcept
{
	Timestamp& currentStamp = timestamps[currentTimestampIx];
	Timestamp nextStamp;
	// if can allocate
	if (currentStamp.GiveSource(processIx, std::move(toSource), nextStamp)) {
		currentTimestampIx++;

		if (currentTimestampIx < timestamps.size()) {
			timestamps[currentTimestampIx] = std::move(nextStamp);
		}
		else {
			timestamps.emplace_back(std::move(nextStamp));
		}

		return true;
	}

	return false;
}

bool Binker::ReturnTimestamp(size_t toIx)
{
	if (0 <= toIx && toIx <= currentTimestampIx) {
		currentTimestampIx = toIx;
		return true;
	}

	return false;
}

void Binker::ShowTimestampInfo(size_t timestampIx) const
{
	if (0 <= timestampIx && timestampIx <= currentTimestampIx) {
		std::cout << "T" << timestampIx << "时刻进程信息为: \n";
		timestamps[timestampIx].ShowProcessInfo();
	}
}

void Binker::CurrentTimestampInfo() const
{
	ShowTimestampInfo(currentTimestampIx);
}

size_t Binker::GetCurrentStampProcessSize() const
{
	return timestamps[currentTimestampIx].GetProcessSize();
}
