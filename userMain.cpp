/*
 * userMain.cpp
 *
 *  Created on: Aug 4, 2020
 *      Author: OS1
 */

#include "thread.h"
#include "kernel.h"
#include "consts.h"
#include "linkLst.h"
#include  "semaphor.h"
#include "ker_sem.h"

Semaphor s(0);

int t = 0;
void tick() {
	//cout << t++ << " ";
	//cout << s.myImpl->value << " ";
}

class A: public Thread {
public:
	A(int nn, Time ts, Semaphor *ss) :
			Thread(defaultStackSize, ts), n(nn), s(ss) {
	}
	~A() {
		waitToComplete();
	}
protected:
	void run() {

		// do something ...
		for (int i = 0; i < 30000; i++) {
			for (int j = 0; j < 30000; j++) {

			}
		}

		//critical section start
		s->wait(0);

		syncPrintf(
				"thread %d entered critical section++++++++++++++++++++++++\n",
				this->getId());
		for (int N = 0; N < n; N++) {
			for (int q = 0; q < 30000; ++q) {
				for (int p = 0; p < 30000; ++p) {

				}
			}
			cout << "thread " << this->getId() << " N = " << N << endl;
		}
		syncPrintf(
				"thread %d finished critical section--------------------------\n",
				this->getId());
		//critical section end
		s->signal(0);

		// do something ..
		for (int a = 0; a < 30000; a++) {
			for (int b = 0; b < 30000; b++) {

			}
		}

		kIntLock
		cout << endl << "thread " << this->getId() << " terminating" << endl;
		kIntUnlock
	}
private:
	int n;
	Semaphor* s;
};

int userMain(int argc, char** argv) {

	cout << "test start" << endl;

	A* a[10];
	for (int i = 0; i < 10; i++) {
		a[i] = new A(i * 2, 2, &s);
		a[i]->start();
	}

	for (int aa = 0; aa < 30000; aa++) {
		for (int b = 0; b < 30000; b++) {

		}
	}
	s.wait(100);

	syncPrintf("\nmain signal\n");
	s.signal(1);

	for (int j = 0; j < 10; j++) {
		delete a[j];
	}

	cout << "test over" << endl;
	return 0;
}

/*
 * test	|	resault
 * -----------------
 * 1	|	success
 * 2	|	success
 * 3	|	success
 * 4	|	success
 * 5	|	success
 * 6	|	success
 * 15	|	success
 */
