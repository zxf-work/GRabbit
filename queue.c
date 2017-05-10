/*
 * queue.c
 *
 *  Created on: May 8, 2017
 *      Author: will
 */

#include"queue.h"

void qinit(Queue * q){
	q->head = (Unit*)malloc(sizeof(Unit));
	q->tail = (Unit*)malloc(sizeof(Unit));
	q->head->id = 0;
	q->head->next = q->tail;
	q->tail->id = 0;
	q->tail->next = NULL;
	q->last = q->head;
	q->length = 0;
}

void qadd(Queue * q, ul v){
	Unit * new;

	new = (Unit*)malloc(sizeof(Unit));

	new->id = v;
	new->next = q->last->next;

	if(q->length == 0){
		q->head->next = new;
	}
	q->last->next = new;
	q->last = new;
	q->length++;
}

ul qpop(Queue * q){

	Unit * pt;

	pt = q->head->next;
	ul v = pt->id;
	q->head->next = pt->next;
	if(q->length == 1){
		q->last = q->head;
	}
	q->length--;

	free(pt);

	return v;
}

bool qsearch(Queue * q, ul l, ul id){

	ul i = 0;
	Unit * pt;
	pt = q->head;
	while(pt->next != NULL){
		pt = pt->next;
		if(pt->id == id){
			return true;
		}
		i++;
		if(i == l){
			break;
		}

	}
	return false;
}

ul ecntq(Vertex * vlist, Queue * q, ul l){
	Unit * pt;
	ul id;
	ul ecnt = 0;
	ul i = 0;
	pt = q->head;
	while(pt->next != NULL){
		pt = pt->next;
		id = pt->id;
		if(id!=0)
			ecnt = ecnt + vlist[id].dgr;
		i++;
		if(i == l){
			break;
		}

	}
	return ecnt;
}

void qclean(Queue * q){
	Unit * pt;

	while(q->head->next != q->tail){
		pt = q->head->next;
		//pt = pt->next;
		q->head->next = pt->next;
		free(pt);
	}

	free(q);
}
