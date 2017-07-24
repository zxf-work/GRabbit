/*
 * profile.c
 *
 *  Created on: Jun 17, 2017
 *      Author: will
 */

#include "queue.h"

void dg_ssbfs(DVertex * vlist, ul vcnt, ul s,  Queue * qs, char * vcheck, ul * d, ul * nextseed, short mark, ul * scheck){

	ul qsl = 0;
	ul i = 0;
	ul cur = 0;
	ul tmp = 0;

	ul hopcnt = 0;

	if(mark%2==0){
		while(qs->length != 0){
			qsl = qs->length;

			while(qsl != 0){
				s = qpop(qs);
				qsl--;

					for(i = 0; i < vlist[s].outdgr; i++){
						cur = vlist[s].out[i];

						if(vcheck[cur] != mark){
							vcheck[cur] = mark;
							if(scheck[cur]==0)
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
						if(scheck[cur]==0)
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


void foursweep(DVertex * vlist, ul vcnt, ul * seed,  ul * dia, ul * scheck){

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
	scheck[s] = 1;

	dg_ssbfs(vlist, vcnt, s, qs, vcheck, &d, &nextseed, 1, scheck);

	if(d>(*dia)){
		(*dia)=d;
		printf("Source [%ld]: 1-sweep [%ld]: diameter = %ld\n",(*seed), s, (*dia));
	}
	printf("\t1-sweep [%ld]: diameter = %ld\n", s, d);


	s=nextseed;
	vcheck[s] = 2;
	scheck[s] = 1;
	qadd(qs, s);
	dg_ssbfs(vlist, vcnt, s, qs, vcheck, &d, &nextseed, 2, scheck);

	if(d>(*dia)){
		(*dia)=d;
		printf("Source [%ld]: 2-sweep [%ld]: diameter = %ld\n",(*seed), s, (*dia));
	}
	printf("\t2-sweep [%ld]: diameter = %ld\n", s, d);

	s=nextseed;
	vcheck[s] = 3;
	scheck[s] = 1;
	qadd(qs, s);
	dg_ssbfs(vlist, vcnt, s, qs, vcheck, &d, &nextseed, 3, scheck);

	if(d>(*dia)){
		(*dia)=d;
		printf("Source [%ld]: 3-sweep [%ld]: diameter = %ld\n",(*seed), s, (*dia));
	}
	printf("\t3-sweep [%ld]:  diameter = %ld\n", s, d);

	s=nextseed;
	vcheck[s] = 4;
	scheck[s] = 1;
	qadd(qs, s);
	dg_ssbfs(vlist, vcnt, s, qs, vcheck, &d, &nextseed, 4, scheck);

	if(d>(*dia)){
		(*dia)=d;
		printf("Source [%ld]: 4-sweep [%ld]: diameter = %ld\n",(*seed), s, (*dia));
	}
	printf("\t4-sweep [%ld]:  diameter = %ld\n", s, d);

	qclean(qs);
	free(vcheck);


}

void dg_diameter(DVertex * vlist, ul vcnt){
	ul seed;
	ul stagecnt = 100;

	ul i, j, k;

	ul dia = 0;
	ul tmpdia = dia;

	FILE * fp;
	fp = fopen("source.txt","r");
	ul * scheck;

	scheck=calloc(vcnt, sizeof(ul));


	for(i=0;i<stagecnt;i++){
		fscanf(fp,"%ld",&seed);
		printf("<%ld>\n", i);
		foursweep(vlist,vcnt,&seed,&dia,scheck);


		if(dia>tmpdia){
			tmpdia = dia;
		}

	}
	printf("diameter is above %ld \n", dia);
	fclose(fp);

	free(scheck);
}

