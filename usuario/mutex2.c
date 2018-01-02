/*
 * usuario/mutex2.c
 *
 *  Minikernel. Versión 1.0
 *
 *  Fernando Pérez Costoya
 *
 */

/*
 * Programa de usuario que forma parte de una prueba de los mutex
 *
 */

#include "servicios.h"

int main(){
	int desc1, desc2;

	printf("mutex2 comienza\n");

	if ((desc1=abrir_mutex("m1"))<0)
		printf("error abriendo m1. NO DEBE APARECER\n");

	if ((desc2=abrir_mutex("m2"))<0)
		printf("error abriendo m2. NO DEBE APARECER\n");

	if (lock(desc1)<0)
		printf("error en lock de mutex. NO DEBE APARECER\n");

	printf("mutex2 ha obtenido mutex m1, se bloqueará a continuación al intentar obtener m2\n");

	if (lock(desc2)<0)
		printf("error en lock de mutex. NO DEBE APARECER\n");


	printf("mutex2 ha obtenido mutex m2\n");

	if (unlock(desc2)<0)
		printf("error en unlock de mutex. NO DEBE APARECER\n");

	if (unlock(desc1)<0)
		printf("error en unlock de mutex. NO DEBE APARECER\n");


	printf("mutex2 termina\n");

	return 0;
}
