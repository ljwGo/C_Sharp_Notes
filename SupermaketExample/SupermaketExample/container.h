#pragma once
#include <vector>
#include <iostream>

using namespace std;

template <typename PELE>
class Container {
public:
	~Container();
	// ���ĩβԪ��
	void push(PELE pNewEle);
	// ɾ��ĩβԪ��
	void pop();
	// ����ָ��idֵ��Ԫ������
	PELE getEle(unsigned int id);
	// ����ָ�����Ƶ�Ԫ������
	PELE getEle(string title);
	// ����Ԫ��idɾ��Ԫ��(Ԫ�ر��뺬��id����) 
	void removeEle(unsigned int id);
	// ��������ɾ��Ԫ��(Ԫ�ر��뺬��Name��string��������)
	void removeEle(string title);
	// ����Ԫ��ɾ��
	void removeEle(PELE pEle);
	// ��������װ
	PELE next();
	// ���õ�����
	void resetIterator();
	// ��ʾ����
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
		// �����Ƕ�̬������Ԫ��, ɾ��ǰ������delete
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
			// ��ʱ�����ж�it�Ƿ�͵���end(),����,��һ��forѭ����������it
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
		// �����ʱ��iter������end
		if (iter != elements.end()) {
			return *(iter++);
		}
	}
	return NULL;
}
template <typename PELE>
void Container<PELE>::resetIterator() {
	// ���elements��Ϊ��
	if (!elements.empty()) {
		iter = elements.begin();
	}
	else {
		iter = NULL;
	}
}
template <typename PELE>
void Container<PELE>::display(string title) {
	// PELE�������ع� << �����������ĺ���
	cout << "++++++ " << title << " ++++++" << endl;
	for (PELE iele : elements) {
		iele->showMe();
	}
}
