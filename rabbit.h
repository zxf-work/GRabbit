/*
 * rabbit.h
 *
 *  Created on: May 4, 2017
 *      Author: will
 */

#ifndef RABBIT_H_
#define RABBIT_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

typedef struct v{
	unsigned long id;
	unsigned long * ngb;
	unsigned long dgr;
}Vertex;

typedef struct e{
	unsigned long s;
	unsigned long t;
}Edge;



#endif /* RABBIT_H_ */
