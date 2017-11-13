#include<stdio.h>
#include<pthread.h>
#define NTH 5
void *print(void *arg){
	int *x = (int*) arg;
	printf("numero:%d\n",*x);
	pthread_exit(0);
}

int main(){
	pthread_t t[NTH];
	int i;
	int p[NTH];
	for(i=0;i<5;i++){
		p[i]=i;
		pthread_create(&t[i],NULL,print,(void*) &p[i]);
	}
	for(i=0;i<5;i++){
		pthread_join(t[i],NULL);
	}
}