#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define FLT_MAX 3.402823466e+38F /* max value */

typedef struct Musica{
	float *array;
	char *genero;
} Musica;

void debugArq(char line[], int qdeElem){
	printf("Line: %s \n", line);
    printf("%d elementos \n",qdeElem);
}
void print_array(float *array, int length){
	printf("\nPrintando array ");
    for (int i = 0; i < length; i++) {
    	printf("\narray[%d] => %f; ",i,array[i]);
    }
}

int countChars( char* s, char c ){
    return *s == '\0'? 0: countChars( s + 1, c ) + (*s == c);
}

float calculaEucliciana(float el1,float el2){
	return pow((el1-el2), 2);
}
float distanciaMusica(struct Musica caso_teste,struct Musica caso_treino,int qdeElem){
	float distancia=0;
	for(int i=0;i<qdeElem;i++){
		distancia+=calculaEucliciana(caso_teste.array[i],caso_treino.array[i]);
	}	
	distancia = sqrt(distancia);
	/*print_array(caso_treino.array,qdeElem);
	print_array(caso_teste.array,qdeElem);
	printf("\n Genero %s ",caso_treino.genero);
	printf("\n Genero %s ",caso_teste.genero);
	
	printf("\n Distancia entre %s e %s: %.10f ",caso_teste.genero,caso_treino.genero,distancia);
	*/
	return distancia;
}
void treino(struct Musica caso_teste,int qdeElem){

	char *line = NULL,
	     *split,
		 read,
		 dir[]="bases/train_59.data";
	int ind_array,
		qdeMusicas=0;
	size_t len = 0;
	FILE *file;
	float distancia,
		  MENOR_DISTANCIA=FLT_MAX;
	struct Musica MELHOR_MUSICA;
	struct Musica *casos_treino = (struct Musica *)malloc(sizeof(struct Musica));


	/*-----var def-----*/

	file = fopen(dir, "r");
	if(file != NULL){
		while ((read = getline(&line, &len, file)) != -1) {
			ind_array=0;
    		//debugArq(line,qdeElem);
			//printf("\nQDE musica %d",qdeMusicas);
    		casos_treino = (struct Musica *)realloc(casos_treino,(qdeMusicas+1)*sizeof(Musica));
    		casos_treino[qdeMusicas].array = (float *)malloc(qdeElem*sizeof(float));

    		while((split = strsep(&line,",")) != NULL ){
    			if(ind_array!=qdeElem){
	    			casos_treino[qdeMusicas].array[ind_array] = strtof(split, NULL);
	       		}else{
	       			casos_treino[qdeMusicas].genero = strtok(split, "\n");
	       		}
       			ind_array++;
    		}    	
    		//printf("\nTreino %s",casos_treino[qdeMusicas].genero);
    		
    		distancia = distanciaMusica(caso_teste,casos_treino[qdeMusicas],qdeElem);

    		if(distancia < MENOR_DISTANCIA){
    			MENOR_DISTANCIA = distancia;
    			MELHOR_MUSICA = casos_treino[qdeMusicas];
    		}
    		qdeMusicas++;
		}
		printf("\n Menor Distancia %.10f ",MENOR_DISTANCIA);
		printf("\n Genero encontrado %s; Genero correto %s",MELHOR_MUSICA.genero,caso_teste.genero);
		fclose(file);
    }else{
    	printf("Erro, nao foi possivel abrir o arquivo %s \n",dir);
	}

}
void leituraArquivo(char dir[],struct Musica **musicas_return,int *qdeElem,int *qdeMusicas){
	size_t len = 0;
	FILE *file;
	char *line = NULL,
	     *split,
		 read;
	*qdeElem=0;
	float *array;
	file = fopen(dir, "r");
	int ind_array=0;
	*qdeMusicas=0;

	struct Musica *musicas = (struct Musica *)malloc(sizeof(struct Musica));
	
	file = fopen(dir, "r");
	if(file != NULL){
		while ((read = getline(&line, &len, file)) != -1) {
			ind_array=0;
    		if(*qdeElem==0){
    			*qdeElem = countChars(line,',');//retorna 59 em Split[58]: 0.283174, Split[59]: forro
    		}
    		//debugArq(line,qdeElem);
    		musicas = (struct Musica *)realloc(musicas,(*qdeMusicas+1)*sizeof(Musica));
    		musicas[*qdeMusicas].array = (float *)malloc(*qdeElem*sizeof(float));

    		while((split = strsep(&line,",")) != NULL ){
    			if(ind_array!=*qdeElem){
	    			musicas[*qdeMusicas].array[ind_array] = strtof(split, NULL);
	       		}else{
	       			musicas[*qdeMusicas].genero = strtok(split, "\n");
	       		}
       			ind_array++;
    		}    	
    		//treino(musicas[qdeMusicas],qdeElem);
    		*qdeMusicas+=1;
		}
		*musicas_return = musicas;

		fclose(file);
    }else{
    	printf("Erro, nao foi possivel abrir o arquivo %s \n",dir);
	}
    
}
void calcula_menor_distancia(Musica caso_teste, Musica *casos_treino,int qdeElem,int size_treino,float *MENOR_DISTANCIA, Musica *MELHOR_MUSICA){
	*MENOR_DISTANCIA=FLT_MAX;
	float distancia;
	for(int i=0;i<size_treino;i++){
		distancia = distanciaMusica(caso_teste,casos_treino[i],qdeElem);
		/*printf("\n distancia %.10f ",distancia);
		printf("\n gen %s ",caso_teste.genero);
		printf("\n gen %s ",casos_treino[i].genero);
		/**/
		if(distancia < *MENOR_DISTANCIA){
			*MENOR_DISTANCIA = distancia;
			*MELHOR_MUSICA = casos_treino[i];
		}
	}
}
int main(int argc, char *argv[]){		
	char *line = NULL,
	     *split,
		 read,
		 dir_test[]="bases/test_154.data",
		 dir_treino[]="bases/train_154.data";

	int qdeElem=0,
	    ind_array=0,
	    qdeMusicas=0,
	    size_teste,
	    size_treino;
	size_t len = 0;
	float MENOR_DISTANCIA;
	struct Musica MELHOR_MUSICA;
	struct Musica *casos_teste = (struct Musica *)malloc(sizeof(struct Musica));
	struct Musica *casos_treino = (struct Musica *)malloc(sizeof(struct Musica));
	/*-----var def-----*/
	printf("\n::Iniciando::");

	leituraArquivo(dir_test,&casos_teste,&qdeElem,&size_teste);
	leituraArquivo(dir_treino,&casos_treino,&qdeElem,&size_treino);

	/*printf("\nSize [%d]",size_teste);
	printf("\nSize [%d]",size_treino);
*/
	for(int i=0;i<size_teste;i++){
		calcula_menor_distancia(casos_teste[i],casos_treino,qdeElem,size_treino,&MENOR_DISTANCIA,&MELHOR_MUSICA);
		printf("\n Genero: [%s => %s]; Menor distancia %.10f ",casos_teste[i].genero,MELHOR_MUSICA.genero,MENOR_DISTANCIA);
	}
	/*
	print_array(casos_teste[0].array,qdeElem);
	print_array(casos_treino[0].array,qdeElem);
	*/
	printf("\n");
    return 0;
}
/*
steps:
ler arquivo teste
para cada linha arquivo teste, pesquisar em todo treino
qual tiver menor raiz((el1-el2)²+..+(eln-eln)²+)
*/
/*float getPositivo(float entrada){	if(entrada>=0){		return entrada;	}	return entrada*-1;}*/

