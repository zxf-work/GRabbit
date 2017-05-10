/*
 * util.c
 *
 *  Created on: May 5, 2017
 *      Author: will
 */

#include"rabbit.h"


void readconfig(ul * a, ul * b, char arr[16]){
	FILE * fp;


	fp=fopen("graph.cfg","r");
	if(fp == NULL){
		printf("Failed to load the graph.cfg file\n");
		exit(1);
	}

	fscanf(fp, "%s", arr);
	fscanf(fp, "%ld", a);
	fscanf(fp, "%ld", b);

	fclose(fp);
}

void edgeread(Edge * elist, ul cnt, char str[16]){

	FILE * fp;

	fp = fopen(str, "r");
	if(fp == NULL){
		printf("Failed to load graph file %s\n", str);
		exit(1);
	}

	ul i = 0;
	ul s = 0;
	ul t = 0;

	for(i = 0; i < cnt; i++){
		elist[i].s = 0;
		elist[i].t = 0;
	}

	printf("Loading edges : ");
	for(i = 0; i < cnt; i++){
		fscanf(fp,"%ld %ld", &s, &t);
		elist[i].s = s;
		elist[i].t = t;
		if( i % 1000000 == 0)
			printf("#");
	}
	printf("\nEdges loaded\n\n");

	fclose(fp);

}

void dgrcnt(Vertex * vlist, Edge * elist, ul vcnt, ul ecnt){
	ul i = 0;
	ul s = 0;
	ul t = 0;

	printf("Degree calculating : ");
	for(i = 0; i < ecnt; i++){
		s = elist[i].s;
		t = elist[i].t;

		vlist[s].dgr++;
		vlist[t].dgr++;

		if( i % 1000000 == 0)
			printf("#");
	}
	printf("\nDegree calculated\n\n");

}

void adjmaker(Vertex * vlist, Edge * elist, ul vcnt, ul ecnt){
	ul i = 0;
	ul s = 0;
	ul t = 0;

	ul * off;

	off = (ul *)calloc(vcnt, sizeof(ul));
	// offset created to generate the adjmatrix from edge list;

	for(i = 0; i < vcnt; i++){
		if(vlist[i].dgr != 0){
			vlist[i].ngb = (ul *)calloc(vlist[i].dgr, sizeof(ul));
		}
	} // allocating space for the adjmatrix;


	printf("Adjacency list generating : ");
	for(i = 0; i< ecnt; i++){
		s = elist[i].s;
		t = elist[i].t;

		vlist[s].ngb[off[s]] = t;
		off[s]++;

		vlist[t].ngb[off[t]] = s;
		off[t]++;

		if( i % 1000000 == 0)
			printf("#");
	}
	printf("\nAdjacency list generated\n\n");

	free(off);

}



void quicksort(Vertex * vlist, ul * arr, ul first, ul last){
    ul pivot, j, temp, i;

    if(first < last){
        pivot = first;
        i = first;
        j = last;

        while(i < j){
            while(vlist[arr[i]].dgr>=vlist[arr[pivot]].dgr && i<last)
                i++;
            while(vlist[arr[j]].dgr<vlist[arr[pivot]].dgr)
                j--;
            if(i<j){
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }

        temp = arr[pivot];
        arr[pivot]=arr[j];
        arr[j]=temp;
        if(j >= 1)
        	quicksort(vlist,arr,first,j-1);
        if(j < last)
        	quicksort(vlist,arr,j+1,last);
    }
}

void adjsort(Vertex * vlist, ul vcnt){
	ul i = 0;

	for(i = 1; i < vcnt; i++){
		if(vlist[i].dgr>1)
		quicksort(vlist, vlist[i].ngb, 0, vlist[i].dgr-1);
		//printf("%ld: %ld ...\n", i, vlist[i].ngb[0])
	}
}

void rinit(Result * res, ul qcnt){
	ul i = 0;
	for(i = 0; i < qcnt; i++){
		res[i].s = 0;
		res[i].t = 0;
		res[i].d = 0;
		res[i].vtotal = 0;
		res[i].etotal = 0;
		res[i].ttotal = 0.0;
	}
}
void cleanup(Vertex * vlist, Edge * elist, ul vcnt){
	ul i = 0;

	for(i = 0; i < vcnt; i++){
		if(vlist[i].dgr != 0)
			free(vlist[i].ngb);
	}

	//free(vlist);
	//free(elist);
}
