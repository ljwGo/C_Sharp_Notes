#pragma once
#include <vector>
#include <iostream>

using namespace std;

template <typename PELE>
class Container {
public:
	~Container();
	// 添加末尾元素
	void push(PELE pNewEle);
	// 删除末尾元素
	void pop();
	// 返回指定id值的元素引用
	PELE getEle(unsigned int id);
	// 返回指定名称的元素引用
	PELE getEle(string title);
	// 根据元素id删除元素(元素必须含有id属性) 
	void removeEle(unsigned int id);
	// 根据名称删除元素(元素必须含有Name的string类型属性)
	void removeEle(string title);
	// 根据元素删除
	void removeEle(PELE pEle);
	// 迭代器封装
	PELE next();
	// 重置迭代器
	void resetIterator();
	// 显示函数
	void display(string title);
protected:
	vector<PELE> elements;
	typename vector<PELE>::iterator iter;
};

template <typename PELE>
Container<PELE>::~Container() {
	for (PELE iele : elements) {
		delete iele;
	}
}
template <typename PELE>
void Container<PELE>::push(PELE pNewEle) {
	elements.push_back(pNewEle);
}
template <typename PELE>
void Container<PELE>::pop() {
	if (!elements.empty()) {
		// 由于是动态创建的元素, 删除前必须先delete
		delete elements[elements.size() - 1];
		elements.pop_back();
	}
}
template <typename PELE>
PELE Container<PELE>::getEle(unsigned int id) {
	for (PELE iele : elements) {
		if (iele->getId() == id) {
			return iele;
		}
	}
	return NULL;
}
template <typename PELE>
PELE Container<PELE>::getEle(string name) {
	for (PELE iele : elements) {
		if (iele->getName() == name) {
			return iele;
		}
	}
	return NULL;
}
template <typename PELE>
void Container<PELE>::removeEle(unsigned int id) {
	for (typename vector<PELE>::iterator it = elements.begin(); it != elements.end(); it++) {
		if ((*it)->getId() == id) {
			delete* it;
			it = elements.erase(it);
		}
	}
}
template <typename PELE>
void Container<PELE>::removeEle(string name) {
	for (typename vector<PELE>::iterator it = this->elements.begin(); it != this->elements.end(); it++) {
		if ((*it)->getName() == name) {
			delete* it;
			it = this->elements.erase(it);
			// 此时必须判断it是否就等于end(),否则,下一次for循环将再增加it
			if (it == this->elements.end()) break;
		}
	}
}
template <typename PELE>
void Container<PELE>::removeEle(PELE pEle) {
	for (typename vector<PELE>::iterator it = this->elements.begin(); it != this->elements.end(); it++) {
		if (*it == PELE) {
			delete* it;
			elements.erase(it);
			break;
		}
	}
}
template <typename PELE>
PELE Container<PELE>::next() {
	if (iter != NULL) {
		// 如果此时的iter不超过end
		if (iter != elements.end()) {
			return *(iter++);
		}
	}
	return NULL;
}
template <typename PELE>
void Container<PELE>::resetIterator() {
	// 如果elements不为空
	if (!elements.empty()) {
		iter = elements.begin();
	}
	else {
		iter = NULL;
	}
}
template <typename PELE>
void Container<PELE>::display(string title) {
	// PELE必须重载过 << 插入和输出流的函数
	cout << "++++++ " << title << " ++++++" << endl;
	for (PELE iele : elements) {
		iele->showMe();
	}
}
