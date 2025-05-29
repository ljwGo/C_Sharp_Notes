#ifndef _BOOKSHELF_H
#define _BOOKSHELF_H

#include "container.h"
#include "book.h"
#include <map>
#include "order.h"

template <typename PELE>
class BookShelf : public Container<PELE> {
public:
	bool removeEleByTitle(string title); // ��������ɾ��Ԫ��(Ԫ�ر��뺬��title��string��������)
	PELE getEleByTitle(string title); // ����ָ�����Ƶ�Ԫ������
	bool isEleExist(PELE pele); // ����Ԫ��ָ���Ƿ����
	bool check(Order* pOrder); // ��鶩���е���, ������Ƿ���, ���������㹻
};

template <typename PELE>
bool BookShelf<PELE>::removeEleByTitle(string title) {
	bool flag = false;
	// (1)bug���˺þ�, ��, ���ܹ��ڱ���ʱɾ����ǰ������, erase������һ��������
	// (2)���һ��bug����һ��, ���ǵ���������end��
	// (3)this->elements.erase(iele); eraseֻ֧�ֵ��������͵��β��ƺ�
	for (typename vector<PELE>::iterator it = this->elements.begin(); it != this->elements.end(); it++) {
		if ((*it)->getTitle() == title) {
			delete* it;
			it = this->elements.erase(it);
			// ��ʱ�����ж�it�Ƿ�͵���end(),����,��һ��forѭ����������it, �ͳ���end��
			if (it == this->elements.end()) break;

			flag = true;
		}
	}
	return flag;
}

template <typename PELE>
PELE BookShelf<PELE>::getEleByTitle(string title) {
	for (PELE iele : this->elements) {
		if (iele->getTitle() == title) {
			return iele;
		}
	}
	return NULL;
}

template <typename PELE>
bool BookShelf<PELE>::isEleExist(PELE ele) {
	for (PELE pele : this->elements) {
		if (pele == ele) {
			return true;
		}
	}
	return false;
}

// ��ѵ, ��Ҫ��ͷ�ļ��е���ǻ������е���, ����������ɻ��ർ�������
template <typename PELE>
bool BookShelf<PELE>::check(Order* pOrder) {
	Book* pBook = NULL;
	bool flag = true;

	for (typename map<Book*, unsigned int>::iterator it = pOrder->begin(); it != pOrder->end(); it++) {
		// ��������е������
		if (isEleExist(it->first)) {
			// �����������С�ڶ����е�����
			// ����ָ������, ���ڴ�����ļ��л��������
			if (it->first->getAmount() < it->second) {
				cout << "���Ϊ" << it->first->getId() << "�����治��" << endl;
				flag = false;
			}
		}
		else {
			cout << "���Ϊ" << it->first->getId() << "���鲻����" << endl;
			flag = false;
		}
	}
	return flag;
}

#endif