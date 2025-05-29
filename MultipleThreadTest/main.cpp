#include <iostream>
#include "CacheNoHit.h"
#include "Synchronization.h"
#include "TestForFine_Grained.h"
#include "ShareSource.h"

int main(void) {

	//TestForCacheNoHit();

	//TestForSync();

	//std::cout << "sizeof(long long): " << sizeof(long long) << std::endl;

	//TestForGrained();

	TestForOperateN();

	return 0;
}