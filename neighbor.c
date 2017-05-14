/*
 * neighbor.c
 *
 *  Created on: May 12, 2017
 *      Author: will
 */


#include"queue.h"

void exploreone(ul * arr, ul l, Queue * q, char * vcheck, ul * cnt, ul mark){


	ul i = 0;
	ul cur = 0;
	for(i = 0; i < l; i++){
		cur = arr[i];
		if(vcheck[cur] == mark)
			continue;
		if(vcheck[cur] == 0){
			vcheck[cur] = mark;
			(*cnt)++;
			qadd(q,cur);
			//printf("\t%ld(add)\t",cur);
		}
	}
}



void localngbcnt(Vertex * vlist, ul vcnt, ul s, ul k){
	Queue * qs;
	ul ngbcnt = 0;
	ul qsl = 0;

	ul tmps = 0;
	ul i = 0;
	FILE * fp2;

	ul j = k;
	ul m = 0;

	qs = (Queue*)malloc(sizeof(Queue));


	char * vcheck;
	vcheck=(char*)calloc(vcnt,sizeof(char));

	fp2 = fopen("xdgr.txt","a");

	qinit(qs);
	qadd(qs, s);


	vcheck[s] = 1;


		while(j != 0 ){
			qsl = qs->length;
			while(qsl!=0){
				tmps = qpop(qs);
				//printf("%ld-ngb of %ld, exploring %ld: \n",j,s,tmps);
				exploreone(vlist[tmps].ngb, vlist[tmps].dgr, qs, vcheck, &ngbcnt, 1);
				//printf("\n");
				qsl--;
			}
			j--;
		}

		fprintf(fp2,"%ld %ld\n", s, ngbcnt);
		printf("%ld %ld\n", s, ngbcnt);
		ngbcnt = 0;

	j = k;
	qclean(qs);




	free(vcheck);

	fclose(fp2);

}

void ngbcnt(Vertex * vlist, ul vcnt, ul k) {

	FILE * fp;
	ul s;
	fp=fopen("source.txt","r");

	ul i = 0;


	for(i = 0; i < 10000; i++){
		fscanf(fp,"%ld",&s);
		localngbcnt(vlist, vcnt, s, k);
	}

/*
	for(i = 1; i < vcnt ; i++){
		//fscanf(fp,"%ld",&s);
		localngbcnt(vlist, vcnt, i, k);
	}
*/
	fclose(fp);
}

