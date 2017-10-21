#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct musica{
	float *array;
	char *genero;
};

double calculaEucliciana(double el1,double el2){
	return pow((el1-el2), 2);
}
int countChars( char* s, char c ){
    return *s == '\0'? 0: countChars( s + 1, c ) + (*s == c);
}
void print_array(float *array, int length){
	printf("\n Printando array ");
    for (int i = 0; i < length; i++) {
    	printf("array[%d] => %f; ",i,array[i]);
    }
}
void leituraArquivo(char dir[],struct musica *musica_return,int *qdeElem){
	size_t len = 0;
	FILE *file;
	char *line = NULL,
	     *split,
		 read;
	*qdeElem=0;
	float *array;
	file = fopen(dir, "r");
	int ind_array=0;
	struct musica principal;
	if(file == NULL)
    	printf("Erro, nao foi possivel abrir o arquivo\n");
    else{
		while ((read = getline(&line, &len, file)) != -1) {
    		printf("Line: %s \n", line);
    		*qdeElem = countChars(line,',');//retorna 59 em Split[58]: 0.283174, Split[59]: forro
    		printf("%d elementos.\n",*qdeElem);
    		array = (float *)malloc(*qdeElem*sizeof(float));

    		while((split = strsep(&line,",")) != NULL ){
    			if(ind_array!=*qdeElem){
	    			array[ind_array] = strtof(split, NULL);
	       		}else{
	       			principal.genero = split;
	       		}
       			ind_array++;
    		}    	
    		principal.array = array;
    		print_array(principal.array,*qdeElem);
    		printf("\n . %s ",principal.genero);
    		*musica_return = principal;
    		break;
		}
    }
    
}

int main(int argc, char *argv[]){
	
	char dir[]="bases/init.data";
	
	int qdeElem;
	float *array;
	struct musica principal;
	leituraArquivo(dir,& principal,& qdeElem);
	printf("\n ggg ");
	print_array(principal.array,qdeElem);
    return 0;
}
/*float getPositivo(float entrada){	if(entrada>=0){		return entrada;	}	return entrada*-1;}*/

