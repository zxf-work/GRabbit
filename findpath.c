/*
 * findpath.c
 *
 *  Created on: May 5, 2017
 *      Author: will
 */


#include"rabbit.h"

void ugfindpath(){

	ul i = 0;
	ul vcnt;
	ul ecnt;
	char gfile[16];
	FILE * fp;


	readconfig(&vcnt, &ecnt, gfile);

	printf("going to read graph %s, with %ld vertices and %ld edges\n", gfile, vcnt, ecnt);

	Edge * elist;
	elist = (Edge *)malloc(sizeof(Edge) * ecnt);
	edgeread(elist, ecnt, gfile); //read edges line-by-line from the input graph


	Vertex * vlist;
	Vertex * vlistsort;

	vlist = (Vertex *)malloc(sizeof(Vertex) * vcnt);
	for(i = 0; i < vcnt; i++){
		vlist[i].id = i;
		vlist[i].dgr = 0;
		vlist[i].ngb = NULL;
	}
	dgrcnt(vlist, elist, vcnt, ecnt); //calculate every vertex's degree
	adjmaker(vlist, elist, vcnt, ecnt); //make the adjlist

	/*
	fp=fopen("dgr.txt","w");
	for(i=1;i<vcnt;i++)
		fprintf(fp,"%ld %ld\n",vlist[i].id, vlist[i].dgr);
	fclose(fp);
	printf("dgr exported!\n");
	*/

	/*
	vlistsort = (Vertex *)malloc(sizeof(Vertex) * vcnt);

	for(i = 0; i < vcnt; i++){
		vlistsort[i].id = i;
		vlistsort[i].dgr = 0;
		vlistsort[i].ngb = NULL;
	}
	dgrcnt(vlistsort, elist, vcnt, ecnt); //calculate every vertex's degree
	adjmaker(vlistsort, elist, vcnt, ecnt); //make the adjlist
	adjsort(vlistsort, vcnt);

	PArray * bfstree;
	ul * roots;
	ul bfstreecnt = 4;

	bfstree = (PArray*)malloc(sizeof(PArray) * vcnt);
	roots = calloc(bfstreecnt, sizeof(ul));

	getroots(vlist, vcnt, roots, bfstreecnt);


	for(i = 0; i < vcnt; i++){
		bfstree[i].parent = calloc(bfstreecnt, sizeof(ul));
		bfstree[i].lvl = calloc(bfstreecnt, sizeof(ul));
	}

	getbfstree(vlist, bfstree, roots, vcnt, bfstreecnt);
	*/

	printf("\nRabbit gets ready ... starts hopping ...\n");

	//ul k = 4;
	//ngbcnt(vlist, vcnt, k);

	//shortpath(vlist, vlistsort, bfstree, vcnt);


	ug_lmtest(vlist,vcnt);

	//cleanup(vlist, elist, vcnt);


	free(vlist);
	free(elist);
	free(vlistsort);
	//free(bfstree);

}

void dgfindpath(){

	ul i = 0;
	ul vcnt;
	ul ecnt;
	char gfile[16];
	FILE * fp;


	readconfig(&vcnt, &ecnt, gfile);

	printf("going to read graph %s, with %ld vertices and %ld edges\n", gfile, vcnt, ecnt);

	Edge * elist;
	elist = (Edge *)malloc(sizeof(Edge) * ecnt);
	edgeread(elist, ecnt, gfile); //read edges line-by-line from the input graph


	DVertex * vlist;
	DVertex * vlistsort;

	vlist = (DVertex *)malloc(sizeof(DVertex) * vcnt);
	for(i = 0; i < vcnt; i++){
		vlist[i].id = i;
		vlist[i].indgr = 0;
		vlist[i].outdgr = 0;
		vlist[i].in = NULL;
		vlist[i].out = NULL;
	}
	dg_dgrcnt(vlist, elist, vcnt, ecnt); //calculate every vertex's degree
	dg_adjmaker(vlist, elist, vcnt, ecnt); //make the adjlist

	/*
	fp=fopen("dgr.txt","w");
	for(i=1;i<vcnt;i++)
		fprintf(fp,"%ld %ld\n",vlist[i].id, vlist[i].outdgr*vlist[i].indgr);
	fclose(fp);
	printf("dgr exported!\n");
	*/


	/*
	vlistsort = (DVertex *)malloc(sizeof(DVertex) * vcnt);

	for(i = 0; i < vcnt; i++){
		vlistsort[i].id = i;
		vlistsort[i].indgr = 0;
		vlistsort[i].outdgr = 0;
		vlistsort[i].in = NULL;
		vlistsort[i].out = NULL;
	}
	dg_dgrcnt(vlistsort, elist, vcnt, ecnt); //calculate every vertex's degree
	dg_adjmaker(vlistsort, elist, vcnt, ecnt); //make the adjlist
	dg_adjsort(vlistsort, vcnt);
	
	*/

	printf("Rabbit gets ready ... starts hopping ...\n");

	/*********
	 * 3-hop neighbor count, intuition is to test if skewed 3-hop count makes direction optimized bfs better
	 */
	/*
	ul k = 3;
	ngbcnt(vlist, vcnt, k);
	*/

	//dg_diameter(vlist, vcnt);//diameter estimation function

	//dg_shortpath(vlist, vlistsort, vcnt);

	dg_lmtest(vlist, vcnt);


	dg_cleanup(vlist, vlistsort, elist, vcnt);


	free(vlist);
	free(elist);
	free(vlistsort);

}
