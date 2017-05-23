/*
 * dgbfs.c
 *
 *  Created on: May 19, 2017
 *      Author: will
 */

#include"bfs.h"

void dg_naivebfs(DVertex * vlist, ul vcnt, ul s, ul t, Queue * qs, Queue * qt, char * vcheck, Result * r, Flag *f){

	ul qsl = 0;
	ul qtl = 0;
	ul hopcnt = 0;

	clock_t begin = clock();
	while(qs->length != 0 && qt->length != 0 && (!f->hit && !f->meet)){

		// set the range to traverse
		qsl = qs->length;
		qtl = qt->length;

		// search from s-side
		//printf("qsl = %ld\n", qsl);
		while(!f->hit && !f->meet && qsl != 0){
			s = qpop(qs);
			//printf("%ld-s-%ld:\t",hopcnt+1,s);
			hop(vlist[s].out, vlist[s].outdgr, t, qs, vcheck, r, f, 1);
			//printf("\n");
			if(f->hit || f->meet){
				hopcnt++;
				//printf("s-side step %ld break\n", hopcnt);
				r->d = hopcnt;
				break;
			}
			qsl--;
		}
		if(!f->hit && !f->meet){
			hopcnt++;
			//printf("s-side step %ld finished\n", hopcnt);
		}

		//search from t-side
		//printf("qtl = %ld\n", qtl);
		while(!f->hit && !f->meet && qtl != 0){
			t = qpop(qt);
			//printf("%ld-t-%ld:\t",hopcnt+1, t);
			hop(vlist[t].in, vlist[t].indgr, s, qt, vcheck, r, f, 2);
			//printf("\n");
			if(f->hit || f->meet){
				hopcnt++;
				//printf("t-side step %ld break\n", hopcnt);
				r->d = hopcnt;
				break;
			}
			qtl--;
		}
		if(!f->hit && !f->meet){
			hopcnt++;
			//printf("t-side step %ld finished\n", hopcnt);
		}
	}


		clock_t end = clock();
			float t_total = ((float)(end-begin)/1000000.0F)*1000;

			r->ttotal += t_total;


			if(f->hit || f->meet){
				printf("%ld - %ld dist: %ld v_total: %ld e_total: %ld t_total: %f ms\n", r->s, r->t, r->d, r->vtotal, r->etotal, r->ttotal);
			}
			else{
				printf("%ld - %ld dist: null v_total: %ld e_total: %ld t_total: %f ms\n", r->s, r->t, r->vtotal, r->etotal, r->ttotal);
			}



}


void dg_onebfs(DVertex * vlist, ul vcnt, ul s, ul t, Queue * qs, Queue * qt, char * vcheck, Result * r, Flag *f){

	ul qsl = 0;
	ul qtl = 0;
	ul s_hopcnt = 0;
	ul t_hopcnt = 0;

	//char * hopcheck;
	//hopcheck=(char *)calloc(vcnt,sizeof(char));

	// set the initial range to traverse
	qsl = qs->length;
	qtl = qt->length;


	clock_t begin = clock();
	while(qs->length != 0 && qt->length != 0 && (!f->hit && !f->meet)){

		//search from s-side
		s = qpop(qs);
		//printf("%ld-s-%ld:\n",s_hopcnt,s);

		hop(vlist[s].out, vlist[s].outdgr, t, qs, vcheck, r, f, 1);
		//printf("\n");
		if(f->hit || f->meet){
			if(qsearch(qt, qtl, r->mid))
				r->d = s_hopcnt + t_hopcnt + 1;
			else{
				r->d = s_hopcnt + t_hopcnt + 2;
				//checkshortcut(vlist, qs, qt, qsl, qtl, vcheck, r);
				//frontier(vlist,qs,qt,qsl,qtl,vcheck,r,1);
			}
			//printf("s-side step %ld break\n", s_hopcnt);

			break;
		}
		qsl--;
		if(qsl == 0){
			if(!f->hit && !f->meet){
				//printf("s-side step %ld finished\n", s_hopcnt );
				s_hopcnt++;

			}
			qsl = qs->length;
			//printf("qsl = %ld\n", qsl);
		}

		//search from t-side
		t = qpop(qt);

		//printf("%ld-t-%ld:\n",t_hopcnt, t);
		hop(vlist[t].in, vlist[t].indgr, s, qt, vcheck, r, f, 2);
		//printf("\n");
		if(f->hit || f->meet){
			if(qsearch(qs, qsl, r->mid))
				r->d = s_hopcnt + t_hopcnt + 1;
			else{
				r->d = s_hopcnt + t_hopcnt + 2;
				//checkshortcut(vlist, qt, qs, qtl, qsl, vcheck, r);
				//frontier(vlist,qt,qs,qtl,qsl,vcheck,r,2);
			}
			//printf("t-side step %ld break\n", t_hopcnt);

			break;
		}
		qtl--;
		if(qtl == 0){
			if(!f->hit && !f->meet){
				//printf("t-side step %ld finished\n", t_hopcnt );
				t_hopcnt++;
			}
			qtl = qt->length;
			//printf("qtl = %ld\n", qtl);
		}


	}

	clock_t end = clock();

	float t_total = ((float)(end-begin)/1000000.0F)*1000;

	r->ttotal += t_total;


	if(f->hit || f->meet){
		printf("%ld - %ld dist: %ld v_total: %ld e_total: %ld t_total: %f ms\n", r->s, r->t, r->d, r->vtotal, r->etotal, r->ttotal);
	}
	else{
		printf("%ld - %ld dist: null v_total: %ld e_total: %ld t_total: %f ms\n", r->s, r->t, r->vtotal, r->etotal, r->ttotal);
	}
}


void dg_bfs(DVertex * vlist, ul vcnt, ul s, ul t, Result * r){

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

	dg_naivebfs(vlist, vcnt, s, t, qs, qt, vcheck, r, f);

	//dg_onebfs(vlist, vcnt, s, t, qs, qt, vcheck, r, f);

	qclean(qs);
	qclean(qt);
	free(vcheck);
}


void dg_drtbfshop(DVertex * vlist, ul * arr, ul l, ul t, Queue * q, char * vcheck, Result * r, Flag * f, ul mark, ul * nextfrtsize){


	ul i = 0;
	ul cur = 0;

	for(i = 0; i < l; i++){
		cur = arr[i];
		r->etotal++;
		if(cur == t){
			f->hit = true;

			//printf("%ld(hit)\n",cur);
			break;
		}
		if(vcheck[cur] != 0 && vcheck[cur] != mark){
			f->meet = true;
			r->mid = cur;
			//printf("%ld(meet)\n",cur);
			break;
		}
		if(vcheck[cur] == 0){
			vcheck[cur] = mark;
			r->vtotal++;
			if(mark == 1)
				(*nextfrtsize) += vlist[cur].outdgr;
			if(mark == 2)
				(*nextfrtsize) += vlist[cur].indgr;
			qadd(q,cur);
			//printf("\t%ld(add)\t",cur);
		}

	}
}


void dg_drtbfs(DVertex * vlist, ul vcnt, ul s, ul t, Queue * qs, Queue * qt, char * vcheck, Result * r, Flag *f){

	ul qsl = 0;
	ul qtl = 0;
	ul hopcnt = 0;
	ul sfrtecnt = 1;
	ul tfrtecnt = 1;

	sfrtecnt = vlist[getqhead(qs)].outdgr;
	tfrtecnt = vlist[getqhead(qt)].indgr;

	clock_t begin = clock();
	while(qs->length != 0 && qt->length != 0 && (!f->hit && !f->meet)){

		// set the range to traverse
		qsl = qs->length;
		qtl = qt->length;

		//printf("sfrt = %ld tfrt = %ld\n",sfrtecnt, tfrtecnt);
		if(sfrtecnt <= tfrtecnt){
			sfrtecnt = 0;
		// search from s-side
		//printf("qsl = %ld\n", qsl);
		while(!f->hit && !f->meet && qsl != 0){
			s = qpop(qs);

			//printf("%ld-s-%ld:\t",hopcnt+1,s);
			dg_drtbfshop(vlist, vlist[s].out, vlist[s].outdgr, t, qs, vcheck, r, f, 1, &sfrtecnt);
			//printf("\n");
			if(f->hit || f->meet){
				hopcnt++;
				//printf("s-side step %ld break\n", hopcnt);
				r->d = hopcnt;
				break;
			}
			qsl--;
		}
		if(!f->hit && !f->meet){
			hopcnt++;
			//printf("s-side step %ld finished\n", hopcnt);
		}

		}else{
			tfrtecnt = 0;
		//search from t-side
		//printf("qtl = %ld\n", qtl);
		while(!f->hit && !f->meet && qtl != 0){
			t = qpop(qt);

			//printf("%ld-t-%ld:\t",hopcnt+1, t);
			dg_drtbfshop(vlist, vlist[t].in, vlist[t].indgr, s, qt, vcheck, r, f, 2, &tfrtecnt);
			//printf("\n");
			if(f->hit || f->meet){
				hopcnt++;
				//printf("t-side step %ld break\n", hopcnt);
				r->d = hopcnt;
				break;
			}
			qtl--;
		}
		if(!f->hit && !f->meet){
			hopcnt++;
			//printf("t-side step %ld finished\n", hopcnt);
		}

		}
	}


		clock_t end = clock();
			float t_total = ((float)(end-begin)/1000000.0F)*1000;

			r->ttotal += t_total;


			if(f->hit || f->meet){
				printf("%ld - %ld dist: %ld v_total: %ld e_total: %ld t_total: %f ms\n", r->s, r->t, r->d, r->vtotal, r->etotal, r->ttotal);
			}
			else{
				printf("%ld - %ld dist: null v_total: %ld e_total: %ld t_total: %f ms\n", r->s, r->t, r->vtotal, r->etotal, r->ttotal);
			}



}


void dg_drtopt(DVertex * vlist, ul vcnt, ul s, ul t, Result * r){

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

		dg_drtbfs(vlist, vcnt, s, t, qs, qt, vcheck, r, f);

		qclean(qs);
		qclean(qt);
		free(vcheck);
}


void dg_vvbfs(DVertex * vlist, ul vcnt, ul s, ul t, Result * r){

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

	//naivebfs(vlist, vcnt, s, t, qs, qt, vcheck, r, f);

	dg_onebfs(vlist, vcnt, s, t, qs, qt, vcheck, r, f);

	qclean(qs);
	qclean(qt);
	free(vcheck);
}


void dg_klimitbfs(DVertex * vlist, ul vcnt, ul s, ul t, Queue * qs, Queue * qt, char * vcheck, Result * r, Flag *f, ul k){

	ul qsl = 0;
	ul qtl = 0;
	ul hopcnt = 0;

	clock_t begin = clock();
	while(qs->length != 0 && qt->length != 0 && (!f->hit && !f->meet)){

		// set the range to traverse
		qsl = qs->length;
		qtl = qt->length;

		// search from s-side
		//printf("qsl = %ld\n", qsl);
		while(!f->hit && !f->meet && qsl != 0){
			s = qpop(qs);
			//printf("%ld-s-%ld:\t",hopcnt+1,s);
			if(vlist[s].outdgr < k)
				hop(vlist[s].out, vlist[s].outdgr, t, qs, vcheck, r, f, 1);
			else
				hop(vlist[s].out, k, t, qs, vcheck, r, f, 1);
			//printf("\n");
			if(f->hit || f->meet){
				hopcnt++;
				//printf("s-side step %ld break\n", hopcnt);
				r->d = hopcnt;
				break;
			}
			qsl--;
		}
		if(!f->hit && !f->meet){
			hopcnt++;
			//printf("s-side step %ld finished\n", hopcnt);
		}

		//search from t-side
		//printf("qtl = %ld\n", qtl);
		while(!f->hit && !f->meet && qtl != 0){
			t = qpop(qt);
			//printf("%ld-t-%ld:\t",hopcnt+1, t);
			if(vlist[t].indgr < k)
				hop(vlist[t].in, vlist[t].indgr, s, qt, vcheck, r, f, 2);
			else
				hop(vlist[t].in, k, s, qt, vcheck, r, f, 2);
			//printf("\n");
			if(f->hit || f->meet){
				hopcnt++;
				//printf("t-side step %ld break\n", hopcnt);
				r->d = hopcnt;
				break;
			}
			qtl--;
		}
		if(!f->hit && !f->meet){
			hopcnt++;
			//printf("t-side step %ld finished\n", hopcnt);
		}

		if(hopcnt == 10){
			break;
		}
	}

	clock_t end = clock();

	if(hopcnt < 10){
		float t_total = ((float)(end-begin)/1000000.0F)*1000;

		r->ttotal += t_total;


		if(f->hit || f->meet){
			printf("%ld - %ld dist: %ld v_total: %ld e_total: %ld t_total: %f ms\n", r->s, r->t, r->d, r->vtotal, r->etotal, r->ttotal);
		}
		else{
			r->d = 0;
			printf("%ld - %ld dist: null v_total: %ld e_total: %ld t_total: %f ms\n", r->s, r->t, r->vtotal, r->etotal, r->ttotal);
		}
	}
	else{
		printf("fall back to naive bfs\n");
		dg_bfs(vlist, vcnt, r->s, r->t, r);
	}

}


void dg_klimit(DVertex * vlist, ul vcnt, ul s, ul t, ul k, Result * r){
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


		dg_klimitbfs(vlist, vcnt, s, t, qs, qt, vcheck, r, f, k);

		//onebfs(vlist, vcnt, s, t, qs, qt, vcheck, r, f);

		qclean(qs);
		qclean(qt);
		free(vcheck);

}




void dg_kunvistbfs(DVertex * vlist, ul vcnt, ul s, ul t, Queue * qs, Queue * qt, char * vcheck, Result * r, Flag *f, ul k){
	ul qsl = 0;
	ul qtl = 0;
	ul hopcnt = 0;

	clock_t begin = clock();
	while(qs->length != 0 && qt->length != 0 && (!f->hit && !f->meet)){

		// set the range to traverse
		qsl = qs->length;
		qtl = qt->length;

		// search from s-side
		//printf("qsl = %ld\n", qsl);
		while(!f->hit && !f->meet && qsl != 0){
			s = qpop(qs);
			//printf("%ld-s-%ld:\t",hopcnt+1,s);

			kunvisithop(vlist[s].out, vlist[s].outdgr, k, t, qs, vcheck, r, f, 1);

			//printf("\n");
			if(f->hit || f->meet){
				hopcnt++;
				//printf("s-side step %ld break\n", hopcnt);
				r->d = hopcnt;
				break;
			}
			qsl--;
		}
		if(!f->hit && !f->meet){
			hopcnt++;
			//printf("s-side step %ld finished\n", hopcnt);
		}

		//search from t-side
		//printf("qtl = %ld\n", qtl);
		while(!f->hit && !f->meet && qtl != 0){
			t = qpop(qt);
			//printf("%ld-t-%ld:\t",hopcnt+1, t);

			kunvisithop(vlist[t].in, vlist[t].indgr, k, s, qt, vcheck, r, f, 2);

			//printf("\n");
			if(f->hit || f->meet){
				hopcnt++;
				//printf("t-side step %ld break\n", hopcnt);
				r->d = hopcnt;
				break;
			}
			qtl--;
		}

		if(!f->hit && !f->meet){
			hopcnt++;
			//printf("t-side step %ld finished\n", hopcnt);
		}

		if(hopcnt == 10){
			break;
		}
	}


	clock_t end = clock();

	if(hopcnt < 10){
		float t_total = ((float)(end-begin)/1000000.0F)*1000;

		r->ttotal += t_total;


		if(f->hit || f->meet){
			printf("%ld - %ld dist: %ld v_total: %ld e_total: %ld t_total: %f ms\n", r->s, r->t, r->d, r->vtotal, r->etotal, r->ttotal);
		}
		else{
			r->d = 0;
			printf("%ld - %ld dist: null v_total: %ld e_total: %ld t_total: %f ms\n", r->s, r->t, r->vtotal, r->etotal, r->ttotal);
		}
	}
	else{
		printf("fall back to naive bfs\n");
		dg_bfs(vlist, vcnt, r->s, r->t, r);
	}

}


void dg_kunvisit(DVertex * vlist, ul vcnt, ul s, ul t, ul k, Result * r){
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


	dg_kunvistbfs(vlist, vcnt, s, t, qs, qt, vcheck, r, f, k);

	qclean(qs);
	qclean(qt);
	free(vcheck);


}


