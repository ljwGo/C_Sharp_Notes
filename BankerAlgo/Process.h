#pragma once
#include <vector>
#include <string>
#include "global.h"

class Process
{
public:
	Process(source&& max, source&& alloc) noexcept;
	source const& GetAlloc() const;
	source const& GetNeed() const;
	source const& GetMax() const;
	void GiveSource(source&& toSource);

	bool finish = false;

private:
	source max;
	source alloc;
	source need;
};

