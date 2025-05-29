#include "container.h"
#include "book.h"
#include <vector>
/* 后面优化时尽量使用异常处理, 而非靠返回bool值来判断是否成功! */

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
		// 由于是动态创建的元素, 删除前必须先delete
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
	//		this->elements.erase(iele); // erase只支持迭代器类型的形参似乎
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
	// PELE必须重载过 << 插入和输出流的函数
	// (先不写)或使用display
	for (PELE iele : this->elements) {
		cout << *iele << endl;
	}
}

// 显示实例化
template class Container<Book*>;