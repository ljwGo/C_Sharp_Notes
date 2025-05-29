#include "orderGroup.h"

template <class PELE>
void OrderGroup<PELE>::removeEleByBuyerId(unsigned int buyerId) {
	for (PELE iele: this->elements) {
		if (iele->getBuyerId() == buyerId) {
			delete iele;
			this->elements.erase(iele);
		}
	}
}