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

void dg_dgrcnt(DVertex * vlist, Edge * elist, ul vcnt, ul ecnt){
	ul i = 0;
	ul s = 0;
	ul t = 0;

	printf("Degree calculating : ");
	for(i = 0; i < ecnt; i++){
		s = elist[i].s;
		t = elist[i].t;

		vlist[s].outdgr++;
		vlist[t].indgr++;

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


void dg_adjmaker(DVertex * vlist, Edge * elist, ul vcnt, ul ecnt){
	ul i = 0;
	ul s = 0;
	ul t = 0;

	ul * inoff;
	ul * outoff;

	inoff = (ul *)calloc(vcnt, sizeof(ul));
	outoff = (ul *)calloc(vcnt, sizeof(ul));
	// offset created to generate the adjmatrix from edge list;

	for(i = 0; i < vcnt; i++){
		if(vlist[i].indgr != 0){
			vlist[i].in = (ul *)calloc(vlist[i].indgr, sizeof(ul));
		}
		if(vlist[i].outdgr != 0){
			vlist[i].out = (ul *)calloc(vlist[i].outdgr, sizeof(ul));
		}
	} // allocating space for the adjmatrix;


	printf("Adjacency list generating : ");
	for(i = 0; i< ecnt; i++){
		s = elist[i].s;
		t = elist[i].t;

		vlist[s].out[outoff[s]] = t;
		outoff[s]++;

		vlist[t].in[inoff[t]] = s;
		inoff[t]++;

		if( i % 1000000 == 0)
			printf("#");
	}
	printf("\nAdjacency list generated\n\n");

	free(outoff);
	free(inoff);

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

void dg_out_quicksort(DVertex * vlist, ul * arr, ul first, ul last){
    ul pivot, j, temp, i;

    if(first < last){
        pivot = first;
        i = first;
        j = last;

        while(i < j){
            while(vlist[arr[i]].outdgr>=vlist[arr[pivot]].outdgr && i<last)
                i++;
            while(vlist[arr[j]].outdgr<vlist[arr[pivot]].outdgr)
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
        	dg_out_quicksort(vlist,arr,first,j-1);
        if(j < last)
        	dg_out_quicksort(vlist,arr,j+1,last);
    }
}

void dg_in_quicksort(DVertex * vlist, ul * arr, ul first, ul last){
    ul pivot, j, temp, i;

    if(first < last){
        pivot = first;
        i = first;
        j = last;

        while(i < j){
            while(vlist[arr[i]].indgr>=vlist[arr[pivot]].indgr && i<last)
                i++;
            while(vlist[arr[j]].indgr<vlist[arr[pivot]].indgr)
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
        	dg_in_quicksort(vlist,arr,first,j-1);
        if(j < last)
        	dg_in_quicksort(vlist,arr,j+1,last);
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

void dg_out_merge(DVertex * vlist, ul *arr, ul size1, ul size2) {
      ul temp[size1+size2];
      ul ptr1=0;
      ul ptr2=0;

      while (ptr1+ptr2 < size1+size2) {
	      if ((ptr1 < size1 && vlist[ptr1].outdgr <= vlist[size1+ptr2].outdgr) || (ptr1 < size1 && ptr2 >= size2))
	              temp[ptr1+ptr2] = arr[ptr1++];

	      if ((ptr2 < size2 && vlist[size1+ptr2].outdgr < vlist[ptr1].outdgr) || (ptr2 < size2 && ptr1 >= size1))
	              temp[ptr1+ptr2] = arr[size1+ptr2++];
      }
      ul i = 0;

      for (i=0; i < size1+size2; i++)
	      arr[i] = temp[i];
}

void dg_out_mergesort(DVertex * vlist, ul *arr, ul size) {
     if (size == 1)
	      return;

     ul size1 = size/2;
     ul size2 = size-size1;
     dg_out_mergesort(vlist, arr, size1);
     dg_out_mergesort(vlist, arr+size1, size2);
     dg_out_merge(vlist, arr, size1, size2);
}

void dg_in_merge(DVertex * vlist, ul *arr, ul size1, ul size2) {
      ul temp[size1+size2];
      ul ptr1=0;
      ul ptr2=0;

      while (ptr1+ptr2 < size1+size2) {
	      if ((ptr1 < size1 && vlist[ptr1].indgr <= vlist[size1+ptr2].indgr) || (ptr1 < size1 && ptr2 >= size2))
	              temp[ptr1+ptr2] = arr[ptr1++];

	      if ((ptr2 < size2 && vlist[size1+ptr2].indgr < vlist[ptr1].indgr) || (ptr2 < size2 && ptr1 >= size1))
	              temp[ptr1+ptr2] = arr[size1+ptr2++];
      }
      ul i = 0;

      for (i=0; i < size1+size2; i++)
	      arr[i] = temp[i];
}

void dg_in_mergesort(DVertex * vlist, ul *arr, ul size) {
     if (size == 1)
	      return;

     ul size1 = size/2;
     ul size2 = size-size1;
     dg_in_mergesort(vlist, arr, size1);
     dg_in_mergesort(vlist, arr+size1, size2);
     dg_in_merge(vlist, arr, size1, size2);
}

void dg_adjsort(DVertex * vlist, ul vcnt){
	ul i = 0;

	for(i = 1; i < vcnt; i++){
		if(vlist[i].outdgr > 1){
			//dg_out_quicksort(vlist,vlist[i].out, 0, vlist[i].outdgr-1);
			dg_out_mergesort(vlist, vlist[i].out, vlist[i].outdgr);
		}
		if(vlist[i].indgr > 1){
			//dg_in_quicksort(vlist,vlist[i].in, 0, vlist[i].indgr-1);
			dg_in_mergesort(vlist, vlist[i].in, vlist[i].indgr);
		}
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

void report(Result * r1, Result * r2, ul l){
	FILE * fp;
	ul i = 0;
	ul acc[6];
	ul diff = 0;
	ul r1vcnt = 0;
	ul r2vcnt = 0;
	ul r1ecnt = 0;
	ul r2ecnt = 0;
	float r1tcnt = 0.0;
	float r2tcnt = 0.0;

	for(i = 0; i < 6; i++){
		acc[i] = 0;
	}

	fp=fopen("report.txt","a");
	if(fp==NULL){
		printf("Failed to export the results\n");
		exit(1);
	}

	for(i = 0; i < l; i++){
		r1vcnt += r1[i].vtotal;
		r1ecnt += r1[i].etotal;
		r1tcnt += r1[i].ttotal;

		r2vcnt += r2[i].vtotal;
		r2ecnt += r2[i].etotal;
		r2tcnt += r2[i].ttotal;

		if(r2[i].d != 0){
			diff = r2[i].d - r1[i].d;
			if(diff < 6){
				acc[diff] ++;
			}
		}

	}

	fprintf(fp,"%ld %ld %f %ld %ld %f ", r1vcnt, r1ecnt, r1tcnt, r2vcnt, r2ecnt, r2tcnt);

	for(i = 0; i < 6; i++){
		fprintf(fp, "%ld ", acc[i]);
	}
	fprintf(fp,"\n");

	fclose(fp);

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

void dg_cleanup(DVertex * vlist, DVertex * vlistsort, Edge * elist, ul vcnt){
	ul i = 0;

	for(i = 0; i < vcnt; i++){
		if(vlist[i].indgr != 0)
			free(vlist[i].in);
		if(vlist[i].outdgr != 0)
			free(vlist[i].out);
		if(vlistsort[i].indgr != 0)
			free(vlistsort[i].in);
		if(vlistsort[i].outdgr != 0)
			free(vlistsort[i].out);
	}

	//free(vlist);
	//free(elist);
}
