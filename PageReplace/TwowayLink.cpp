#include "TwowayLink.h"

TwowayLink::TwowayLink(int blockNum)
{
	this->blockNum = blockNum;
	head = nullptr;
	tail = nullptr;
}

TwowayLink::~TwowayLink()
{
	LinkNode* node = head;

	while (node != nullptr) {
		LinkNode* temp = node;
		node = node->next;
		delete temp;
	}
}

bool TwowayLink::Insert(int val)
{
	if (IsFull()) {
		return false;
	}

	LinkNode* newNode = new LinkNode();
	newNode->value = val;

	// 插入首个元素需要特殊处理
	if (IsEmpty()) {
		head = newNode;
		tail = newNode;

		eleNum++;
		return true;
	}

	// 头插法
	newNode->next = head;
	head->pervious = newNode;
	head = newNode;

	eleNum++;
	return true;
}

// tail 表示最早进入的元素
bool TwowayLink::SwapTailVal(int val)
{
	if (IsEmpty()) {
		return false;
	}

	tail->value = val;
	return true;
}

void TwowayLink::SwapTail2Head()
{
	Swap2Head(eleNum - 1);
}

void TwowayLink::Swap2Head(int ix)
{
	LinkNode* targetNode = GetNodeByIx(ix);

	if (targetNode == nullptr || targetNode == head) {
		return;
	}

	if (targetNode == tail) {
		tail = tail->pervious;
		tail->next = nullptr;
	}
	else {
		// 将targetNode抽离出来
		LinkNode& next = *(targetNode->next);
		LinkNode& pervious = *(targetNode->pervious);
		pervious.next = &next;
		next.pervious = &pervious;
	}

	// 头插法插入
	targetNode->next = head;
	head->pervious = targetNode;
	head = targetNode;
}

bool TwowayLink::IsExist(int val, int& addressIx)
{
	LinkNode* node = head;
	int ix = 0;

	while (node != nullptr) {
		if (node->value == val){
			addressIx = ix;
			return true;
		}
		node = node->next;
		ix++;
	}

	return false;
}

int TwowayLink::GetVal(int ix)
{
	LinkNode* node = GetNodeByIx(ix);
	if (node != nullptr) {
		return node->value;
	}
	return 0;
}

bool TwowayLink::IsFull()
{
	return eleNum >= blockNum;
}

bool TwowayLink::IsEmpty()
{
	return eleNum == 0;
}

LinkNode* TwowayLink::GetNodeByIx(int ix)
{
	if (ix < eleNum) {
		LinkNode* node = head;

		for (int i=1; i<=ix; i++){
			node = node->next;
		}

		return node;
	}
	return nullptr;
}
