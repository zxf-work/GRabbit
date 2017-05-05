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

typedef unsigned long  ul;

typedef struct v{
	ul id;
	ul * ngb;
	ul dgr;
}Vertex;

typedef struct e{
	ul s;
	ul t;
}Edge;



#endif /* RABBIT_H_ */
