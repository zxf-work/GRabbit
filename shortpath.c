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
	Result * resv;
	Result * resd;
	Result * resdv;
	Result * resee;

	query = (ul*)calloc(qcnt*2, sizeof(ul));
	res = (Result*)malloc(sizeof(Result) * qcnt);
	resl = (Result*)malloc(sizeof(Result) * qcnt);
	resu = (Result*)malloc(sizeof(Result) * qcnt);
	resr = (Result*)malloc(sizeof(Result) * qcnt);
	resv = (Result*)malloc(sizeof(Result) * qcnt);
	resd = (Result*)malloc(sizeof(Result) * qcnt);
	resdv = (Result*)malloc(sizeof(Result) * qcnt);
	resee = (Result*)malloc(sizeof(Result) * qcnt);

	rinit(res, qcnt);
	rinit(resl, qcnt);
	rinit(resu, qcnt);
	rinit(resr, qcnt);
	rinit(resv, qcnt);
	rinit(resd, qcnt);
	rinit(resdv, qcnt);
	rinit(resee, qcnt);


	fp=fopen("stpath-query.txt","r");

	ul i = 0;

	for(i = 0; i < qcnt * 2; i++){
		fscanf(fp,"%ld",&query[i]);
	}
	fclose(fp);

	ul s = 0;
	ul t = 0;

	//baseline BFS
	printf("Baseline BFS\n");
	for(i = 0; i < qcnt; i++){
		s = query[2*i];
		t = query[2*i+1];
		bfs(vlist, vcnt, s, t, &(res[i]));
	}
	//rinit(res, qcnt);

	//direction optimized BFS
	printf("Direction optimized BFS\n");
	for(i = 0; i < qcnt; i++){
		s = query[2*i];
		t = query[2*i+1];
		drtopt(vlist, vcnt, s, t, &(resd[i]));
	}
	report(res, resd, qcnt);

	//one-vertex BFS
	printf("Vertex-Vertex BFS\n");
	for(i = 0; i < qcnt; i++){
		s = query[2*i];
		t = query[2*i+1];
		vvbfs(vlist, vcnt, s, t, &(resv[i]));
	}
	report(res,resv,qcnt);

	/*
	//direction first one-vertex BFS
	printf("Drt-VV BFS\n");
	for(i = 0; i < qcnt; i++){
		s = query[2*i];
		t = query[2*i+1];
		dv(vlist, vcnt, s, t, &(resdv[i]));
	}
	report(res,resdv,qcnt);
	*/

	//edge-by-edge BFS
	printf("Edge-by-Edge BFS\n");
	for(i = 0; i < qcnt; i++){
		s = query[2*i];
		t = query[2*i+1];
		ee(vlist, vcnt, s, t, &(resee[i]));
	}
	report(res,resee,qcnt);

	/********BFS-K TEST***********/
	ul k = 1;

	//S1: k-limit
	while(k < 1024){
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

	/*
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

	********************************/


}


void dg_shortpath(DVertex * vlist, DVertex * vlistsort, ul vcnt) {

	FILE * fp;
	ul qcnt = 1000;
	ul * query = NULL;
	Result * res;
	Result * resl;
	Result * resu;
	Result * resr;
	Result * resv;
	Result * resd;

	query = (ul*)calloc(qcnt*2, sizeof(ul));
	res = (Result*)malloc(sizeof(Result) * qcnt);
	resl = (Result*)malloc(sizeof(Result) * qcnt);
	resu = (Result*)malloc(sizeof(Result) * qcnt);
	resr = (Result*)malloc(sizeof(Result) * qcnt);
	resv = (Result*)malloc(sizeof(Result) * qcnt);
	resd = (Result*)malloc(sizeof(Result) * qcnt);

	rinit(res, qcnt);
	rinit(resl, qcnt);
	rinit(resu, qcnt);
	rinit(resr, qcnt);
	rinit(resv, qcnt);
	rinit(resd, qcnt);


	fp=fopen("stpath-query.txt","r");

	ul i = 0;

	for(i = 0; i < qcnt * 2; i++){
		fscanf(fp,"%ld",&query[i]);
	}
	fclose(fp);

	ul s = 0;
	ul t = 0;

	//baseline BFS
	printf("Baseline dg_BFS\n");
	for(i = 0; i < qcnt; i++){
		s = query[2*i];
		t = query[2*i+1];
		dg_bfs(vlist, vcnt, s, t, &(res[i]));
	}
	//rinit(res, qcnt);

	//direction optimized BFS
	printf("Direction optimized BFS\n");
	for(i = 0; i < qcnt; i++){
		s = query[2*i];
		t = query[2*i+1];
		dg_drtopt(vlist, vcnt, s, t, &(resd[i]));
	}
	report(res, resd, qcnt);

	/*
	//one-vertex BFS
	printf("Vertex-Vertex BFS\n");
	for(i = 0; i < qcnt; i++){
		s = query[2*i];
		t = query[2*i+1];
		dg_vvbfs(vlist, vcnt, s, t, &(resv[i]));
	}
	report(res,resv,qcnt);

	*/

	/********BFS-K TEST***********
	ul k = 1;

	//S1: k-limit
	while(k < 128){
		printf("\n%ld-limit\n",k);

		for(i = 0; i < qcnt; i++){
			s = query[2*i];
			t = query[2*i+1];
			dg_klimit(vlistsort, vcnt, s, t, k, &(resl[i]));

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
			dg_kunvisit(vlistsort, vcnt, s, t, k, &(resu[i]));
		}
		report(res,resu,qcnt);
		rinit(resu, qcnt);

		k = k * 2;
	}

	/*
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

	********************************/


}
