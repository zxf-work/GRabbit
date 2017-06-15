/*
 * bfstree.c
 *
 *  Created on: Jun 12, 2017
 *      Author: will
 */

#include"bfs.h"


void ssbfs(Vertex * vlist, PArray * bfstree, ul off, ul lm, ul vcnt){
	Queue * qs;


	qs = (Queue*)malloc(sizeof(Queue));

	qinit(qs);

	qadd(qs, lm);
	//ul hop = 0;

	bfstree[lm].lvl[off] = 0;
	char * vcheck;

	vcheck=(char*)calloc(vcnt,sizeof(char));
	vcheck[lm] = 1;

	ul qsl = 1;
	ul i = 0;
	ul cur = 0;
	ul s = lm;
	ul hop=0;

	while(qs->length != 0){

		// set the range to traverse
		qsl = qs->length;
		printf("%ld-hop: %ld vertices\n",hop++,qsl);

		// search from s-side
		//printf("qsl = %ld\n", qsl);
		while(qsl != 0){
			s = qpop(qs);
			qsl--;
			//printf("%ld-s-%ld:\t",hopcnt+1,s);

			for(i = 0; i < vlist[s].dgr; i++){
				cur = vlist[s].ngb[i];

				if(vcheck[cur] == 0){
					vcheck[cur] = 1;
					bfstree[cur].parent[off] = s;
					bfstree[cur].lvl[off] = bfstree[s].lvl[off] + 1;
					qadd(qs,cur);
						//printf("\t%ld(add)\t",cur);
				}

			}
		}
	}

	qclean(qs);

	free(vcheck);
}

void getbfstree(Vertex * vlist, PArray * bfstree, ul * roots, ul vcnt, ul l){
	ul i = 0;
	ul j = 0;
	FILE * fp;

	fp=fopen("kbfstree","r");
	if(fp!=NULL){
		for(i=0;i<vcnt;i++){
			for(j=0;j<l;j++){
				fscanf(fp,"%ld%ld",&bfstree[i].parent[j], &bfstree[i].lvl[j]);
			}
		}
		fclose(fp);
		printf("k-bfstree loaded\n");
	}
	else{
		printf("Generating k-bfs-trees:\n");
		for(i = 0; i < l; i++){
			ssbfs(vlist, bfstree, i, roots[i], vcnt);
			printf("%ldth tree done\n",i);
		}
		fp=fopen("kbfstree","w");
		for(i = 0; i < vcnt; i++){
			for(j = 0; j < l; j++){
				fprintf(fp,"%ld %ld ", bfstree[i].parent[j], bfstree[i].lvl[j]);
			}
			fprintf(fp,"\n");
		}
		fclose(fp);
		printf("dumping k-bfstree log to disk\n");
	}

}

void ktree(Vertex * vlist, PArray * bfstree, ul vcnt, ul s, ul t, ul k, Result * r){

	char * vcheck;

	vcheck=calloc(vcnt,sizeof(char));

	ul i = 0;
	ul j = 0;


	Flag * f;

	f=(Flag*)malloc(sizeof(Flag));
	f->meet = false;


	r->s = s;
	r->t = t;

	ul src;
	ul des;
	ul s_hop = 0;
	ul t_hop = 0;
	ul * diff;
	ul min = 10000;
	float t_total = 0.0;

	diff = calloc(k, sizeof(ul));



	for(i = 0; i < k; i++){
		clock_t begin = clock();
		src = s;
		des = t;
		//vcheck = calloc(vcnt, sizeof(char));
		f->meet=false;

		vcheck[src]=i+1;
		vcheck[des]=i+1;
		s_hop = 0;
		t_hop = 0;

		if(src == des){
			f->meet = true;
			diff[i] = 2;
			continue;
		}
		else{
			if(bfstree[s].lvl[i]>bfstree[t].lvl[i]){
				diff[i]=bfstree[s].lvl[i]-bfstree[t].lvl[i];
				for(j=0;j<diff[i];j++){
					src=bfstree[src].parent[i];
					r->etotal++;
					r->vtotal++;
				}
			}
			if(bfstree[s].lvl[i]<bfstree[t].lvl[i]){
				diff[i]=bfstree[t].lvl[i]-bfstree[s].lvl[i];
				for(j=0;j<diff[i];j++){
					des=bfstree[des].parent[i];
					r->etotal++;
					r->vtotal++;
				}
			}
		}

		while(src!=0 && des!=0 && !f->meet){
			src = bfstree[src].parent[i];
			s_hop++;
			r->etotal++;
			r->vtotal++;
			//vcheck[src]=1;
			vcheck[src]=i+1;
			des = bfstree[des].parent[i];
			t_hop++;
			r->etotal++;
			r->vtotal++;
			if(vcheck[des]==i+1){
				f->meet=true;
				r->mid = des;
				break;
			}
			vcheck[des]=i+1;
		}

		if(f->meet){
			diff[i]+=s_hop;
			diff[i]+=t_hop;
			if(diff[i]<min)
				min=diff[i];
		}

		clock_t end = clock();
		t_total += ((float)(end-begin)/1000000.0F)*1000;
		//free(vcheck);
		//for(j=0;j<vcnt;j++)
		//	vcheck[j]=0;
	}
	r->d=min;



	r->ttotal += t_total;


	if(f->meet){
		printf("%ld[%ld] - %ld[%ld] dist: %ld v_total: %ld e_total: %ld t_total: %f ms\n", r->s, vlist[r->s].dgr, r->t, vlist[r->t].dgr, r->d, r->vtotal, r->etotal, r->ttotal);
	}
	else{
		printf("%ld[%ld] - %ld[%ld] dist: null v_total: %ld e_total: %ld t_total: %f ms\n", r->s, vlist[r->s].dgr, r->t, vlist[r->t].dgr, r->vtotal, r->etotal, r->ttotal);
	}

	free(vcheck);
}





