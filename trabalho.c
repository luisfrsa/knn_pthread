#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

float calculaEucliciana(float el1,float el2){
	return pow((el1-el2),2);
}

int main(int argc, char *argv[]){
	FILE *file;
	char *line = NULL,
		 *split,
	     read,
	     dir[]="bases/init.data";
	size_t len = 0;
	int num_elementos=59;
	int aux=0;
	file = fopen(dir, "r");
	if(file == NULL)
    	printf("Erro, nao foi possivel abrir o arquivo\n");
    else{
		while ((read = getline(&line, &len, file)) != -1) {
    		printf("Line: %s \n", line);
    		while((split = strsep(&line,",")) != NULL ){
       			printf("Split[%d]: %s\n",aux,split);
       			aux++;
    		}
    		aux--;
    		printf("%d elementos.\n",aux);
    		break;
		}
    }
    return 0;
}
/*float getPositivo(float entrada){	if(entrada>=0){		return entrada;	}	return entrada*-1;}*/

