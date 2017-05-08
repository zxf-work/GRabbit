/*
 * shortpath.c
 *
 *  Created on: May 5, 2017
 *      Author: will
 */

#include"rabbit.h"

void shortpath(Vertex * vlist, ul vcnt) {

	FILE * fp;
	ul qcnt = 1000;
	ul * query = NULL;
	Result * res;

	query = (ul*)calloc(qcnt*2, sizeof(ul));
	res = (Result*)malloc(sizeof(Result) * qcnt);

	rinit(res, qcnt);

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
			bfs(vlist, vcnt, s, t, &res[i]);

	}
	rinit(res, qcnt);

	ul k = 1;
	//S1: k-limited
	klimit(vlist, vcnt, s, t, k, res);

	//S2: k-unvisited
	kunvisit(vlist, vcnt, s, t, k, res);

	//S3: k-reduced
	kreduce(vlist, vcnt, s, t, k, res);

}
