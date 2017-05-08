/*
 * queue.h
 *
 *  Created on: May 8, 2017
 *      Author: will
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#include"rabbit.h"

typedef struct u{
	ul id;
	struct u * next;
}Unit;

typedef struct q{
	Unit * head;
	Unit * tail;
	Unit * last;
	ul length;
}Queue;


#endif /* QUEUE_H_ */
