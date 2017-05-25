#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct n{
    long id;
    long dgr;
}nb;

typedef struct v{
    long id;
    long * ngb;
    long dgr;
}vertex;

int cmpfunc(const void * a, const void * b){
    nb  x = *(const nb *)a;
    nb  y = *(const nb *)b;

    if(x.dgr<y.dgr)
        return 1;
    else if(x.dgr>y.dgr)
        return -1;

    return 0;
}

void sort(vertex * vlist, vertex v){

    nb * arr;
    arr=(nb*)malloc(sizeof(nb)*v.dgr);
    long i;
    for(i=0;i<v.dgr;i++){
        arr[i].id=v.ngb[i];
        arr[i].dgr=vlist[v.ngb[i]].dgr;
    }
    qsort(arr,v.dgr,sizeof(nb),cmpfunc);
    for(i=0;i<v.dgr;i++){
        v.ngb[i]=arr[i].id;
    }
    free(arr);
}


void bfs_init() {
    long vcnt = 39454464;
	long ecnt = 783027125;

	vertex * adjlist = NULL;
	long * edgelist = NULL;
	long * off = NULL;

	FILE * fp;

	/**allocating space**/
	printf("Loading and allocating space ... \n");

	long i = 0;
	long j = 0;
	long k = 0;

	edgelist = (long*)calloc(ecnt*2,sizeof(long ));
    adjlist = (vertex *)malloc(sizeof(vertex)*vcnt);
	if (adjlist == NULL)
		printf("Failed to allocate space for adjacency list\n");

    for(i=1;i<vcnt;i++){
        adjlist[i].id=i;
        adjlist[i].ngb=NULL;
        adjlist[i].dgr=0;
    }

	fp = fopen("uk-2005.ungraph", "r");
	if (fp == NULL) {
		printf("Failed to read the input file\n");
		exit(1);
	}
	for (i = 0; i < ecnt*2; ) {
		fscanf(fp, "%ld %ld", &j, &k);
		//printf("%ld-->%ld\n",j,k);
		edgelist[i] = j;
		edgelist[i+1] = k;
        i=i+2;
		adjlist[j].dgr++;
        adjlist[k].dgr++;
	}
    fclose(fp);

	printf("constructing the adjacency list\n");


	for (i = 1; i < vcnt; i++) {
		//printf("%ld %ld\n",i,dgr[i]);
		if (adjlist[i].dgr > 0) {
			adjlist[i].ngb = (long*)calloc(adjlist[i].dgr,sizeof(long));
		}
	}
	printf("adjlist space allocated\n");

	off = (long*)calloc(vcnt, sizeof(long));


	long s, t;
	for (i = 0; i < ecnt*2; ) {
		s = edgelist[i];
		t = edgelist[i+1];
        i=i+2;
		//printf("%ld-->%ld\n", s, t);
        //getchar();
		adjlist[s].ngb[off[s]] = t;
		off[s]++;
		adjlist[t].ngb[off[t]] = s;
		off[t]++;
	}
	printf("Loading complete\n");

    long scale = vcnt/100;
    long u=0;
    for(i=1;i<vcnt;i++){
       // if(i%10000 == 0)
       // printf("+");
       if(i%scale == 0)
           printf("<%ld>\n",u++);
        if(adjlist[i].dgr>1){
            sort(adjlist, adjlist[i]);
            //printf("sorting %ld's %ld neighbors\n",i,dgr[i]);
            //quicksort(adjlist[i],dgr,0,dgr[i]-1);
            //mergesort(adjlist[i], dgr, dgr[i]);
            //for(j=0;j<adjlist[i].dgr;j++){
            //    printf("%ld[%ld] ",adjlist[i].ngb[j],adjlist[adjlist[i].ngb[j]].dgr);
            //}
            //printf("\n");
            //getchar();

        }
    }
    printf("Neighbor sorting complete\n");

    
    fp=fopen("tmp-1","w");
    k=1;
    for(i=1;i<vcnt;i++){
        if(adjlist[i].dgr<k){
            for(j=0;j<adjlist[i].dgr;j++){
                fprintf(fp,"%ld %ld\n",i,adjlist[i].ngb[j]);
            }
        }
        else{
            for(j=0;j<k;j++){
                fprintf(fp,"%ld %ld\n",i,adjlist[i].ngb[j]);
            }
        }
    }

    fp=fopen("tmp-2","w");
    k=2;
    for(i=1;i<vcnt;i++){
        if(adjlist[i].dgr<k){
            for(j=0;j<adjlist[i].dgr;j++){
                fprintf(fp,"%ld %ld\n",i,adjlist[i].ngb[j]);
            }
        }
        else{
            for(j=0;j<k;j++){
                fprintf(fp,"%ld %ld\n",i,adjlist[i].ngb[j]);
            }
        }
    }
    fp=fopen("tmp-4","w");
    k=4;
    for(i=1;i<vcnt;i++){
        if(adjlist[i].dgr<k){
            for(j=0;j<adjlist[i].dgr;j++){
                fprintf(fp,"%ld %ld\n",i,adjlist[i].ngb[j]);
            }
        }
        else{
            for(j=0;j<k;j++){
                fprintf(fp,"%ld %ld\n",i,adjlist[i].ngb[j]);
            }
        }
    }
    fp=fopen("tmp-8","w");
    k=8;
    for(i=1;i<vcnt;i++){
        if(adjlist[i].dgr<k){
            for(j=0;j<adjlist[i].dgr;j++){
                fprintf(fp,"%ld %ld\n",i,adjlist[i].ngb[j]);
            }
        }
        else{
            for(j=0;j<k;j++){
                fprintf(fp,"%ld %ld\n",i,adjlist[i].ngb[j]);
            }
        }
    }
    fp=fopen("tmp-16","w");
    k=16;
    for(i=1;i<vcnt;i++){
        if(adjlist[i].dgr<k){
            for(j=0;j<adjlist[i].dgr;j++){
                fprintf(fp,"%ld %ld\n",i,adjlist[i].ngb[j]);
            }
        }
        else{
            for(j=0;j<k;j++){
                fprintf(fp,"%ld %ld\n",i,adjlist[i].ngb[j]);
            }
        }
    }
    fp=fopen("tmp-32","w");
    k=32;
    for(i=1;i<vcnt;i++){
        if(adjlist[i].dgr<k){
            for(j=0;j<adjlist[i].dgr;j++){
                fprintf(fp,"%ld %ld\n",i,adjlist[i].ngb[j]);
            }
        }
        else{
            for(j=0;j<k;j++){
                fprintf(fp,"%ld %ld\n",i,adjlist[i].ngb[j]);
            }
        }
    }
    fp=fopen("tmp-64","w");
    k=64;
    for(i=1;i<vcnt;i++){
        if(adjlist[i].dgr<k){
            for(j=0;j<adjlist[i].dgr;j++){
                fprintf(fp,"%ld %ld\n",i,adjlist[i].ngb[j]);
            }
        }
        else{
            for(j=0;j<k;j++){
                fprintf(fp,"%ld %ld\n",i,adjlist[i].ngb[j]);
            }
        }
    }
    /*
    fp=fopen("tmp-2","w");
    k=2;
    for(i=1;i<vcnt;i++){
        if(dgr[i]<k){
            for(j=0;j<dgr[i];j++){
                fprintf(fp,"%ld %ld\n",i,adjlist[i][j]);
            }
        }
        else{
            for(j=0;j<k;j++){
                fprintf(fp,"%ld %ld\n",i,adjlist[i][j]);
            }
        }
    }

    fp=fopen("tmp-4","w");
    k=4;
    for(i=1;i<vcnt;i++){
        if(dgr[i]<k){
            for(j=0;j<dgr[i];j++){
                fprintf(fp,"%ld %ld\n",i,adjlist[i][j]);
            }
        }
        else{
            for(j=0;j<k;j++){
                fprintf(fp,"%ld %ld\n",i,adjlist[i][j]);
            }
        }
    }


    fp=fopen("tmp-8","w");
    k=8;
    for(i=1;i<vcnt;i++){
        if(dgr[i]<k){
            for(j=0;j<dgr[i];j++){
                fprintf(fp,"%ld %ld\n",i,adjlist[i][j]);
            }
        }
        else{
            for(j=0;j<k;j++){
                fprintf(fp,"%ld %ld\n",i,adjlist[i][j]);
            }
        }
    }


    fp=fopen("tmp-16","w");
    k=16;
    for(i=1;i<vcnt;i++){
        if(dgr[i]<k){
            for(j=0;j<dgr[i];j++){
                fprintf(fp,"%ld %ld\n",i,adjlist[i][j]);
            }
        }
        else{
            for(j=0;j<k;j++){
                fprintf(fp,"%ld %ld\n",i,adjlist[i][j]);
            }
        }
    }


    fp=fopen("tmp-32","w");
    k=32;
    for(i=1;i<vcnt;i++){
        if(dgr[i]<k){
            for(j=0;j<dgr[i];j++){
                fprintf(fp,"%ld %ld\n",i,adjlist[i][j]);
            }
        }
        else{
            for(j=0;j<k;j++){
                fprintf(fp,"%ld %ld\n",i,adjlist[i][j]);
            }
        }
    }


    fp=fopen("tmp-64","w");
    k=64;
    for(i=1;i<vcnt;i++){
        if(dgr[i]<k){
            for(j=0;j<dgr[i];j++){
                fprintf(fp,"%ld %ld\n",i,adjlist[i][j]);
            }
        }
        else{
            for(j=0;j<k;j++){
                fprintf(fp,"%ld %ld\n",i,adjlist[i][j]);
            }
        }
    }
   */ 

    /*
	for (i = 0; i < vcnt; i++)
		off[i] = 0;

	queue = (long *)malloc(sizeof(long)*vcnt);
	for (i = 0; i < vcnt; i++)
		queue[i] = 0;

	rs = (long *)malloc(sizeof(long)*vcnt);
	for (i = 0; i < vcnt; i++)
		rs[i] = 0;


    long source = 0;
    long dest = 0;
    fp=fopen("stpath-query.txt","r");
    while(!feof(fp)){
        fscanf(fp,"%ld",&source);
        fscanf(fp,"%ld",&dest);
        //printf("BFS search from %ld\n", source);

        stpath_u(adjlist,dgr,queue,rs,vcnt,source,dest);
        for(i=0;i<vcnt;i++){
            queue[i] = 0;
            rs[i] = 0;
        }
    }

    */
	free(off);
	free(edgelist);

}

long main(long argc, char ** argv) {


	bfs_init();


	printf("Done!\n");
	//getchar();
	return 0;
}

void merge(long *arr, long * ref, long size1, long size2) {
    long * temp;
    temp=(long*)malloc(sizeof(long)*(size1+size2));
    long ptr1=0, ptr2=0;

    while (ptr1+ptr2 < size1+size2) {
        if (ptr1 < size1 && ref[ptr1] <= ref[size1+ptr2] || ptr1 < size1 && ptr2 >= size2)
              temp[ptr1+ptr2] = arr[size1+ptr2++];
              //temp[ptr1+ptr2] = arr[ptr1++];

        if (ptr2 < size2 && ref[size1+ptr2] < ref[ptr1] || ptr2 < size2 && ptr1 >= size1)
              temp[ptr1+ptr2] = arr[ptr1++];
              //temp[ptr1+ptr2] = arr[size1+ptr2++];
    }
    long i = 0;

    for (i=0; i < size1+size2; i++)
        arr[i] = temp[i];
    free(temp);
}

void mergesort(long *arr, long * ref, long size) {
    if (size == 1)
        return;  

    long size1 = size/2;
    long  size2 = size-size1;
	mergesort(arr, ref, size1);
	mergesort(arr+size1, ref, size2);
	merge(arr, ref,  size1, size2);
}

void quicksort(long * arr, long * dgr, long first, long last){
    long pivot, j, temp, i;

    if(first < last){
        pivot = first;
        i = first;
        j = last;

        while(i < j){
            while(dgr[arr[i]]>=dgr[arr[pivot]] && i<last)
                i++;
            while(dgr[arr[j]]<dgr[arr[pivot]])
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
        if(first < j-1)
        quicksort(arr,dgr,first,j-1);
        if(j+1 < last )
        quicksort(arr,dgr,j+1,last);
    }
}
