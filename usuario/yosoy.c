/*
 * usuario/yosoy.c
 *
 *  Minikernel. Versi�n 1.0
 *
 *  Fernando P�rez Costoya
 *
 */

/*
 * Programa de usuario que simplemente imprime su identificador
 */

#include "servicios.h"

#define TOT_ITER 20	/* ponga las que considere oportuno */

int main(){
	int i, id;

	id=obtener_id_pr();
	for (i=0; i<TOT_ITER; i++)
		printf("yosoy (%d): i %d\n", id, i);
	printf("yosoy (%d): termina\n", id);
	return 0;
}

