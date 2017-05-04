/*
 * main.c
 *
 *  Created on: May 4, 2017
 *      Author: will
 */

#include"rabbit.h"

int main(int argc, char ** argv)
{


	printf("Rabbit gets ready ...\n");

	printf("Rabbit starts hopping ...\n");

	clock_t begin = clock();

	clock_t end = clock();

	float t_total = ((float)(end-begin)/1000000.0F)/1000;

	printf("Rabbit hopping for %f ms, exhausted\n", t_total);

	return 0;
}
