#include <chrono>
#include <iostream>
#include <thread>
#include "global.h"

// 缓存行未命中 163840=10*1024*16 | 16
// 1级数据缓存 320 | 32K=1024*32B 8192
// 2及数据缓存 40 | 256K=1024*256 65536
#define ROW 320
#define COL 8200
#define REPEATCOUNT 100

inline int RowPriorityCol(int a[ROW][COL]) {
	int sum = 0;
	for (int i = 0; i < ROW; ++i) {
		for (int j = 0; j < COL; ++j) {
			sum += a[i][j];
		}
	}
	return sum;
}

inline int ColPriorityRow(int a[ROW][COL]) {
	int sum = 0;
	for (int j = 0; j < COL; ++j) {
		for (int i = 0; i < ROW; ++i) {
			sum += a[i][j];
		}
	}
	return sum;
}

inline void TestForCacheNoHit(){
	using namespace std;

	//int a[ROW][COL];
	int (*a)[COL] = new int[ROW][COL];
	double avgRowPriorityCol = 0, avgColPriorityRow = 0;

	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			a[i][j] = i * j;
		}
	}

	avgRowPriorityCol = avgTime<chrono::milliseconds>(RowPriorityCol, REPEATCOUNT, a);
	avgColPriorityRow = avgTime<chrono::milliseconds>(ColPriorityRow, REPEATCOUNT, a);

	delete[] a;

	cout << "avgColPriorityRow finished in " << avgColPriorityRow << "milliseconds\n";
	cout << "avgRowPriorityCol finished in " << avgRowPriorityCol << "milliseconds\n";
}
