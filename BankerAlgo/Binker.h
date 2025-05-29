#pragma once
#include <vector>
#include <iostream>
#include <string>
#include "global.h"
#include "Timestamp.h"

class Binker {

public:
	Binker(source&& allSource, std::vector<Process>&& ps) noexcept;
	void SecurityDetect();
	bool GiveSource(size_t processIx, source&& toSource) noexcept;
	bool ReturnTimestamp(size_t toIx);
	void ShowTimestampInfo(size_t timestampIx) const;
	void CurrentTimestampInfo() const;
	size_t GetCurrentStampProcessSize() const;

private:
	void __PrintInfo() const;

	size_t currentTimestampIx = 0;
	source allSource;
	std::vector<Timestamp> timestamps;
};