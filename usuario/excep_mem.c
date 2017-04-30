/*
 * usuario/excep_mem.c
 *
 *  Minikernel. Versi�n 1.0
 *
 *  Fernando P�rez Costoya
 *
 */

/*
 * Programa de usuario que fuerza una excepci�n en acceso a memoria.
 * Adem�s crea un proceso hijo (simplon).
 */

#include "servicios.h"

#define TOT_ITER 20	/* N�mero total de iteraciones */
#define ITER_EXCEP 12	/* iteraci�n en la que causa excepci�n */

int main(){
	int i;
	int *p=0;

	if (crear_proceso("simplon")<0)
		printf("Error creando simplon\n");

	for (i=0; i<TOT_ITER; i++){
		printf("excep_mem: i %d\n", i);
		if ((i+1)%ITER_EXCEP==0)
			*p=5;
	}
	printf("excep_mem: termina\n");
	terminar_proceso();
	return 0; /* No se deber�a llegar a este punto */
}

