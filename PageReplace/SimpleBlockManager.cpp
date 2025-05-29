#include "SimpleBlockManager.h"

SimpleBlockManager::SimpleBlockManager(int size)
{
	elements = new std::vector<int>(size);
	eleIx = 0;

	for (int i = 0; i < elements->size(); i++) {
		(*elements)[i] = -1;
	}
}

SimpleBlockManager::~SimpleBlockManager()
{
	delete elements;
}

bool SimpleBlockManager::IsFull()
{
	return eleIx >= elements->size();
}

bool SimpleBlockManager::Push(int val)
{
	if (IsFull()) {
		return false;
	}

	(*elements)[eleIx++] = val;
	return true;
}

bool SimpleBlockManager::Push(int ix, int val)
{
	if (ix < 0 || ix >= (*elements).size()) {
		return false;
	}

	(*elements)[ix] = val;

	return true;
}

int SimpleBlockManager::GetVal(int ix)
{
	return (*elements)[ix];
}
