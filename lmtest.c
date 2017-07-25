/*
 * lmtest.c
 *
 *  Created on: Jul 24, 2017
 *      Author: will
 */

#include"rabbit.h"
#include"bfs.h"



void dg_ssbfs_lm2v(DVertex * vlist, ul vcnt, ul s, Queue * qs, char * vcheck, ul ** lm2v, ul off){

	ul qsl = 0;
	ul hopcnt = 0;
	ul cur = 0;
	ul i = 0;

	lm2v[s][off] = 0;

	while(qs->length != 0 ){

		// set the range to traverse
		qsl = qs->length;

		// search from s-side
		//printf("qsl = %ld\n", qsl);
		while(qsl != 0){
			s = qpop(qs);
			for(i=0;i<vlist[s].outdgr;i++){
				cur = vlist[s].out[i];
				if(vcheck[cur]==0){
					vcheck[cur]=1;
					lm2v[cur][off]=hopcnt+1;
					qadd(qs,cur);
				}
			}
			qsl--;
		}
		hopcnt++;
	}
}

void dg_ssbfs_v2lm(DVertex * vlist, ul vcnt, ul s, Queue * qs, char * vcheck, ul ** v2lm, ul off){

	ul qsl = 0;
	ul hopcnt = 0;
	ul cur = 0;
	ul i = 0;

	v2lm[s][off] = 0;

	while(qs->length != 0 ){

		// set the range to traverse
		qsl = qs->length;

		// search from s-side
		//printf("qsl = %ld\n", qsl);
		while(qsl != 0){
			s = qpop(qs);
			for(i=0;i<vlist[s].indgr;i++){
				cur = vlist[s].in[i];
				if(vcheck[cur]==0){
					vcheck[cur]=1;
					v2lm[cur][off]=hopcnt+1;
					qadd(qs,cur);
				}
			}
			qsl--;
		}
		hopcnt++;
	}
}


void lm2vload(DVertex * vlist, ul vcnt, ul s, ul ** lm2v, ul off){

	Queue * qs;

	qs = (Queue*)malloc(sizeof(Queue));

	qinit(qs);
	qadd(qs, s);

	char * vcheck;

	vcheck=(char*)calloc(vcnt,sizeof(char));
	vcheck[s] = 1;

	dg_ssbfs_lm2v(vlist, vcnt, s, qs, vcheck, lm2v, off);

	qclean(qs);
	free(vcheck);

}

void v2lmload(DVertex * vlist, ul vcnt, ul s, ul ** v2lm, ul off){

	Queue * qs;

	qs = (Queue*)malloc(sizeof(Queue));

	qinit(qs);
	qadd(qs, s);

	char * vcheck;

	vcheck=(char*)calloc(vcnt,sizeof(char));
	vcheck[s] = 1;

	dg_ssbfs_v2lm(vlist, vcnt, s, qs, vcheck, v2lm, off);

	qclean(qs);
	free(vcheck);

}

ul ** lm2vcompute(DVertex * vlist, ul * lmarray, ul vcnt, ul lmcnt, ul ** lm2v){
	ul i = 0;
	ul s = 0;
	for(i=0;i<lmcnt;i++){
		s = lmarray[i];
		lm2vload(vlist, vcnt, s, lm2v, i);
	}

	return lm2v;
}


ul ** v2lmcompute(DVertex * vlist, ul * lmarray, ul vcnt, ul lmcnt, ul ** v2lm){
	ul i = 0;
	ul s = 0;
	for(i=0;i<lmcnt;i++){
		s = lmarray[i];
		v2lmload(vlist, vcnt, s, v2lm, i);
	}
	return v2lm;
}

ul * lmcopy(ul lmcnt, ul * array){
	FILE * fp;
	ul i = 0;

	fp=fopen("lm.txt","r");
	for(i=0;i<lmcnt;i++){
		fscanf(fp,"%ld",&array[i]);
	}

	return array;
}

void dg_statistic(Result * res, ul ** lm2v, ul ** v2lm, ul qcnt, ul lmcnt){
	ul i=0;
	ul j=0;
	ul * hist=NULL;
	ul s;
	ul t;
	FILE * fp;

	hist=(ul*)calloc(lmcnt,sizeof(ul));
	for(i=0;i<qcnt;i++){
		for(j=0;j<lmcnt;j++){
			s=res[i].s;
			t=res[i].t;
			if(res[i].d==v2lm[s][j]+lm2v[t][j] && v2lm[s][j]!= 9999 && lm2v[t][j]!=9999){
				hist[j]++;
				break;
			}

		}
	}

	for(i=lmcnt-1;i>0;i--)
		for(j=0;j<i;j++)
			hist[i]+=hist[j];

	fp=fopen("statistic.txt","w");
	for(i=0;i<lmcnt;i++)
		fprintf(fp,"%ld\n",hist[i]);
	fclose(fp);

	free(hist);
}

void dg_lmtest(DVertex * vlist, ul vcnt) {

	FILE * fp;
	ul qcnt = 10000;
	ul lmcnt = 64;
	ul * query = NULL;
	Result * res;
	Result * reslm_s;
	Result * reslm_t;
	ul ** v2lm = NULL;
	ul ** lm2v = NULL;
	ul i = 0;
	ul j = 0;
	ul * lmarray = NULL;

	lmarray=(ul*)calloc(lmcnt,sizeof(ul));

	lmarray=lmcopy(lmcnt,lmarray);

	v2lm = (ul**)malloc(sizeof(ul*)*vcnt);
	for(i=1;i<vcnt;i++){
		v2lm[i]=(ul*)malloc(sizeof(ul)*lmcnt);
		for(j=0;j<lmcnt;j++)
			v2lm[i][j]=9999;
	}

	lm2v = (ul**)malloc(sizeof(ul*)*vcnt);
	for(i=1;i<vcnt;i++){
		lm2v[i]=(ul*)malloc(sizeof(ul)*lmcnt);
		for(j=0;j<lmcnt;j++)
			lm2v[i][j]=9999;
	}

	v2lm = v2lmcompute(vlist, lmarray, vcnt, lmcnt, v2lm);
	lm2v = lm2vcompute(vlist, lmarray, vcnt, lmcnt, lm2v);

	/*
	 *
	for(i=1;i<vcnt;i++){
		printf("%ld: ",vlist[i].id);
		for(j=0;j<lmcnt;j++)
			printf("%ld ", v2lm[i][j]);
		printf("\n");
	}
	*/



	query = (ul*)calloc(qcnt*2, sizeof(ul));
	res = (Result*)malloc(sizeof(Result) * qcnt);
	reslm_s = (Result*)malloc(sizeof(Result) * qcnt);
	reslm_t = (Result*)malloc(sizeof(Result) * qcnt);


	rinit(res, qcnt);

	fp=fopen("lmtest-query.txt","r");



	for(i = 0; i < qcnt * 2; i++){
		fscanf(fp,"%ld",&query[i]);
	}
	fclose(fp);

	ul s = 0;
	ul t = 0;
	ul lm = 0;

	ul k = 0;

	//direction optimized BFS
	printf("Direction optimized BFS\n");
	for(i = 0; i < qcnt; i++){
		s = query[2*i];
		t = query[2*i+1];
		dg_drtopt(vlist, vcnt, s, t, &(res[i]));


	}

	dg_statistic(res,lm2v,v2lm,qcnt,lmcnt);

}


void ug_ssbfs_lmidx(Vertex * vlist, ul vcnt, ul s, Queue * qs, char * vcheck, ul ** lmidx, ul off){

	ul qsl = 0;
	ul hopcnt = 0;
	ul cur = 0;
	ul i = 0;

	lmidx[s][off] = 0;

	while(qs->length != 0 ){

		// set the range to traverse
		qsl = qs->length;

		// search from s-side
		//printf("qsl = %ld\n", qsl);
		while(qsl != 0){
			s = qpop(qs);
			for(i=0;i<vlist[s].dgr;i++){
				cur = vlist[s].ngb[i];
				if(vcheck[cur]==0){
					vcheck[cur]=1;
					lmidx[cur][off]=hopcnt+1;
					qadd(qs,cur);
				}
			}
			qsl--;
		}
		hopcnt++;
	}
}

void lmidxload(Vertex * vlist, ul vcnt, ul s, ul ** lmidx, ul off){

	Queue * qs;

	qs = (Queue*)malloc(sizeof(Queue));

	qinit(qs);
	qadd(qs, s);

	char * vcheck;

	vcheck=(char*)calloc(vcnt,sizeof(char));
	vcheck[s] = 1;

	ug_ssbfs_lmidx(vlist, vcnt, s, qs, vcheck, lmidx, off);

	qclean(qs);
	free(vcheck);

}

ul ** lmidxcompute(Vertex * vlist, ul * lmarray, ul vcnt, ul lmcnt, ul ** lmidx){
	ul i = 0;
	ul s = 0;
	for(i=0;i<lmcnt;i++){
		s = lmarray[i];
		lmidxload(vlist, vcnt, s, lmidx, i);
	}

	return lmidx;
}

void ug_statistic(Result * res, ul ** lmidx, ul qcnt, ul lmcnt){
	ul i=0;
	ul j=0;
	ul * hist=NULL;
	ul s;
	ul t;
	FILE * fp;

	hist=(ul*)calloc(lmcnt,sizeof(ul));
	for(i=0;i<qcnt;i++){
		for(j=0;j<lmcnt;j++){
			s=res[i].s;
			t=res[i].t;
			if(res[i].d==lmidx[s][j]+lmidx[t][j] && lmidx[s][j]!= 9999 && lmidx[t][j]!=9999){
				hist[j]++;
				break;
			}

		}
	}

	for(i=lmcnt-1;i>0;i--)
		for(j=0;j<i;j++)
			hist[i]+=hist[j];

	fp=fopen("statistic.txt","w");
	for(i=0;i<lmcnt;i++)
		fprintf(fp,"%ld\n",hist[i]);
	fclose(fp);

	free(hist);
}

void ug_lmtest(Vertex * vlist, ul vcnt) {

	FILE * fp;
	ul qcnt = 10000;
	ul lmcnt = 64;
	ul * query = NULL;
	Result * res;
	ul ** lmidx = NULL;
	ul i = 0;
	ul j = 0;
	ul * lmarray = NULL;

	lmarray=(ul*)calloc(lmcnt,sizeof(ul));

	lmarray=lmcopy(lmcnt,lmarray);

	lmidx = (ul**)malloc(sizeof(ul*)*vcnt);
	for(i=1;i<vcnt;i++){
		lmidx[i]=(ul*)malloc(sizeof(ul)*lmcnt);
		for(j=0;j<lmcnt;j++)
			lmidx[i][j]=9999;
	}

	lmidx = lmidxcompute(vlist, lmarray, vcnt, lmcnt, lmidx);

	/*
	 *
	for(i=1;i<vcnt;i++){
		printf("%ld: ",vlist[i].id);
		for(j=0;j<lmcnt;j++)
			printf("%ld ", v2lm[i][j]);
		printf("\n");
	}
	*/



	query = (ul*)calloc(qcnt*2, sizeof(ul));
	res = (Result*)malloc(sizeof(Result) * qcnt);

	rinit(res, qcnt);

	fp=fopen("lmtest-query.txt","r");



	for(i = 0; i < qcnt * 2; i++){
		fscanf(fp,"%ld",&query[i]);
	}
	fclose(fp);

	ul s = 0;
	ul t = 0;
	ul k = 0;

	//direction optimized BFS
	printf("Direction optimized BFS\n");
	for(i = 0; i < qcnt; i++){
		s = query[2*i];
		t = query[2*i+1];
		dg_drtopt(vlist, vcnt, s, t, &(res[i]));


	}

	ug_statistic(res,lmidx, qcnt,lmcnt);

}
//}
