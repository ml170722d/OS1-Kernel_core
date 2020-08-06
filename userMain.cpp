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

void tick(){
	cout<<".";
}

class A:public Thread{
public:
	A(char c, Time ts):Thread(defaultStackSize, ts), znak(c){}
	~A(){
		waitToComplete();
	}
protected:
	void run(){
		for (unsigned long long int i = 0; i < 10000; ++i) {
			kIntLock
			cout<<znak;
			kIntUnlock
			for (int j = 0; j < 2000; ++j) {
				for (int k = 0; k < 2000; ++k) {

				}
			}
		}
		kIntLock
		cout<<endl<<znak<<" over"<<endl;
		kIntUnlock
	}
private:
	char znak;
};

int userMain(int argc, char** argv)
{

	/*cout<<"test start"<<endl;

	A *a = new A('a', 4),
			*b = new A('b', 6),
			*c = new A('c', 8),
			*d = new A('d', 10),
			*e = new A('e', 4),
			*f = new A('f', 6),
			*g = new A('g', 8),
			*h = new A('h', 2);

	a->start();
	b->start();
	c->start();
	d->start();
	e->start();
	f->start();
	g->start();
	h->start();


	delete a;
	delete b;
	delete c;
	delete d;
	delete e;
	delete f;
	delete g;
	delete h;

	cout<<"test over"<<endl;*/

	lock_I;
	tests_for_linkedList();
	unlock_I;

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
