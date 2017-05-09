/*
 * findpath.c
 *
 *  Created on: May 5, 2017
 *      Author: will
 */


#include"rabbit.h"

void findpath(){

	ul i = 0;
	ul vcnt;
	ul ecnt;
	char gfile[16];

	readconfig(&vcnt, &ecnt, gfile);

	printf("going to read graph %s, with %ld vertices and %ld edges\n", gfile, vcnt, ecnt);

	Edge * elist;
	elist = (Edge *)malloc(sizeof(Edge) * ecnt);
	edgeread(elist, ecnt, gfile); //read edges line-by-line from the input graph


	Vertex * vlist;
	Vertex * vlist_sort;

	vlist = (Vertex *)malloc(sizeof(Vertex) * vcnt);
	for(i = 0; i < vcnt; i++){
		vlist[i].id = 0;
		vlist[i].dgr = 0;
		vlist[i].ngb = NULL;
	}
	dgrcnt(vlist, elist, vcnt, ecnt); //calculate every vertex's degree
	adjmaker(vlist, elist, vcnt, ecnt); //make the adjlist

	vlist_sort = (Vertex *)malloc(sizeof(Vertex) * vcnt);
	for(i = 0; i < vcnt; i++){
		vlist_sort[i].id = 0;
		vlist_sort[i].dgr = 0;
		vlist_sort[i].ngb = NULL;
	}
	dgrcnt(vlist_sort, elist, vcnt, ecnt); //calculate every vertex's degree
	adjmaker(vlist_sort, elist, vcnt, ecnt); //make the adjlist
	adjsort(vlist_sort, vcnt);



	printf("Rabbit gets ready ... starts hopping ...\n");

	shortpath(vlist, vlist_sort, vcnt);

	//cleanup(vlist, elist, vcnt);


	free(vlist);
	free(elist);

}
