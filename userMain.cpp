/*
 * userMain.cpp
 *
 *  Created on: Aug 4, 2020
 *      Author: OS1
 */

#include "thread.h"

class A: public Thread {
public:
	A() :
			Thread() {
	}
	virtual ~A() {
		waitToComplete();
	}
protected:
	void run() {
		while (1) {}
	}

private:

};

int userMain(int argc, char** argv) {

	A a;
	a.start();


	return 0;
}

void tick() {
	cout<<".";
}
