#include "Process.h"

Process::Process(source&& max, source&& alloc) noexcept
{
	this->need = std::move(max - alloc);
	this->alloc = std::move(alloc);
	this->max = std::move(max);
}

source const& Process::GetAlloc() const
{
	return alloc;
}

source const& Process::GetNeed() const
{
	return need;
}

source const& Process::GetMax() const
{
	return max;
}

void Process::GiveSource(source&& toSource)
{
	if (toSource > need) {
		return;
	}

	alloc = alloc + toSource;
	need = need - toSource;
}
