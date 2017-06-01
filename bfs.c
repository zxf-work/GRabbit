/*
 * bfs.c
 *
 *  Created on: May 8, 2017
 *      Author: will
 */

#include"bfs.h"

/** (need to fix) checking if there's shortcuts between unfinished frontiers  **/
void frontier(Vertex * vlist, Queue * qs, Queue * qt, ul qsl, ul qtl, char * vcheck, Result * r, ul mark){
	ul i = 0;
	ul j = 0;
	ul s = 0;
	ul t = 0;
	bool shortcut = false;

	for(i = 0; i < qsl; i++){
		s = qpop(qs);
		r->vtotal ++;
		for(j = 0; j < vlist[s].dgr; j++){
			t = vlist[s].ngb[j];
			r->etotal ++;
			if(vcheck[t] != 0 && vcheck[t] != mark){
				if(qsearch(qt, qtl, t)){
					r->d = r->d - 1;
					shortcut = true;
					break;
				}
			}
		}
		if(shortcut)
			break;
	}
}

void checkshortcut(Vertex * vlist, Queue * qs, Queue * qt, ul qsl, ul qtl, char * vcheck, Result * r){

	ul se = 0;
	ul te = 0;


	se = ecntq(vlist, qs, qsl);
	te = ecntq(vlist, qt, qtl);

	if(se <= te){
		frontier(vlist, qs, qt, qsl, qtl, vcheck, r, 1);
	}else{
		frontier(vlist, qt, qt, qtl, qsl, vcheck, r, 2);
	}


	//frontier(vlist,qs,qt,qsl,qtl,vcheck,r,mark);
}


bool existshortcut(Vertex *vlist, Queue * q, ul l, char * vcheck, ul mark){
	ul i = 0;
	ul j = 0;
	ul s;
	ul cur;

	for(i = 0; i < l-1; i++){
		s = qpop(q);
		for(j = 0; j < vlist[s].dgr; j++){
			cur = vlist[s].ngb[j];
			if(vcheck[cur] != 0 && vcheck[cur] != mark)
				return true;
		}
	}

	return false;
}

void hop(ul * arr, ul l, ul t, Queue * q, char * vcheck, Result * r, Flag * f, ul mark){


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
			qadd(q,cur);
			//printf("\t%ld(add)\t",cur);
		}

	}
}

void getedge(Vertex * vlist, ul * arr, ul off, Queue * q, char * vcheck, Result * r, Flag * f, ul mark){

	ul cur = 0;
	cur = arr[off];
	r->etotal++;
	if((cur == r->t ) || (cur == r->s )){
		f->hit = true;

	}
	if(vcheck[cur] != 0 && vcheck[cur] != mark){
		f->meet = true;
		r->mid = cur;
		//printf("%ld(meet)\n",cur);

	}
	if(vcheck[cur] == 0){
		vcheck[cur] = mark;
		r->vtotal++;
		qadd(q,cur);

	}

}


void hop_frtcnt(Vertex * vlist, ul * arr, ul l, ul t, Queue * q, char * vcheck, Result * r, Flag * f, ul mark, ul * nextfrtsize){

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
				(*nextfrtsize) += vlist[cur].dgr;
				qadd(q,cur);
				//printf("\t%ld(add)\t",cur);
			}

		}
}



void kunvisithop(ul * arr, ul l, ul k, ul t, Queue * q, char * vcheck, Result * r, Flag * f, ul mark){


	ul i = 0;
	ul cur = 0;
	ul j = 0;

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
			qadd(q,cur);
			//printf("\t%ld(add)\t",cur);
			j++;
			if(j == k){
				break;
			}
		}

	}
}

void drtbfshop(Vertex * vlist, ul * arr, ul l, ul t, Queue * q, char * vcheck, Result * r, Flag * f, ul mark, ul * nextfrtsize){


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
			(*nextfrtsize) += vlist[cur].dgr;
			qadd(q,cur);
			//printf("\t%ld(add)\t",cur);
		}

	}
}

/*naive bfs is the classic BFS, every step searches the entire front*/
void naivebfs(Vertex * vlist, ul vcnt, ul s, ul t, Queue * qs, Queue * qt, char * vcheck, Result * r, Flag *f){

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
			hop(vlist[s].ngb, vlist[s].dgr, t, qs, vcheck, r, f, 1);
			//printf("\n");
			if(f->hit || f->meet){
				hopcnt++;
				//printf("s-side step %ld break\n", hopcnt);
				r->d = hopcnt;
				//printf("\t meeting at exploring %ld[%ld] to %ld[%ld]\n",s,vlist[s].dgr, r->mid, vlist[r->mid].dgr);
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
			hop(vlist[t].ngb, vlist[t].dgr, s, qt, vcheck, r, f, 2);
			//printf("\n");
			if(f->hit || f->meet){
				hopcnt++;
				//printf("t-side step %ld break\n", hopcnt);
				r->d = hopcnt;
				//printf("\t meeting at exploring %ld[%ld] to %ld[%ld]\n",t,vlist[t].dgr, r->mid, vlist[r->mid].dgr);
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
				printf("%ld[%ld] - %ld[%ld] dist: %ld v_total: %ld e_total: %ld t_total: %f ms\n", r->s, vlist[r->s].dgr, r->t, vlist[r->t].dgr, r->d, r->vtotal, r->etotal, r->ttotal);
			}
			else{
				printf("%ld[%ld] - %ld[%ld] dist: null v_total: %ld e_total: %ld t_total: %f ms\n", r->s, vlist[r->s].dgr, r->t, vlist[r->t].dgr, r->vtotal, r->etotal, r->ttotal);
			}



}

void klimitbfs(Vertex * vlist, ul vcnt, ul s, ul t, Queue * qs, Queue * qt, char * vcheck, Result * r, Flag *f, ul k){

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
			if(vlist[s].dgr < k)
				hop(vlist[s].ngb, vlist[s].dgr, t, qs, vcheck, r, f, 1);
			else
				hop(vlist[s].ngb, k, t, qs, vcheck, r, f, 1);
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
			if(vlist[t].dgr < k)
				hop(vlist[t].ngb, vlist[t].dgr, s, qt, vcheck, r, f, 2);
			else
				hop(vlist[t].ngb, k, s, qt, vcheck, r, f, 2);
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
		bfs(vlist, vcnt, r->s, r->t, r);
	}

}

void kunvistbfs(Vertex * vlist, ul vcnt, ul s, ul t, Queue * qs, Queue * qt, char * vcheck, Result * r, Flag *f, ul k){
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

			kunvisithop(vlist[s].ngb, vlist[s].dgr, k, t, qs, vcheck, r, f, 1);

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

			kunvisithop(vlist[t].ngb, vlist[t].dgr, k, s, qt, vcheck, r, f, 2);

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
		bfs(vlist, vcnt, r->s, r->t, r);
	}

}

void kreducebfs(Vertex * vlist, Vertex * vlistmaster, ul vcnt, ul s, ul t, Queue * qs, Queue * qt, char * vcheck, Result * r, Flag *f){
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

			hop(vlist[s].ngb, vlist[s].dgr, t, qs, vcheck, r, f, 1);

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

			hop(vlist[t].ngb, vlist[t].dgr, s, qt, vcheck, r, f, 2);

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
		bfs(vlistmaster, vcnt, r->s, r->t, r);
	}

}

void drtbfs(Vertex * vlist, ul vcnt, ul s, ul t, Queue * qs, Queue * qt, char * vcheck, Result * r, Flag *f){

	ul qsl = 0;
	ul qtl = 0;
	ul hopcnt = 0;
	ul sfrtecnt = 1;
	ul tfrtecnt = 1;

	sfrtecnt = vlist[getqhead(qs)].dgr;
	tfrtecnt = vlist[getqhead(qt)].dgr;

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
			drtbfshop(vlist, vlist[s].ngb, vlist[s].dgr, t, qs, vcheck, r, f, 1, &sfrtecnt);
			//printf("\n");
			if(f->hit || f->meet){
				hopcnt++;
				//printf("s-side step %ld break\n", hopcnt);
				r->d = hopcnt;
				//printf("\t meeting at exploring %ld[%ld] to %ld[%ld]\n",s,vlist[s].dgr, r->mid, vlist[r->mid].dgr);
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
			drtbfshop(vlist, vlist[t].ngb, vlist[t].dgr, s, qt, vcheck, r, f, 2, &tfrtecnt);
			//printf("\n");
			if(f->hit || f->meet){
				hopcnt++;
				//printf("t-side step %ld break\n", hopcnt);
				r->d = hopcnt;
				//printf("\t meeting at exploring %ld[%ld] to %ld[%ld]\n",t,vlist[t].dgr, r->mid, vlist[r->mid].dgr);
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

void tmpdvbfs(Vertex * vlist, ul vcnt, ul s, ul t, Queue * qs, Queue * qt, char * vcheck, Result * r, Flag *f){

	ul qsl = 0;
	ul qtl = 0;
	ul hopcnt = 0;
	ul sfrtecnt = 1;
	ul tfrtecnt = 1;

	sfrtecnt = vlist[getqhead(qs)].dgr;
	tfrtecnt = vlist[getqhead(qt)].dgr;

	clock_t begin = clock();
	while(qs->length != 0 && qt->length != 0 && (!f->hit && !f->meet)){

		// set the range to traverse
		qsl = qs->length;
		qtl = qt->length;

		printf("sfrt = %ld tfrt = %ld\n",sfrtecnt, tfrtecnt);
		if(sfrtecnt <= tfrtecnt){
			sfrtecnt = 0;
		// search from s-side
		//printf("qsl = %ld\n", qsl);
		while(!f->hit && !f->meet && qsl != 0){
			s = qpop(qs);

			//printf("%ld-s-%ld:\t",hopcnt+1,s);
			drtbfshop(vlist, vlist[s].ngb, vlist[s].dgr, t, qs, vcheck, r, f, 1, &sfrtecnt);
			//printf("\n");
			if(f->hit || f->meet){
				hopcnt++;
				//printf("s-side step %ld break\n", hopcnt);
				r->d = hopcnt;
				//printf("\t meeting at exploring %ld[%ld] to %ld[%ld]\n",s,vlist[s].dgr, r->mid, vlist[r->mid].dgr);
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
			drtbfshop(vlist, vlist[t].ngb, vlist[t].dgr, s, qt, vcheck, r, f, 2, &tfrtecnt);
			//printf("\n");
			if(f->hit || f->meet){
				hopcnt++;
				//printf("t-side step %ld break\n", hopcnt);
				r->d = hopcnt;
				//printf("\t meeting at exploring %ld[%ld] to %ld[%ld]\n",t,vlist[t].dgr, r->mid, vlist[r->mid].dgr);
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

}

void dvbfs(Vertex * vlist, ul vcnt, ul s, ul t, Queue * qs, Queue * qt, char * vcheck, Result * r, Flag *f){

	ul qsl = 0;
	ul qtl = 0;
	ul s_hopcnt = 0;
	ul t_hopcnt = 0;
	ul sfrtecnt = 1;
	ul tfrtecnt = 1;
	ul snextfrt = 0;
	ul tnextfrt = 0;

	sfrtecnt = vlist[getqhead(qs)].dgr;
	tfrtecnt = vlist[getqhead(qt)].dgr;


	qsl = qs->length;
	qtl = qt->length;


	clock_t begin = clock();
	while(qs->length != 0 && qt->length != 0 && (!f->hit && !f->meet)){

		if(vlist[getqhead(qs)].dgr>tfrtecnt){
		// if a single vertex's degree is greater than the size of the other frontier, first explore the frontier
			while(!f->hit && !f->meet && qtl != 0){
				t = qpop(qt);
				drtbfshop(vlist, vlist[t].ngb, vlist[t].dgr, s, qt, vcheck, r, f, 2, &tnextfrt);

				if(f->hit || f->meet){
					//t_hopcnt++;

					if(qsearch(qs, qsl, r->mid))
						r->d = s_hopcnt + t_hopcnt + 1;
					else{
						r->d = s_hopcnt + t_hopcnt + 2;
					}
					//printf("\t meeting at exploring %ld[%ld] to %ld[%ld]\n",t,vlist[t].dgr, r->mid, vlist[r->mid].dgr);
					break;
				}
				qtl--;
			}

			if(!f->hit && !f->meet){
				t_hopcnt++;
				tfrtecnt = tnextfrt;
				tnextfrt = 0;
			}
			qtl = qt->length;

		}
		else{

			s = qpop(qs);
			sfrtecnt = sfrtecnt - vlist[s].dgr;

			hop_frtcnt(vlist, vlist[s].ngb, vlist[s].dgr, t, qs, vcheck, r, f, 1, &snextfrt);
			if(f->hit || f->meet){
				if(qsearch(qt, qtl, r->mid))
					r->d = s_hopcnt + t_hopcnt + 1;
				else{
					r->d = s_hopcnt + t_hopcnt + 2;
				}
				//printf("\t meeting at exploring %ld[%ld] to %ld[%ld]\n",s,vlist[s].dgr, r->mid, vlist[r->mid].dgr);
				break;
			}
			qsl--;
			if(qsl == 0){
				if(!f->hit && !f->meet){
					s_hopcnt++;
					sfrtecnt = snextfrt;
					snextfrt = 0;
				}
				qsl = qs->length;
			}
		}

		if(f->hit || f->meet){
			break;
		}
		if(vlist[getqhead(qt)].dgr>sfrtecnt){
			while(!f->hit && !f->meet && qsl != 0){
				s = qpop(qs);
				drtbfshop(vlist, vlist[s].ngb, vlist[s].dgr, t, qs, vcheck, r, f, 1, &snextfrt);

				if(f->hit || f->meet){
					//s_hopcnt++;

					if(qsearch(qt, qtl, r->mid))
						r->d = s_hopcnt + t_hopcnt + 1;
					else{
						r->d = s_hopcnt + t_hopcnt + 2;

					}
					//printf("\t meeting at exploring %ld[%ld] to %ld[%ld]\n",s,vlist[s].dgr, r->mid, vlist[r->mid].dgr);
					break;
				}
				qsl--;
			}
			if(!f->hit && !f->meet){
				s_hopcnt++;
				sfrtecnt = snextfrt;
				snextfrt = 0;

			}
			qsl = qs->length;
		}
		else{

			t = qpop(qt);
			tfrtecnt = tfrtecnt - vlist[t].dgr;

			hop_frtcnt(vlist, vlist[t].ngb, vlist[t].dgr, s, qt, vcheck, r, f, 2, &tnextfrt);

			if(f->hit || f->meet){
				if(qsearch(qs, qsl, r->mid))
					r->d = s_hopcnt + t_hopcnt + 1;
				else{
					r->d = s_hopcnt + t_hopcnt + 2;
				}

				//printf("\t meeting at exploring %ld[%ld] to %ld[%ld]\n",t,vlist[t].dgr, r->mid, vlist[r->mid].dgr);
				break;
			}
			qtl--;
			if(qtl == 0){
				if(!f->hit && !f->meet){

					t_hopcnt++;
					tfrtecnt = tnextfrt;
					tnextfrt = 0;
				}
				qtl = qt->length;

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

/** (need to fix) one-bfs: interleavingly explore one vertex from each side **/
void onebfs(Vertex * vlist, ul vcnt, ul s, ul t, Queue * qs, Queue * qt, char * vcheck, Result * r, Flag *f){

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

		hop(vlist[s].ngb, vlist[s].dgr, t, qs, vcheck, r, f, 1);
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
			//printf("\t meeting at exploring %ld[%ld] to %ld[%ld]\n",s,vlist[s].dgr, r->mid, vlist[r->mid].dgr);
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
		hop(vlist[t].ngb, vlist[t].dgr, s, qt, vcheck, r, f, 2);
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
			//printf("\t meeting at exploring %ld[%ld] to %ld[%ld]\n",t,vlist[t].dgr, r->mid, vlist[r->mid].dgr);
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

void eebfs(Vertex * vlist, ul vcnt, ul s, ul t, Queue * qs, Queue * qt, char * vcheck, Result * r, Flag *f){

	ul qsl = 0;
	ul qtl = 0;
	ul s_hopcnt = 0;
	ul t_hopcnt = 0;
	ul s_off = 0;
	ul t_off = 0;

	//char * hopcheck;
	//hopcheck=(char *)calloc(vcnt,sizeof(char));

	// set the initial range to traverse
	qsl = qs->length;
	qtl = qt->length;


	clock_t begin = clock();
	while(qs->length != 0 && qt->length != 0 && (!f->hit && !f->meet)){

		//search from s-side
		if(s_off == 0){
			s = qpop(qs);
			qsl--;
		}
		if(s_off<vlist[s].dgr){
			getedge(vlist,vlist[s].ngb,s_off,qs,vcheck,r,f,1);
			s_off++;
			if(f->hit || f->meet){
				if(qsearch(qs, qsl, r->mid))
					r->d = s_hopcnt + t_hopcnt + 1;
				else
					r->d = s_hopcnt + t_hopcnt + 2;
				break;
			}
		}
		if(s_off == vlist[s].dgr)
			s_off = 0;
		if(qsl == 0){
			if(!f->hit && !f->meet){
				s_hopcnt++;
			}
			qsl = qs->length;
			//printf("qsl = %ld\n", qsl);
		}

		if(t_off==0 && qt->length!=0){
			t = qpop(qt);
			qtl--;
		}
		if(t_off<vlist[t].dgr){
			getedge(vlist,vlist[t].ngb,t_off,qt,vcheck,r,f,2);
			t_off++;
			if(f->hit || f->meet){
				if(qsearch(qs, qsl, r->mid))
					r->d = s_hopcnt + t_hopcnt + 1;
				else
					r->d = s_hopcnt + t_hopcnt + 2;
				break;
			}
		}
		if(t_off == vlist[t].dgr)
			t_off = 0;
		if(qtl == 0){
			if(!f->hit && !f->meet){
				t_hopcnt++;
			}
			qtl = qt->length;
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

	naivebfs(vlist, vcnt, s, t, qs, qt, vcheck, r, f);

	//onebfs(vlist, vcnt, s, t, qs, qt, vcheck, r, f);

	qclean(qs);
	qclean(qt);
	free(vcheck);
}


void vvbfs(Vertex * vlist, ul vcnt, ul s, ul t, Result * r){

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

	onebfs(vlist, vcnt, s, t, qs, qt, vcheck, r, f);

	qclean(qs);
	qclean(qt);
	free(vcheck);
}

void klimit(Vertex * vlist, ul vcnt, ul s, ul t, ul k, Result * r){
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


		klimitbfs(vlist, vcnt, s, t, qs, qt, vcheck, r, f, k);

		//onebfs(vlist, vcnt, s, t, qs, qt, vcheck, r, f);

		qclean(qs);
		qclean(qt);
		free(vcheck);

}

void kunvisit(Vertex * vlist, ul vcnt, ul s, ul t, ul k, Result * r){
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


	kunvistbfs(vlist, vcnt, s, t, qs, qt, vcheck, r, f, k);

	qclean(qs);
	qclean(qt);
	free(vcheck);


}


void kreduce(Vertex * vlistreduce, Vertex * vlist, ul vcnt, ul s, ul t, Result * r){

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

	kreducebfs(vlistreduce, vlist, vcnt, s, t, qs, qt, vcheck, r, f);

	//onebfs(vlist, vcnt, s, t, qs, qt, vcheck, r, f);

	qclean(qs);
	qclean(qt);
	free(vcheck);


}

void drtopt(Vertex * vlist, ul vcnt, ul s, ul t, Result * r){

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

		drtbfs(vlist, vcnt, s, t, qs, qt, vcheck, r, f);

		qclean(qs);
		qclean(qt);
		free(vcheck);
}

void dv(Vertex * vlist, ul vcnt, ul s, ul t, Result * r){

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

		dvbfs(vlist, vcnt, s, t, qs, qt, vcheck, r, f);

		qclean(qs);
		qclean(qt);
		free(vcheck);
}

void ee(Vertex * vlist, ul vcnt, ul s, ul t, Result * r){

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

	eebfs(vlist, vcnt, s, t, qs, qt, vcheck, r, f);

	qclean(qs);
	qclean(qt);
	free(vcheck);
}
