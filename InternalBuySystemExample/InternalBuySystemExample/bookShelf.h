#ifndef _BOOKSHELF_H
#define _BOOKSHELF_H

#include "container.h"
#include "book.h"
#include <map>
#include "order.h"

template <typename PELE>
class BookShelf : public Container<PELE> {
public:
	bool removeEleByTitle(string title); // 根据名称删除元素(元素必须含有title的string类型属性)
	PELE getEleByTitle(string title); // 返回指定名称的元素引用
	bool isEleExist(PELE pele); // 返回元素指针是否存在
	bool check(Order* pOrder); // 检查订单中的书, 书架上是否都有, 并且数量足够
};

template <typename PELE>
bool BookShelf<PELE>::removeEleByTitle(string title) {
	bool flag = false;
	// (1)bug找了好久, 靠, 不能够在遍历时删除当前迭代器, erase返回下一个迭代器
	// (2)解决一个bug又来一个, 就是迭代器超过end了
	// (3)this->elements.erase(iele); erase只支持迭代器类型的形参似乎
	for (typename vector<PELE>::iterator it = this->elements.begin(); it != this->elements.end(); it++) {
		if ((*it)->getTitle() == title) {
			delete* it;
			it = this->elements.erase(it);
			// 此时必须判断it是否就等于end(),否则,下一次for循环将再增加it, 就超过end了
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

// 教训, 不要在头文件中导入非基本库中的类, 否则容易造成互相导入等问题
template <typename PELE>
bool BookShelf<PELE>::check(Order* pOrder) {
	Book* pBook = NULL;
	bool flag = true;

	for (typename map<Book*, unsigned int>::iterator it = pOrder->begin(); it != pOrder->end(); it++) {
		// 如果订单中的书存在
		if (isEleExist(it->first)) {
			// 并且书的数量小于订单中的数量
			// 保存指针类型, 对于存放在文件中会出现问题
			if (it->first->getAmount() < it->second) {
				cout << "编号为" << it->first->getId() << "的书库存不足" << endl;
				flag = false;
			}
		}
		else {
			cout << "编号为" << it->first->getId() << "的书不存在" << endl;
			flag = false;
		}
	}
	return flag;
}

#endif