#ifndef _ORDERGROUP_H
#define _ORDERGROUP_H

#include "container.h"

template <class PELE>
class OrderGroup: public Container<PELE>{
public:
	void removeEleByBuyerId(unsigned int buyerId);
};

#endif