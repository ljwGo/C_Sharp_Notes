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
	bool removeEleById(unsigned int id); // ����Ԫ��idɾ��Ԫ��(Ԫ�ر��뺬��id����) 
	void push(PELE pNewEle); // ���ĩβԪ��
	//PELE pop(); // �Ƴ�ĩβԪ��, ���ر�ɾ��Ԫ��ֵ�ĸ÷����Ȳ���
	bool pop();
	PELE getEleById(unsigned int id); // ����ָ��idֵ��Ԫ������
	void display(); // ��ʾ����
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
		// �����Ƕ�̬������Ԫ��, ɾ��ǰ������delete
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
	// PELE�������ع� << �����������ĺ���
	// (�Ȳ�д)��ʹ��display
	for (PELE iele : this->elements) {
		cout << *iele << endl;
	}
}

#endif // !_CONTAINER_H