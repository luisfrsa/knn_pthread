#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

float *v1, 
	  *v2,
	  *r;
long int nth, tam;

void * soma(void * arg) {
  long int tid = (long int) arg;
  long int i;
  for (i = tid; i < tam; i += nth) {
    r[i] = v1[i] + v2[i];
  }
}

int main(int argc, char * argv[]) {
  long int i;
  tam = atoi(argv[1]);
  nth = atoi(argv[2]);
  pthread_t * t = (pthread_t * ) malloc(nth * sizeof(pthread_t));
  v1 = (float * ) malloc(tam * sizeof(float));
  v2 = (float * ) malloc(tam * sizeof(float));
  r = (float * ) malloc(tam * sizeof(float));
  for (i = 0; i < tam; i++) {
    v1[i] = rand() % 100;
    v2[i] = rand() % 100;
  }
  for (i = 0; i < nth; i++) {
    pthread_create( & t[i], NULL, soma, (void * ) i);
  }
  for (i = 0; i < nth; i++) {
    pthread_join(t[i], NULL);
  }
}