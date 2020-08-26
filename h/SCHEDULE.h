/*
 * schedule.h
 *
 *  Created on: May 30, 2018
 *      Author: OS1
 */

#ifndef SCHEDULE_H_
#define SCHEDULE_H_


class PCB;

class Scheduler {
public:
	static void put(PCB*);
	static PCB* get();
};

#endif /* SCHEDULE_H_ */
