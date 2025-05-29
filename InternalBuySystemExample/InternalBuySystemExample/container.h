#ifndef _CONTAINER_H
#define _CONTAINER_H

#include "book.h"
#include <vector>
#include <iostream>
using namespace std;

template <typename PELE>
class Container {
public:
	~Container();
	bool removeEleById(unsigned int id); // 根据元素id删除元素(元素必须含有id属性) 
	void push(PELE pNewEle); // 添加末尾元素
	//PELE pop(); // 移除末尾元素, 返回被删除元素值的该方法先不做
	bool pop();
	PELE getEleById(unsigned int id); // 返回指定id值的元素引用
	void display(); // 显示函数
protected:
	vector<PELE> elements;
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
bool Container<PELE>::pop() {
	if (!elements.empty()) {
		// 由于是动态创建的元素, 删除前必须先delete
		delete elements[elements.size() - 1];
		elements.pop_back();
		return true;
	}
	else {
		return false;
	}
}

template <typename PELE>
bool Container<PELE>::removeEleById(unsigned int id) {
	for (typename vector<PELE>::iterator it = elements.begin(); it!=elements.end(); it++) {
		if ((*it)->getId() == id) {
			delete* it;
			it = elements.erase(it);
			return true;
		}
	}
	return false;
}

template <typename PELE>
PELE Container<PELE>::getEleById(unsigned int id) {
	for (PELE iele : this->elements) {
		if (iele->getId() == id) {
			return iele;
		}
	}
	return NULL;
}

template <typename PELE>
void Container<PELE>::display() {
	// PELE必须重载过 << 插入和输出流的函数
	// (先不写)或使用display
	for (PELE iele : this->elements) {
		cout << *iele << endl;
	}
}

#endif // !_CONTAINER_H