#pragma once
#include <vector>
#include <string>
#include "Process.h"
#include <sstream>

class Timestamp
{
public:
	Timestamp();
	Timestamp(source&& allSource, std::vector<Process>&& ps) noexcept;
	bool SecurityDetect();
	bool GiveSource(size_t processIx, source&& toSource, Timestamp& nextStamp);
	void ShowProcessInfo() const;
	size_t GetProcessSize() const;

private:
	void __ResetProcess();

	source remainSource;
	std::vector<Process> ps;
};

