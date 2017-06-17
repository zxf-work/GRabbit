/*
 * profile.c
 *
 *  Created on: Jun 17, 2017
 *      Author: will
 */

#include "queue.h"

void dg_naivebfs(DVertex * vlist, ul vcnt, ul s,  Queue * qs, char * vcheck, ul * r, ul * d, ul * nextseed, short mark){

	ul qsl = 0;
	ul i = 0;
	ul cur = 0;

	ul hopcnt = 0;


	qsl=qs->length;


	while(qs->length != 0){

		// set the range to traverse
		qsl = qs->length;


		// search from s-side
		//printf("qsl = %ld\n", qsl);
		while(qsl != 0){
			s = qpop(qs);
			qsl--;
			for(i = 0; i < vlist[s].outdgr; i++){
				cur = vlist[s].out[i];

				if(vcheck[cur] != mark){
					vcheck[cur] = mark;
					qadd(qs,cur);
					//printf("\t%ld(add)\t",cur);
				}

			}
			//printf("\n");

		}
		hopcnt++;
	}
	(*r)=hopcnt;
	(*d)=hopcnt;
	(*nextseed)=s;
}


void foursweep(DVertex * vlist, ul vcnt, ul * seed, ul * radius, ul * dia){

	ul s = (*seed);
	ul r = (*radius);
	ul d = (*dia);
	ul nextseed = 0;
	ul mark = 1;

	Queue * qs;
	qs = (Queue*)malloc(sizeof(Queue));
	qinit(qs);
	qadd(qs, s);

	char * vcheck;

	vcheck=(char*)calloc(vcnt,sizeof(char));
	vcheck[s] = 1;

	dg_ssbfs(vlist, vcnt, s, qs, vcheck, &r, &d, &nextseed, 1);
	if(r<(*radius)){
		(*radius)=r;
	}
	if(d>(*dia)){
		(*dia)=d;
	}
	printf("1-sweep: ub = %ld, diameter = %ld\n", radius*2, dia);

	s=nextseed;
	vcheck[s] = 2;
	dg_ssbfs(vlist, vcnt, s, qs, vcheck, &r, &d, &nextseed, 2);
	if(r<(*radius)){
		(*radius)=r;
	}
	if(d>(*dia)){
		(*dia)=d;
	}
	printf("2-sweep: ub = %ld, diameter = %ld\n", radius*2, dia);

	s=nextseed;
	vcheck[s] = 3;
	dg_ssbfs(vlist, vcnt, s, qs, vcheck, &r, &d, &nextseed, 3);
	if(r<(*radius)){
		(*radius)=r;
	}
	if(d>(*dia)){
		(*dia)=d;
	}
	printf("3-sweep: ub = %ld, diameter = %ld\n", radius*2, dia);

	s=nextseed;
	vcheck[s] = 4;
	dg_ssbfs(vlist, vcnt, s, qs, vcheck, &r, &d, &nextseed, 4);
	if(r<(*radius)){
		(*radius)=r;
	}
	if(d>(*dia)){
		(*dia)=d;
	}
	printf("4-sweep: ub = %ld, diameter = %ld\n", radius*2, dia);

	qclean(qs);
	free(vcheck);


}

void dg_diameter(DVertex * vlist, ul vcnt){
	ul seed;
	ul stagecnt = 2000;

	ul i, j, k;

	ul radius = 100000;
	ul dia = 0;

	ul tmpradius = radius;
	ul tmpdia = dia;

	ul ub = radius * 2;

	FILE * fp;
	fp = fopen("source.txt","r");

	for(i=0;i<stagecnt;i++){
		fscanf(fp,"%ld",&seed);
		printf("Stage %ld, starting from vertex %ld\n", i, seed);
		foursweep(vlist,vcnt,&seed,&radius,&dia);

		if(radius<tmpradius){
			ub = radius * 2;
			tmpradius = radius;
		}
		if(dia>tmpdia){
			tmpdia = dia;
		}
		if(dia==ub){
			print("Exact diameter is %ld\n",dia);
			break;
		}
	}
	fclose(fp);

}

