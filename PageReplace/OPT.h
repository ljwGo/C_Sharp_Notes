#include "AlgorithmBase.h"

class OPT : public AlgorithmBase {
public:
	OPT(int blockNum);
	~OPT();
	virtual void Execute(PageAccessSequence sequence);
private:
	SimpleBlockManager* blockManager;
};