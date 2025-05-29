#include "container.h"
#include "book.h"
#include <vector>
/* �����Ż�ʱ����ʹ���쳣����, ���ǿ�����boolֵ���ж��Ƿ�ɹ�! */

template <class PELE>
Container<PELE>::~Container() {
	for (PELE iele : elements) {
		delete iele;
	}
}

template <class PELE>
void Container<PELE>::push(PELE pNewEle) {
	elements.push_back(pNewEle);
}

template <class PELE>
//PELE Container<PELE>::pop(){
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

template <class PELE>
void Container<PELE>::removeEleById(unsigned int id) {
	//for (PELE iele : this->elements) {
	//	if (iele->getId() == id) {
	//		delete iele;
	//		this->elements.erase(iele); // eraseֻ֧�ֵ��������͵��β��ƺ�
	//	}
	//}
	for (typename vector<PELE>::iterator it = this->elements.begin(); it != this->elements.end(); it++) {
		if ((*it)->getId() == id) {
			delete* it;
			this->elements.erase(it);
		}
	}
}

template <class PELE>
PELE Container<PELE>::getEleById(unsigned int id) {
	for (PELE iele : this->elements) {
		if (iele->getId() == id) {
			return iele;
		}
	}
	return NULL;
}

template <class PELE>
void Container<PELE>::display() {
	// PELE�������ع� << �����������ĺ���
	// (�Ȳ�д)��ʹ��display
	for (PELE iele : this->elements) {
		cout << *iele << endl;
	}
}

// ��ʾʵ����
template class Container<Book*>;