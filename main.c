/*
 * main.c
 *
 *  Created on: May 4, 2017
 *      Author: will
 */

#include"rabbit.h"

int main(int argc, char ** argv)
{

	printf("Welcome to the Rabbit-hopping program!\n");
	printf("size of long int is %d\n",sizeof(ul));
	clock_t begin = clock();

	//findpath_u();

	ugfindpath();

	//dgfindpath();

	clock_t end = clock();

	float t_total = ((float)(end-begin)/1000000.0F)*1000;

	printf("Rabbit hopping for %f ms, exhausted\n", t_total);

	return 0;
}
