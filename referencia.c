#include <stdio.h>
#include <stdlib.h>

void foo (int *n){
	*n = *n*2;
	printf("o valor de N dentro de foo() e %d\n",*n);
}

void bar (int n){
	n = n*3;
	printf("o valor de N dentro de bar() e %d\n",n);
}

int main(int argc, char *argv[]){
	int n = 10;
	printf("O valor de n antes de bar() %d\n",n);
	bar(n);
	printf("O valor de n depois de bar() %d\n",n);
	printf("O valor de n antes de foo() %d\n",n);
	foo(&n);
	printf("O valor de n depois de foo() %d\n",n);
	return 0;
}