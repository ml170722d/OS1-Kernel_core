/*
 * LinkLst.cpp
 *
 *  Created on: Jul 8, 2020
 *      Author: OS1
 */

#include "linkLst.h"

/*
 * problem with linker
 * can identify definitions of functions
 */
/*
 template<class T>
 LinkedList<T>::LinkedList() :
 size(0), head(null), tail(null) {
 }

 template<class T>
 LinkedList<T>::~LinkedList() {
 clear();
 }
 */
/*
 template<class T>
 void LinkedList<T>::add(const T& e) {
 LinkedListNode *newE = new LinkedListNode(e);
 if (isEmpty()) {
 head = newE;
 } else {
 tail->next = newE;
 newE->prev = tail;
 }

 tail = newE;
 size++;
 }

 template<class T>
 void LinkedList<T>::clear() {
 LinkedListNode* e = head;
 while (e != null) {
 head = head->next;
 e->next = e->prev = null;
 delete e;
 e = head;
 size--;
 }
 head = tail = null;
 }

 template<class T>
 void LinkedList<T>::remove(const T& e) {
 Iterator it;
 for (it = begin(); it != end(); ++it) {
 if (*it == e) {
 break;
 }
 }

 Iterator next = Iterator(it.elem->next), prev = Iterator(it.elem->prev);

 if (prev.elem != null){
 prev.elem->next = next.elem;
 }
 if (next.elem != null){
 next.elem->prev = prev.elem;
 }

 it.elem->next = it.elem->prev = null;
 size--;
 delete it.elem;
 it.elem = null;

 }

 template<class T>
 const T& LinkedList<T>::first() {
 return head;
 }

 template<class T>
 const T& LinkedList<T>::last() {
 return tail;
 }

 template<class T>
 Large LinkedList<T>::getSize() {
 return size;
 }

 template<class T>
 boolean LinkedList<T>::isEmpty() {
 return (head == null) ? true : false;
 }

 template<class T>
 void LinkedList<T>::printList() {
 for (Iterator it = begin(); it != end(); ++it) {
 cout << *it << " ";
 }
 cout << endl;
 }
 */
/*
 * ERROR: Type qualifier 'Iterator' must be a struct or class name
 * ERROR: Declaration terminated incorrectly
 * NOTE: similar error for any declaration involving inner struct or class
 */
/*
 template<class T>
 LinkedList<T>::Iterator::Iterator(LinkedList<T>::LinkedListNode* e){
 elem = e;
 }
 */

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
	cout<<"test_rm_and_add"<<endl;
	test_rm_and_add();

	cout<<"tests happy end"<<endl;
}
