/*
 * userMain.cpp
 *
 *  Created on: Aug 4, 2020
 *      Author: OS1
 */

#include "thread.h"

class A: public Thread {
public:
	A(char c) :
			Thread(), znak(c) {
	}
	virtual ~A() {
		waitToComplete();
	}
protected:
	void run() {
		for (int i = 0; i < 1000; i++) {
			for (int j = 0; j < 30000; j++) {
				for (int k = 0; k < 30000; k++) {

				}
			}
			cout << i << " " << znak << endl;
		}
	}

private:
	char znak;
};

int userMain(int argc, char** argv) {

	A a('a');
	a.start();
	A b('b');
	b.start();
	A c('c');
	c.start();

	return 0;
}

void tick() {

}
