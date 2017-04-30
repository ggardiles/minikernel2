/*
 * usuario/mudo.c
 *
 *  Minikernel. Versión 1.0
 *
 *  Fernando Pérez Costoya
 *
 */

/*
 * Programa de usuario que "gasta CPU".
 */

#include "servicios.h"

#define TOT_ITER 20000000	/* ponga las que considere oportuno */

int main(){
	int i, tot;
	int j=5;

	for (i=0; i<TOT_ITER; i++)
		tot=j*i;
	printf("mudo (%d): termina\n", obtener_id_pr());
	tot--;
	return 0;
}
