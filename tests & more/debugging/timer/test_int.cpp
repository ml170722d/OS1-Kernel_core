#include "tests.h"

#ifdef TIMER_TESTS

#include <iostream.h>
#include "consts.h"

const int N = 100;

#ifdef TEST_1
void tick() {
	syncPrintf(".");
}
#endif

#ifdef TEST_2
const int T = 1000 / 55; //times timer is called in 1s
int m = 0;
const int GOAL = 10;

void tick() {
	if (m % T == 0) {
		syncPrintf("%d ", m / T);
	}
	m++;
}
#endif

#ifdef TEST_3
const int T = 1000 / 55; //times timer is called in 1s
int m = 0;
const int GOAL = 30;

void tick() {
	if (m % T == 0) {
		syncPrintf("%d\n", m / T);
	}
	m++;
}
#endif

#if !defined TEST_1 && !defined TEST_2 && !defined TEST_3 && !defined TEST_4 && !defined TEST_5 && !defined TEST_6
void tick(){

}
#endif
int userMain(int argc, char** argv) {
	syncPrintf("test start\n");

#ifdef TEST_1
	int i = 0;
	while (i++ < N) {
		for (int q = 0; q < 5000; q++) {
			for (int p = 0; p < 5000; p++) {

			}
		}
	}
	syncPrintf("\n");
#endif

#ifdef TEST_2
	while (m / T < GOAL) {
	}
#endif

#ifdef  TEST_3
	while (m/T<GOAL){
		lock_I;
		syncPrintf("a ");
		unlock_I;
		for (int var = 0; var < 10000; ++var) {
			for (int var2 = 0; var2 < 20000; ++var2) {

			}
		}
	}
#endif

	syncPrintf("test end\n");
	return 0;
}

#endif
