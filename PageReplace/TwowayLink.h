#pragma once
typedef struct LinkNode {
    int value = -1;
	LinkNode* pervious = nullptr;
	LinkNode* next = nullptr;
} LinkNode;

class TwowayLink
{
public:
	TwowayLink(int blockNum);
	~TwowayLink();
	// 使用头插法插入新元素, 那么尾巴就是访问得最晚的元素
	bool Insert(int val);
	bool SwapTailVal(int val);
	void SwapTail2Head();
	void Swap2Head(int ix);
	bool IsExist(int val, int& addressIx);
	int GetVal(int ix);
	bool IsFull();
	bool IsEmpty();

private:
	LinkNode* GetNodeByIx(int ix);

	LinkNode* head;
	LinkNode* tail;
	int eleNum = 0;
	int blockNum;
};

