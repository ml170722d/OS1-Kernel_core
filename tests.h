/*
 * tests.h
 *
 *  Created on: Aug 24, 2020
 *      Author: OS1
 */

#ifndef TESTS_H_
#define TESTS_H_

#include <STDLIB.H>

/*
 * Change only (comment and uncomment)
 * #define MEMORY_LEAK_TEST,
 * #define PUBLIC_TEST and
 * inside #ifndef PUBLIC_TEST
 */
//#define MEMORY_LEAK_TEST
//#define PUBLIC_TEST
#ifndef PUBLIC_TEST

#define TIMER_TESTS
#define THREAD_TESTS
#define LIST_TESTS
#define SEMAPHORE_TESTS
#define EVENT_TESTS

#define TEST_1
#define TEST_2
#define TEST_3
#define TEST_4
#define TEST_5
#define TEST_6

#endif /* PUBLIC_TEST */

#ifdef TEST_1
#undef TEST_2
#undef TEST_3
#undef TEST_4
#undef TEST_5
#undef TEST_6
#endif

#ifdef TEST_2
#undef TEST_1
#undef TEST_3
#undef TEST_4
#undef TEST_5
#undef TEST_6
#endif

#ifdef TEST_3
#undef TEST_2
#undef TEST_1
#undef TEST_4
#undef TEST_5
#undef TEST_6
#endif

#ifdef TEST_4
#undef TEST_2
#undef TEST_3
#undef TEST_1
#undef TEST_5
#undef TEST_6
#endif

#ifdef TEST_5
#undef TEST_2
#undef TEST_3
#undef TEST_4
#undef TEST_1
#undef TEST_6
#endif

#ifdef TEST_6
#undef TEST_2
#undef TEST_3
#undef TEST_4
#undef TEST_5
#undef TEST_1
#endif

#ifdef TIMER_TESTS
#undef THREAD_TESTS
#undef LIST_TESTS
#undef SEMAPHORE_TESTS
#undef EVENT_TESTS
#endif

#ifdef THREAD_TESTS
#undef TIMER_TESTS
#undef LIST_TESTS
#undef SEMAPHORE_TESTS
#undef EVENT_TESTS
#endif

#ifdef LIST_TESTS
#undef THREAD_TESTS
#undef TIMER_TESTS
#undef SEMAPHORE_TESTS
#undef EVENT_TESTS
#endif

#ifdef SEMAPHORE_TESTS
#undef THREAD_TESTS
#undef LIST_TESTS
#undef TIMER_TESTS
#undef EVENT_TESTS
#endif

#ifdef EVENT_TESTS
#undef THREAD_TESTS
#undef LIST_TESTS
#undef SEMAPHORE_TESTS
#undef TIMER_TESTS
#endif

#endif /* TESTS_H_ */
