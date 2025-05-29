#ifndef _CUSTOMERGROUP_H
#define _CUSTOMERGROUP_H

#include "container.h"
#include <string>
#include <vector>

template <typename PELE>
class CustomerGroup : public Container<PELE> {
public:
	bool removeEleByName(string name); // ��������ɾ��Ԫ��(Ԫ�ر��뺬��name��string��������)
	PELE getEleByAccount(string account); // �����˺ŷ���Ԫ�ض���(Ԫ�ر��뺬��account��string��������)
	PELE getEleByName(string name); // ����ָ�����Ƶ�Ԫ������
	bool isAccountExist(string account);
};

template <typename PELE>
bool CustomerGroup<PELE>::removeEleByName(string name) {
	bool flag = false;
	for (typename vector<PELE>::iterator it = this->elements.begin(); it != this->elements.end(); it++) {
		if ((*it)->getName() == name) {
			delete* it;
			it = this->elements.erase(it);
			// ��ʱ�����ж�it�Ƿ�͵���end(),����,��һ��forѭ����������it
			if (it == this->elements.end()) break;

			flag = true;
		}
	}
	return flag;
}

template <typename PELE>
PELE CustomerGroup<PELE>::getEleByName(string name) {
	for (PELE iele : this->elements) {
		if (iele->getName() == name) {
			return iele;
		}
	}
	return NULL;
}

template <typename PELE>
PELE CustomerGroup<PELE>::getEleByAccount(string account) {
	for (PELE iele : this->elements) {
		if (iele->getAccount() == account) {
			return iele;
		}
	}
	return NULL;
}

template <typename PELE>
bool CustomerGroup<PELE>::isAccountExist(string account) {
	for (PELE iele : this->elements) {
		if (iele->getAccount() == account) {
			return true;
		}
	}
	return false;
}

#endif
