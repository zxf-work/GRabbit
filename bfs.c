/*
 * bfs.c
 *
 *  Created on: May 8, 2017
 *      Author: will
 */

#include"bfs.h"


void hop(ul * arr, ul l, ul t, Queue * q, char * vcheck, Result * r, Flag * f){

	ul i = 0;
	ul cur = 0;

	for(i = 0; i < l; i++){
		cur = arr[i];
		r->etotal++;
		if(cur == t){
			f->hit = true;
			break;
		}
		if(vcheck[cur] != 0){
			f->meet = true;
			break;
		}
		if(vcheck[cur] == 0){
			vcheck[cur] = 1;
			r->vtotal++;
			qadd(q,cur);
		}

	}
}

void bfs(Vertex * vlist, ul vcnt, ul s, ul t, Result * r){

	Queue * qs;
	Queue * qt;
	Flag * f;

	qs = (Queue*)malloc(sizeof(Queue));
	qt = (Queue*)malloc(sizeof(Queue));
	f = (Flag *)malloc(sizeof(Flag));

	f->hit = false;
	f->meet = false;

	qinit(qs);
	qinit(qt);

	qadd(qs, s);
	qadd(qt, t);

	ul qsl = 0;
	ul qtl = 0;
	ul hopcnt = 0;
	char * vcheck;

	vcheck=(char*)calloc(vcnt,sizeof(char));
	vcheck[s] = 1;
	vcheck[t] = 1;

	clock_t begin = clock();
	while(qs->length != 0 && qt->length != 0){

		// set the range to traverse
		qsl = qs->length;
		qtl = qt->length;

		// search from s-side
		if((!f->hit && !f->meet) && qsl != 0){
			while(qsl != 0){
			s = qpop(qs);
			hop(vlist[s].ngb, vlist[s].dgr, t, qs, vcheck, r, f);
			qsl--;
			}
			hopcnt++;
		}

		if(f->hit || f->meet){
			r->d = hopcnt;
			break;
		}


		//search from t-side
		if((!f->hit && !f->meet) && qtl != 0){
			while(qtl != 0){
				t = qpop(qt);
				hop(vlist[t].ngb, vlist[t].dgr, s, qt, vcheck, r, f);
				qtl--;
			}
			hopcnt++;
		}

		if(f->hit || f->meet){
			r->d = hopcnt;
			break;
		}
	}

	clock_t end = clock();
	float t_total = ((float)(end-begin)/1000000.0F)/1000;

	r->ttotal += t_total;
	r->s = s;
	r->t = t;

	if(f->hit || f->meet){
		printf("%ld - %ld dist: %ld v_total: %ld e_total: %ld t_total: %f ms\n", r->s, r->t, r->d, r->vtotal, r->etotal, r->ttotal);
	}
	else{
		printf("%ld - %ld dist: null v_total: %ld e_total: %ld t_total: %f ms\n", r->s, r->t, r->vtotal, r->etotal, r->ttotal);
	}

	qclean(qs);
	qclean(qt);
	free(vcheck);
}

void klimit(Vertex * vlist, ul vcnt, ul s, ul t, ul k){

}

void kunvisit(Vertex * vlist, ul vcnt, ul s, ul t, ul k){

}

void kreduce(Vertex * vlist, ul vcnt, ul s, ul t, ul k){



}
