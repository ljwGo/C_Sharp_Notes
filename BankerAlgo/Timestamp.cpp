#pragma once

#include "Timestamp.h"
#include <iostream>

Timestamp::Timestamp()
{
}

Timestamp::Timestamp(source&& allSource, std::vector<Process>&& ps) noexcept
{
	remainSource = allSource;
	for (int i = 0; i < ps.size(); i++) {
		remainSource = std::move(remainSource - ps[i].GetAlloc());
	}
	this->ps = std::move(ps);
}

bool Timestamp::SecurityDetect()
{
	__ResetProcess();

	size_t infoIx = 0;
	source work = remainSource;
	infos.resize(ps.size());

	for (int i = 0; i < ps.size(); i++) {
		for (int j = 0; j < ps.size(); j++) {
			if (!ps[j].finish && ps[j].GetNeed() <= work) {
				ps[j].finish = true;

				Info& info = infos[infoIx++];
				info.pIx = j;
				info.work = work;
				info.alloc = ps[j].GetAlloc();
				info.need = ps[j].GetNeed();
				info.workAndAlloc = info.work + info.alloc;

				work = info.workAndAlloc;
			}
		}
	}

	for (int i = 0; i < ps.size(); i++) {
		if (!ps[i].finish) {
			return false;
		}
	}

	return true;
}

bool Timestamp::GiveSource(size_t processIx, source&& toSource, Timestamp& nextStamp)
{
	if (processIx >= ps.size()) {
		std::cout << "超出进程数量" << std::endl;
		return false;
	}

	if (!(toSource <= ps[processIx].GetNeed())) {
		std::cout << "您的要求超出了需要范围，导致ERROR，请重新输入！" << std::endl;
		return false;
	}

	if (!(toSource <= remainSource)) {
		std::cout << "您的要求暂时无法满足，导致BLOCK，请重新输入~" << std::endl;
		return false;
	}

	nextStamp.ps = this->ps;
	nextStamp.remainSource = this->remainSource - toSource;
	nextStamp.ps[processIx].GiveSource(std::move(toSource));

	if (nextStamp.SecurityDetect()) {
		std::cout << "分配成功!!" << std::endl;
		return true;
	}
	else {
		std::cout << "未找到安全序列，继续分配将导致系统进入不安全状态，进而可能引发死锁，不予分配资源！！" << std::endl;
		return false;
	}
}

void Timestamp::ShowProcessInfo() const
{
	std::ostringstream str;
	str << "|  id  |   need   |   allo   |   max   |\n";
	for (int i = 0; i < ps.size(); i++) {
		str << "|  P" << i << "  | "
			<< ps[i].GetNeed() << " | "
			<< ps[i].GetAlloc() << " | "
			<< ps[i].GetMax() << "  |\n";
	}
	std::cout << str.str() << std::endl;
}

size_t Timestamp::GetProcessSize() const
{
	return ps.size();
}

void Timestamp::__ResetProcess()
{
	for (size_t i = 0; i < ps.size(); i++)
	{
		ps[i].finish = false;
	}
}
