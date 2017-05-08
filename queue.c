/*
 * queue.c
 *
 *  Created on: May 8, 2017
 *      Author: will
 */

#include"queue.h"

void qinit(Queue * q){
	q->head->id = 0;
	q->head->next = q->tail;
	q->tail->id = 0;
	q->tail->next = NULL;
	q->last = q->head;
	q->length = 0;
}

void qadd(Queue * q, ul v){
	Unit new;
	new.id = v;
	new.next = q->last->next;
	q->last->next = &new;
	q->last = &new;
}

ul qpop(Queue * q){

	Unit * pt;

	pt = q->head->next;
	ul v = pt->id;
	q->head = pt->next;

	free(pt);

	return v;
}

void qclean(Queue * q){
	Unit * pt;

	while(q->head->next != q->tail){
		pt = q->head;
		pt = pt->next;
		q->head->next = pt->next;
		free(pt);
	}

	free(q);
}
