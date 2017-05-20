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
#include<stdbool.h>

typedef unsigned long  ul;

typedef struct v{
	ul id;
	ul * ngb;
	ul dgr;
}Vertex;

typedef struct dv{
    ul id;
    ul * in;
    ul * out;
    ul indgr;
    ul outdgr;
}DVertex;

typedef struct e{
	ul s;
	ul t;
}Edge;

typedef struct r{
	ul s;
	ul t;
	ul d;
	ul mid;
	ul vtotal;
	ul etotal;
	float ttotal;
}Result;

#endif /* RABBIT_H_ */
