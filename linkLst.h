/*
 * LinkLst.h
 *
 *  Created on: Jul 8, 2020
 *      Author: OS1
 */

#ifndef LINKLST_H_
#define LINKLST_H_

#include "consts.h"

void tests_for_linkedList();

template<class T>
class LinkedList {
public:

	LinkedList() :
			size(0), head(null), tail(null) {
	}
	~LinkedList() {
		clear();
	}

	void printList();

	/*
	 * list node
	 */
	class LinkedListNode {
	public:
		LinkedListNode(T d) :
				data(d), next(null), prev(null) {
		}
		T data;
		LinkedListNode *next, *prev;
	};

	/*
	 * iterator to traverse through linked list
	 *
	 * NOTE: because of compiler or whatever, these functions for inner
	 * class must be declared and defined here
	 */
	class Iterator {
	public:
		Iterator(LinkedListNode* e = NULL) :
				elem(e) {
		}

		T& operator*() {
			return elem->data;
		}
		const T& operator*() const {
			return elem->data;
		}
		boolean operator!=(const Iterator& other) {
			return elem != other.elem;
		}
		boolean operator==(const Iterator& other) {
			return elem == other.elem;
		}
		Iterator operator++() {
			elem = elem->next;
			return *this;
		}
		Iterator operator++(int) {
			elem = elem->next;
			return *this;
		}

	protected:
		friend class LinkedList<T> ;
	private:
		LinkedListNode* elem;
	};

	/*
	 * functions needed to use linked list
	 */
	const T& first();
	const T& last();

	Iterator begin() {
		return (size != 0) ? Iterator(head) : Iterator(null);
	}
	Iterator end() {
		return (size != 0) ? Iterator(tail->next) : Iterator(null);
	}

	Iterator find(const T& e) {
		for (Iterator it = begin(); it != end(); ++it) {
			if (*it == e) {
				return it;
			}
		}
		return Iterator(null);
	}

	boolean isEmpty();
	int getSize();

	void clear();
	void add(const T& e);
	void remove(const T& e);

protected:
	int size;

private:
	LinkedListNode *head, *tail;
};

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
void LinkedList<T>::remove(const T& e) {
	LinkedListNode* it;
	for (it = head; it != tail; it = it->next) {
		if (it->data == e) {
			//cout << "found" << endl;
			break;
		}
	}

	if (it == head){
		head = head->next;
	}
	if (it == tail){
		tail = tail->prev;
	}

	LinkedListNode *next = it->next, *prev = it->prev;

	if (prev != null) {
		prev->next = next;
	}
	if (next != null) {
		next->prev = prev;
	}

	it->next = it->prev = null;
	size--;
	//delete it->data;
	it->data = null;
	delete it;

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

/*
 template<class T>
 void LinkedList<T>::remove(const T& e) {
 Iterator it;
 for (it = begin(); it != end(); ++it) {
 if (*it == e) {
 break;
 }
 }

 Iterator next = Iterator(it.elem->next), prev = Iterator(it.elem->prev);

 if (prev.elem != null) {
 prev.elem->next = next.elem;
 }
 if (next.elem != null) {
 next.elem->prev = prev.elem;
 }

 it.elem->next = it.elem->prev = null;
 size--;
 delete it.elem;
 it.elem = null;

 }
 */

template<class T>
const T& LinkedList<T>::first() {
	return head->data;
}

template<class T>
const T& LinkedList<T>::last() {
	return tail->data;
}

template<class T>
int LinkedList<T>::getSize() {
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

#endif /* LINKLST_H_ */
