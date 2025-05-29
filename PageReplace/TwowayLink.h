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
	// ʹ��ͷ�巨������Ԫ��, ��ôβ�;��Ƿ��ʵ������Ԫ��
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

