#include <pthread.h>
#include <stdio.h>

void *thread_hello(void *arg){
	printf("Ola, eu sou uma thread!\n");
	pthread_exit(0);
}

int main(){
	pthread_t t;
	pthread_create(&t,NULL,thread_hello,NULL);
	pthread_join(t,NULL);
}