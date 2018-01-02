/*
 * usuario/simplon.c
 *
 *  Minikernel. Versi�n 1.0
 *
 *  Fernando P�rez Costoya
 *
 */

/*
 * Programa de usuario que simplemente imprime un valor entero
 */

#include "servicios.h"

#define TOT_ITER 20 /* ponga las que considere oportuno */

int main(){
	int i;

	for (i=0; i<TOT_ITER; i++)
		printf("simplon: i %d\n", i);

	printf("simplon: termina\n");
	return 0;
}
