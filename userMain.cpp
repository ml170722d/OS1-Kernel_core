/*
 * userMain.cpp
 *
 *  Created on: Aug 4, 2020
 *      Author: OS1
 */

#include "thread.h"
#include "kernel.h"

void tick(){
	cout<<".";
}

class TestThread : public Thread
{
private:
	TestThread *t;

public:

	TestThread(TestThread *thread): Thread(), t(thread){}
	~TestThread()
	{
		waitToComplete();
	}
protected:

	void run();

};

void TestThread::run()
{
	t->waitToComplete();
}


int userMain(int argc, char** argv)
{
	syncPrintf("Test starts.\n");
	TestThread *t1,*t2;
	t1 = new TestThread(t2);
	t2 = new TestThread(t1);
	t1->start();
	t2->start();
	delete t1;
	delete t2;
	syncPrintf("Test ends.\n");
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
