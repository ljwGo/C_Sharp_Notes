#pragma once
#include "AlgorithmBase.h"
#include "TwowayLink.h"

class LRU :
    public AlgorithmBase
{
public:
    LRU(int blockNum);
    ~LRU();
    virtual void Execute(PageAccessSequence sequence);
private:
    TwowayLink* blockLink;
};

