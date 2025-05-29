#include "pch.h"
#include "gtest/gtest.h"
#include "../MultipleThreadTest/CacheNoHit.cpp"
#include "../MultipleThreadTest/Synchronization.cpp"
#include "../MultipleThreadTest/TestForFine_Grained.cpp"

TEST(CacheNoHit, EXECUTE) {
	TestForCacheNoHit();
	EXPECT_TRUE(true);
}

TEST(Synchronization, EXECUTE) {
	TestForSync();
	EXPECT_TRUE(true);
}

TEST(TestForFine, EXECUTE) {
	TestForGrained();
	EXPECT_TRUE(true);
}