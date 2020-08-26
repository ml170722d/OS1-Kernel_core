/*
 * LinkLst.cpp
 *
 *  Created on: Jul 8, 2020
 *      Author: OS1
 */

#include "linkLst.h"

void test_empty_and_size() {
	LinkedList<int> numbers;

	cout << "Initially, numbers.isEmpty(): " << numbers.isEmpty() << endl;

	numbers.add(42);
	numbers.add(13317);
	cout << "After adding elements, numbers.isEmpty(): " << numbers.isEmpty()
		<< ", size: " << numbers.getSize() << endl;

	/*
	 * expected output:
	 * Initially, numbers.empty(): 1
	 * After adding elements, numbers.empty(): 0, size: 2
	 */

}

void test_iteration_trough_list() {
	LinkedList<int> numbers;

	cout << "Initially, numbers.isEmpty(): " << numbers.isEmpty() << endl;

	numbers.add(10);
	numbers.add(20);
	cout << "After adding elements, numbers.isEmpty(): " << numbers.isEmpty()
		<< ", size: " << numbers.getSize() << endl;

	numbers.add(30);
	numbers.add(40);
	numbers.add(50);

	for (LinkedList<int>::Iterator it = numbers.begin(); it != numbers.end();
		++it) {
		cout << *it << " ";
	}
	cout << endl;

	/*
	 * expected output:
	 * Initially, numbers.empty(): 1
	 * After adding elements, numbers.empty(): 0, size: 2
	 * 10 20 30 40 50
	 */
}

void test_printList() {
	LinkedList<char> chars;

	chars.add('a');
	chars.add('b');
	chars.add('c');
	chars.add('d');
	chars.add('e');
	chars.add('f');

	chars.printList();

	/*
	 * expected output:
	 * data: a
	 * data: b
	 * data: c
	 * data: d
	 * data: e
	 * data: f
	 */
}

void test_remove() {
	LinkedList<char> chars;

	char a = 'a', b = 'b', c = 'c', d = 'd', e = 'e', f = 'f';
	chars.add(a);
	chars.add(b);
	chars.add(c);
	chars.add(d);
	chars.add(e);
	chars.add(f);

	chars.printList();

	cout << "rm d" << endl;
	chars.remove(d);
	chars.printList();

	cout << "rm b" << endl;
	chars.remove(b);
	chars.printList();

	cout << "rm a" << endl;
	chars.remove(a);
	chars.printList();

	cout << "rm f" << endl;
	chars.remove(f);
	chars.printList();

	cout << "rm c" << endl;
	chars.remove(c);
	chars.printList();

	cout << "rm e" << endl;
	chars.remove(e);
	chars.printList();

}

void test_rm_and_add() {
	LinkedList<char> chars;

	char a = 'a', b = 'b', c = 'c', d = 'd', e = 'e', f = 'f';
	chars.add(a);
	chars.add(b);
	chars.add(c);
	chars.add(d);
	chars.add(e);
	chars.add(f);

	char y = 'y', yy = 'x', q = 'q', p = 'p';

	chars.printList();

	cout << "rm c" << endl;
	chars.remove(c);
	chars.printList();

	cout << "rm e" << endl;
	chars.remove(e);
	chars.printList();

	cout << "add y" << endl;
	chars.add(y);
	chars.printList();

	cout << "add x" << endl;
	chars.add(yy);
	chars.printList();

	cout << "add x" << endl;
	chars.add(yy);
	chars.printList();

	cout << "rm x" << endl;
	chars.remove(y);
	chars.printList();

	chars.clear();
	chars.printList();

	cout << "add q" << endl;
	chars.add(q);
	chars.printList();

	cout << "rm q" << endl;
	chars.remove(q);
	chars.printList();

	cout << "add p" << endl;
	chars.add(p);
	chars.printList();

	cout << "rm p" << endl;
	chars.remove(p);
	chars.printList();
}

void test_clear() {
	LinkedList<char> chars;

	char a = 'a', b = 'b', c = 'c', d = 'd', e = 'e', f = 'f';
	chars.add(a);
	chars.add(b);
	chars.add(c);
	chars.add(d);
	chars.add(e);
	chars.add(f);

	chars.printList();

	chars.clear();

	chars.printList();
}

class TestClass {
public:
	TestClass(char e) {
		c = new char[sizeof(char) * 1024];
		cc = e;
	}

	~TestClass() {
		delete c;
	}

	friend ostream& operator<<(ostream& it, const TestClass& t) {
		it << t.cc;
		return it;
	}

	friend ostream& operator<<(ostream& it, const TestClass* t) {
		it << t->cc;
		return it;
	}

	char getC() {
		return cc;
	}

private:
	char cc;
	char* c;
};

void test_basic() {
	TestClass t('a');
	TestClass* tt;
	TestClass* ttt;

	tt = new TestClass('b');
	ttt = new TestClass('c');


	cout << t << endl << *tt << endl << *ttt << endl;

	delete tt;
	delete ttt;
}

void test_insert_before() {
	LinkedList<TestClass*>* t = new LinkedList<TestClass*>();

	TestClass* a[20];

	for (int i = 0; i < 20; i++) {
		a[i] = new TestClass(i + 65);
		t->push_back(a[i]);
	}

	t->printList();

	TestClass* q = new TestClass('1'),
		* w = new TestClass('2'),
		* e = new TestClass('3'),
		* r = new TestClass('4'),
		* b = new TestClass('x'),
		* y = new TestClass('n'),
		* u = new TestClass('|'),
		* i2 = new TestClass('~');

	for (LinkedList<TestClass*>::Iterator it = t->begin(); it != t->end(); ++it) {
		switch ((*it)->getC())
		{
		case 'A':
			t->insert_before(it, q);
			t->printList();
			break;
		case 'D':
			t->insert_before(it, b);
			t->printList();
			break;
		case 'H':
			t->insert_before(it, u);
			t->printList();
			break;
		case 'C':
			t->insert_before(it, i2);
			t->printList();
			break;
		case 'x':
			t->insert_before(it, w);
			t->printList();
			break;
		case 'n':
			t->insert_before(it, e);
			t->printList();
			break;
		case 'T':
			t->insert_before(it, r);
			t->printList();
			t->insert_before(it, y);
			t->printList();
			break;
		default:
			break;
		}
	}

	t->printList();

	for (int ii = 0; ii < 20; ii++)
	{
		t->remove(a[ii]);
		delete a[ii];
	}

	t->clear();
	cout<<": ";
	t->printList();

	delete q;
	delete w;
	delete e;
	delete r;
	delete b;
	delete y;
	delete u;
	delete i2;

	t->printList();

	delete t;
}

void test_insert_after() {
	LinkedList<TestClass*>* t = new LinkedList<TestClass*>();

	TestClass* a[20];

	for (int i = 0; i < 20; i++) {
		a[i] = new TestClass(i + 65);
		t->push_back(a[i]);
	}

	t->printList();

	TestClass* q = new TestClass('1'),
		* w = new TestClass('2'),
		* e = new TestClass('3'),
		* r = new TestClass('4'),
		* b = new TestClass('x'),
		* y = new TestClass('n'),
		* u = new TestClass('|'),
		* i3 = new TestClass('~');

	for (LinkedList<TestClass*>::Iterator it = t->begin(); it != t->end(); ++it) {
		switch ((*it)->getC())
		{
		case 'A':
			t->insert_after(it, q);
			t->printList();
			break;
		case 'D':
			t->insert_after(it, b);
			t->printList();
			break;
		case 'H':
			t->insert_after(it, u);
			t->printList();
			break;
		case 'C':
			t->insert_after(it, i3);
			t->printList();
			break;
		case 'x':
			t->insert_after(it, w);
			t->printList();
			break;
		case 'n':
			t->insert_after(it, e);
			t->printList();
			break;
		case 'T':
			t->insert_after(it, r);
			t->printList();
			t->insert_after(it, y);
			t->printList();
			break;
		default:
			break;
		}
	}

	t->printList();

	for (int ii = 0; ii < 20; ii++)
	{
		t->remove(a[ii]);
		delete a[ii];
	}

	t->printList();

	t->clear();
	cout<<": ";
	t->printList();

	delete q;
	delete w;
	delete e;
	delete r;
	delete b;
	delete y;
	delete u;
	delete i3;

	t->printList();

	delete t;
}

void tests_for_linkedList() {
	cout << "Start" << endl;

	cout << "test_empty_and_size" << endl;
	test_empty_and_size();

	cout << "test_iteration_trough_list" << endl;
	test_iteration_trough_list();

	cout << "test_printList" << endl;
	test_printList();

	cout << "----------------" << endl;
	cout << "test_remove" << endl;
	test_remove();

	cout << "----------------" << endl;
	cout << "test_clear" << endl;
	test_clear();

	cout << "----------------" << endl;
	cout << "test_rm_and_add" << endl;
	test_rm_and_add();

	cout << endl;
	test_basic();

	cout << endl;
	test_insert_after();

	cout << endl;
	test_insert_before();

	cout << endl << "tests happy end" << endl;
}
