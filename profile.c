/*
 * profile.c
 *
 *  Created on: Jun 17, 2017
 *      Author: will
 */

#include "queue.h"

void dg_ssbfs(DVertex * vlist, ul vcnt, ul s,  Queue * qs, char * vcheck, ul * d, ul * nextseed, short mark){

	ul qsl = 0;
	ul i = 0;
	ul cur = 0;
	ul tmp = 0;

	ul hopcnt = 0;

	if(mark%2==1){
		while(qs->length != 0){
			qsl = qs->length;

			while(qsl != 0){
				s = qpop(qs);
				qsl--;

					for(i = 0; i < vlist[s].outdgr; i++){
						cur = vlist[s].out[i];

						if(vcheck[cur] != mark){
							vcheck[cur] = mark;
							tmp = cur;
							qadd(qs,cur);
						//printf("\t%ld(add)\t",cur);
						}

					}

			}
			hopcnt++;

		}

	}
	else{
	while(qs->length != 0){
		qsl = qs->length;

		while(qsl != 0){
			s = qpop(qs);
			qsl--;

				for(i = 0; i < vlist[s].indgr; i++){
					cur = vlist[s].in[i];

					if(vcheck[cur] != mark){
						vcheck[cur] = mark;
						tmp = cur;
						qadd(qs,cur);
						//printf("\t%ld(add)\t",cur);
					}

				}


			//printf("\n");

		}
		hopcnt++;

	}

	}

	(*d)=hopcnt;
	(*nextseed)=tmp;
}


void foursweep(DVertex * vlist, ul vcnt, ul * seed,  ul * dia){

	ul s = (*seed);

	ul d = (*dia);
	ul nextseed = 0;


	Queue * qs;
	qs = (Queue*)malloc(sizeof(Queue));
	qinit(qs);
	qadd(qs, s);

	char * vcheck;

	vcheck=(char*)calloc(vcnt,sizeof(char));
	vcheck[s] = 1;

	dg_ssbfs(vlist, vcnt, s, qs, vcheck, &d, &nextseed, 1);

	if(d>(*dia)){
		(*dia)=d;
		printf("Source [%ld]: 1-sweep [%ld]: diameter = %ld\n",(*seed), s, (*dia));
	}


	s=nextseed;
	vcheck[s] = 2;
	qadd(qs, s);
	dg_ssbfs(vlist, vcnt, s, qs, vcheck, &d, &nextseed, 2);

	if(d>(*dia)){
		(*dia)=d;
		printf("Source [%ld]: 2-sweep [%ld]: diameter = %ld\n",(*seed), s, (*dia));
	}
	//printf("2-sweep [%ld]: diameter = %ld\n", s, d);

	s=nextseed;
	vcheck[s] = 3;
	qadd(qs, s);
	dg_ssbfs(vlist, vcnt, s, qs, vcheck, &d, &nextseed, 3);

	if(d>(*dia)){
		(*dia)=d;
		printf("Source [%ld]: 3-sweep [%ld]: diameter = %ld\n",(*seed), s, (*dia));
	}
	//printf("3-sweep [%ld]:  diameter = %ld\n", s, d);

	s=nextseed;
	vcheck[s] = 4;
	qadd(qs, s);
	dg_ssbfs(vlist, vcnt, s, qs, vcheck, &d, &nextseed, 4);

	if(d>(*dia)){
		(*dia)=d;
		printf("Source [%ld]: 4-sweep [%ld]: diameter = %ld\n",(*seed), s, (*dia));
	}
	//printf("4-sweep [%ld]:  diameter = %ld\n", s, d);

	qclean(qs);
	free(vcheck);


}

void dg_diameter(DVertex * vlist, ul vcnt){
	ul seed;
	ul stagecnt = 2000;

	ul i, j, k;

	ul dia = 0;
	ul tmpdia = dia;

	FILE * fp;
	fp = fopen("source.txt","r");

	j=stagecnt/100;
	k=0;

	for(i=0;i<stagecnt;i++){
		fscanf(fp,"%ld",&seed);
		if(i%j==0){
			printf("<%ld>\n", k++);
		}
		foursweep(vlist,vcnt,&seed,&dia);


		if(dia>tmpdia){
			tmpdia = dia;
		}

	}
	printf("diameter is above %ld \n", dia);
	fclose(fp);

}

