/*
 * shortpath.c
 *
 *  Created on: May 5, 2017
 *      Author: will
 */

#include"rabbit.h"

void shortpath(Vertex * vlist, Vertex * vlistsort, ul vcnt) {

	FILE * fp;
	ul qcnt = 1000;
	ul * query = NULL;
	Result * res;
	Result * resl;
	Result * resu;
	Result * resr;

	query = (ul*)calloc(qcnt*2, sizeof(ul));
	res = (Result*)malloc(sizeof(Result) * qcnt);
	resl = (Result*)malloc(sizeof(Result) * qcnt);
	resu = (Result*)malloc(sizeof(Result) * qcnt);
	resr = (Result*)malloc(sizeof(Result) * qcnt);

	rinit(res, qcnt);
	rinit(resl, qcnt);
	rinit(resu, qcnt);
	rinit(resr, qcnt);

	fp=fopen("stpath-query.txt","r");

	ul i = 0;

	for(i = 0; i < qcnt * 2; i++){
		fscanf(fp,"%ld",&query[i]);
	}
	fclose(fp);

	ul s = 0;
	ul t = 0;

	//baseline BFS
	for(i = 0; i < qcnt; i++){
		s = query[2*i];
		t = query[2*i+1];
		bfs(vlist, vcnt, s, t, &(res[i]));
	}
	//rinit(res, qcnt);


	ul k = 1;

	//S1: k-limit
	while(k < 128){
		printf("\n%ld-limit\n",k);

		for(i = 0; i < qcnt; i++){
			s = query[2*i];
			t = query[2*i+1];
			klimit(vlistsort, vcnt, s, t, k, &(resl[i]));

		}
		report(res,resl,qcnt);
		rinit(resl, qcnt);
		k = k * 2;
	}

	k = 1;

	//S2: k-unvisit
	while(k<128){
		printf("\n%ld-unvisit\n",k);

		for(i = 0; i < qcnt; i++){
			s = query[2*i];
			t = query[2*i+1];
			kunvisit(vlistsort, vcnt, s, t, k, &(resu[i]));
		}
		report(res,resu,qcnt);
		rinit(resu, qcnt);

		k = k * 2;
	}


	k = 1;
	fp = fopen("graph.cfg","r");
	char gfile[32];
	char order[16];
	ul ecntreduce;
	ul vcntreduce;

	fscanf(fp,"%s",gfile);
	fscanf(fp,"%ld",&vcntreduce);
	fscanf(fp,"%ld",&ecntreduce);

	Edge * elistreduce;

	Vertex * vlistreduce;

	//S3: k-reduce

	while(k<128){

		fscanf(fp,"%s",gfile);
		fscanf(fp,"%ld",&vcntreduce);
		fscanf(fp,"%ld",&ecntreduce);
		printf("going to read graph %s, with %ld vertices and %ld edges\n", gfile, vcntreduce, ecntreduce);

		elistreduce = (Edge *)malloc(sizeof(Edge) * ecntreduce);
		edgeread(elistreduce, ecntreduce, gfile); //read edges line-by-line from the input graph

		vlistreduce = (Vertex *)malloc(sizeof(Vertex) * vcntreduce);
		for(i = 0; i < vcnt; i++){
			vlistreduce[i].id = i;
			vlistreduce[i].dgr = 0;
			vlistreduce[i].ngb = NULL;
		}
		dgrcnt(vlistreduce, elistreduce, vcntreduce, ecntreduce); //calculate every vertex's degree
		adjmaker(vlistreduce, elistreduce, vcntreduce, ecntreduce); //make the adjlist

		printf("\n%ld-reduce\n",k);

		for(i = 0; i < qcnt; i++){
			s = query[2*i];
			t = query[2*i+1];
			kreduce(vlistreduce, vlist, vcnt, s, t, &(resr[i]));
		}
		report(res, resr, qcnt);
		rinit(resr, qcnt);
		k = k * 2;

		free(vlistreduce);
		free(elistreduce);
	}




}
