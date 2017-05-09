/*
 * bfs.c
 *
 *  Created on: May 8, 2017
 *      Author: will
 */

#include"bfs.h"


void hop(ul * arr, ul l, ul t, Queue * q, char * vcheck, Result * r, Flag * f, ul mark){

	ul i = 0;
	ul cur = 0;

	for(i = 0; i < l; i++){
		cur = arr[i];
		//if(vcheck[cur] != mark)
			r->etotal++;
		if(cur == t){
			f->hit = true;
			//printf("%ld(hit)\n",cur);
			break;
		}
		if(vcheck[cur] != 0 && vcheck[cur] != mark){
			f->meet = true;
			printf("%ld(meet)\n",cur);
			break;
		}
		if(vcheck[cur] == 0){
			vcheck[cur] = mark;
			r->vtotal++;
			qadd(q,cur);
			//printf("%ld(add)\t",cur);
		}

	}
}

void naivebfs(Vertex * vlist, ul s, ul t, Queue * qs, Queue * qt, char * vcheck, Result * r, Flag *f){

	ul qsl = 0;
	ul qtl = 0;
	ul hopcnt = 0;

	clock_t begin = clock();
	while(qs->length != 0 && qt->length != 0 && (!f->hit && !f->meet)){

		// set the range to traverse
		qsl = qs->length;
		qtl = qt->length;

		// search from s-side
		printf("qsl = %ld\n", qsl);
		while(!f->hit && !f->meet && qsl != 0){
			s = qpop(qs);
			//printf("%ld-s-%ld:\t",hopcnt+1,s);
			hop(vlist[s].ngb, vlist[s].dgr, t, qs, vcheck, r, f, 1);
			//printf("\n");
			if(f->hit || f->meet){
				hopcnt++;
				printf("s-side step %ld break\n", hopcnt);
				r->d = hopcnt;
				break;
			}
			qsl--;
		}
		if(!f->hit && !f->meet){
			hopcnt++;
			printf("s-side step %ld finished\n", hopcnt);
		}

		//search from t-side
		printf("qtl = %ld\n", qtl);
		while(!f->hit && !f->meet && qtl != 0){
			t = qpop(qt);
			//printf("%ld-t-%ld:\t",hopcnt+1, t);
			hop(vlist[t].ngb, vlist[t].dgr, s, qt, vcheck, r, f, 2);
			//printf("\n");
			if(f->hit || f->meet){
				hopcnt++;
				printf("t-side step %ld break\n", hopcnt);
				r->d = hopcnt;
				break;
			}
			qtl--;
		}
		if(!f->hit && !f->meet){
			hopcnt++;
			printf("t-side step %ld finished\n", hopcnt);
		}
	}

	clock_t end = clock();

	float t_total = ((float)(end-begin)/1000000.0F)/1000;

	r->ttotal += t_total;


	if(f->hit || f->meet){
		printf("%ld - %ld dist: %ld v_total: %ld e_total: %ld t_total: %f ms\n", r->s, r->t, r->d, r->vtotal, r->etotal, r->ttotal);
	}
	else{
		printf("%ld - %ld dist: null v_total: %ld e_total: %ld t_total: %f ms\n", r->s, r->t, r->vtotal, r->etotal, r->ttotal);
	}
}

void onebfs(Vertex * vlist, ul s, ul t, Queue * qs, Queue * qt, char * vcheck, Result * r, Flag *f){

	ul qsl = 0;
	ul qtl = 0;
	ul hopcnt = 0;

	clock_t begin = clock();
	while(qs->length != 0 && qt->length != 0 && (!f->hit && !f->meet)){

		// set the range to traverse
		qsl = qs->length;
		qtl = qt->length;


		//search from s-side
		s = qpop(qs);

		//printf("%ld-s-%ld:\t",hopcnt+1,s);
		hop(vlist[s].ngb, vlist[s].dgr, t, qs, vcheck, r, f, 1);
		//printf("\n");
		if(f->hit || f->meet){
			//if(qsl != 0 && qtl != 0)
				hopcnt = hopcnt + 3;
			printf("s-side step %ld break\n", hopcnt);
			r->d = hopcnt;
			break;
		}
		qsl--;
		if(qsl == 0){
			if(!f->hit && !f->meet){
				hopcnt++;
				printf("s-side step %ld finished\n", hopcnt);
			}
			qsl = qs->length;
			printf("qsl = %ld\n", qsl);
		}

		//search from t-side
		t = qpop(qt);

		//printf("%ld-t-%ld:\t",hopcnt+1, t);
		hop(vlist[t].ngb, vlist[t].dgr, s, qt, vcheck, r, f, 2);
		//printf("\n");
		if(f->hit || f->meet){
			//if(qsl != 0 && qtl != 0)
				hopcnt = hopcnt + 3;
			printf("t-side step %ld break\n", hopcnt);
			r->d = hopcnt;
			break;
		}
		qtl--;
		if(qtl == 0){
			if(!f->hit && !f->meet){
				hopcnt++;
				printf("t-side step %ld finished\n", hopcnt);
			}
			qtl = qt->length;
			printf("qtl = %ld\n", qtl);
		}


	}

	clock_t end = clock();

	float t_total = ((float)(end-begin)/1000000.0F)/1000;

	r->ttotal += t_total;


	if(f->hit || f->meet){
		printf("%ld - %ld dist: %ld v_total: %ld e_total: %ld t_total: %f ms\n", r->s, r->t, r->d, r->vtotal, r->etotal, r->ttotal);
	}
	else{
		printf("%ld - %ld dist: null v_total: %ld e_total: %ld t_total: %f ms\n", r->s, r->t, r->vtotal, r->etotal, r->ttotal);
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

	char * vcheck;

	vcheck=(char*)calloc(vcnt,sizeof(char));
	vcheck[s] = 1;
	vcheck[t] = 2;

	r->s = s;
	r->t = t;
	r->vtotal = 2;

	naivebfs(vlist, s, t, qs, qt, vcheck, r, f);

	//onebfs(vlist, s, t, qs, qt, vcheck, r, f);

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
