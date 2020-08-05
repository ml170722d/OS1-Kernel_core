/*
 * main.cpp
 *
 *  Created on: Jul 11, 2020
 *      Author: OS1
 */

#include "SCHEDULE.H"
#include "thread.h"
#include "kernel.h"

#include "consts.h"

/*
 * n = 270 max?
 * no more memory?
 */
const int N = 5;
/*
 void doSomething1() {
 Kernel::Lock::CS_lock();
 PCB* p[N];

 int i;

 for (i = 0; i < N; ++i) {
 p[i] = new PCB(1024, (i % 2) ? 50 : 100, NULL);
 p[i]->start();
 }
 Kernel::Lock::CS_unlock();

 /////////////////////////////////////////////////////////////

 Kernel::Lock::CS_lock();
 for (i = 0; i < N; i++) {
 cout << p[i] << " ";
 }
 cout << endl;
 Kernel::printAllPCB();
 Kernel::Lock::CS_unlock();

 /////////////////////////////////////////////////////////////

 for (i = 0; i < N; i++) {
 delete p[i];
 p[i] = NULL;
 }
 Kernel::Lock::CS_lock();
 cout << "all pcb terminated" << endl;
 Kernel::Lock::CS_unlock();

 /////////////////////////////////////////////////////////////

 Kernel::Lock::CS_lock();
 for (i = 0; i < N; i++) {
 cout << p[i] << " ";
 }
 cout << endl;
 Kernel::printAllPCB();
 Kernel::Lock::CS_unlock();

 /////////////////////////////////////////////////////////////

 Kernel::Lock::CS_lock();
 cout << "fin on main end = " << PCB::fin << endl;
 cout << "Happy end for doSomethig1()!" << endl;
 Kernel::Lock::CS_unlock();
 }
 */
/*
void waitSomeTime(int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {

			}
		}
	}
}
*/
/*
class TestThread: public Thread {
public:
	TestThread(StackSize ss, Time ts, int N) :
			Thread(ss, ts) {
		n = N;
	}
	;
	~TestThread() {
		waitToComplete();
	}
	static int fin;
protected:

	void run();

private:
	int n;
};

int TestThread::fin = 0;

void TestThread::run() {

	waitSomeTime(n);

	Kernel::Lock::CS_lock();
	cout<<"i am done, id: "<<getId()<<endl;
	Kernel::Lock::CS_unlock();

	fin++;
}

void doSomething2() {

	Thread* t[N];

	for (int i = 0; i < N; i++) {
		t[i] = new TestThread(1024, (i%2)?50:100, (i%3)?2000:3000);
		t[i]->start();
	}

	for (int j = N; j > 0; j--) {
		delete t[j - 1];
	}

	Kernel::Lock::CS_lock();
	cout << "fin on main end = " << TestThread::fin << endl;
	cout << "Happy end for doSomethig2()!" << endl;
	Kernel::Lock::CS_unlock();

}
*/
/*
class A: public Thread{
public:
	A():Thread(){}
	~A(){
		waitToComplete();
	}
protected:
	virtual void run(){
		cout<<"hi"<<endl;
	}
};

void f(){

}

void doSomething3(){
	userMain(0, NULL);
}
*/

extern int syncPrintf(const char *format, ...);
extern int userMain(int argc, char** argv);

int main(int argc, char** argv) {

	syncPrintf("Starting system\n");

	Kernel::init();

	userMain(argc, argv);

	Kernel::restore();

	syncPrintf("System shutting down");
	return 0;

}
