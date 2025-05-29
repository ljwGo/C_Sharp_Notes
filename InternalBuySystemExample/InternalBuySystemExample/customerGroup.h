#ifndef _CUSTOMERGROUP_H
#define _CUSTOMERGROUP_H

#include "container.h"
#include <string>
#include <vector>

template <typename PELE>
class CustomerGroup : public Container<PELE> {
public:
	bool removeEleByName(string name); // 根据名称删除元素(元素必须含有name的string类型属性)
	PELE getEleByAccount(string account); // 根据账号返回元素对象(元素必须含有account的string类型属性)
	PELE getEleByName(string name); // 返回指定名称的元素引用
	bool isAccountExist(string account);
};

template <typename PELE>
bool CustomerGroup<PELE>::removeEleByName(string name) {
	bool flag = false;
	for (typename vector<PELE>::iterator it = this->elements.begin(); it != this->elements.end(); it++) {
		if ((*it)->getName() == name) {
			delete* it;
			it = this->elements.erase(it);
			// 此时必须判断it是否就等于end(),否则,下一次for循环将再增加it
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
