#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int lm1,lm2,cm1,cm2,nth;
float **m1,**m2,**m3;
/*aloca matrizes dinamicaente*/
float **alocmat(int lin, int col){
	float **m;
	int i;
	m = (float**) malloc (lin * sizeof(float*));
	for(i=0;i<lin;i++){
		m[i] = (float*)malloc(col*sizeof(float));
	}
	return m;
}
/*preenche matrizes com valores aleatorios*/
void fill(float **m,int lin, int col){
	int i,j;
	for(i=0;i<lin;i++){
		for(j=0;j<col;j++){
			m[i][j]=rand()%100;
		}
	}
}
/*multiplica matrizes*/
void *mult(void *arg){
	int i,j,k;
	int *id = (int*) arg;
	for(i=(*id);i<lm1;i+=nth){
		for(j=0;j<cm2;j++){
			m3[i][j]=0;
			for(k=0;k<cm1;k++){
				m3[i][j]+=m1[i][k]*m2[k][j];
			}
		}
	}
	
}

int main(int argc, char *argv[]){
	lm1=atoi(argv[1]);cm1=atoi(argv[2]);lm2=atoi(argv[2]);cm2=atoi(argv[3]);nth=atoi(argv[4]);
	int i,j,k;
	pthread_t *t= (pthread_t*) malloc (nth*sizeof(pthread_t));
	int *par = (int *)malloc(nth*sizeof(int));
	m1 = alocmat(lm1,cm1);
	m2 = alocmat(lm2,cm2);
	m3 = alocmat(lm1,cm2);
	
	fill(m1,lm1,cm1);
	fill(m2,lm2,cm2);
	/*cria nth threads para multiplicar matrizes*/
	/*a thread i ira calcular os elementos na matriz resultados das linhas i, i+nth, i+2*nth ....*/
	for(i=0;i<nth;i++){
		par[i]=i;
		pthread_create(&t[i],NULL,mult,(void*)&par[i]);
	}
	/*da join em cada uma das threads criadas, assim espera que todas terminem de fazer seu trabalho*/
	for(i=0;i<nth;i++){
		pthread_join(t[i],NULL);
	}
}