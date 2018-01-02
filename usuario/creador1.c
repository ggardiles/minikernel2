/*
 * usuario/creador1.c
 *
 *  Minikernel. Versión 1.0
 *
 *  Fernando Pérez Costoya
 *
 */

/*
 * Programa de usuario que crea mutex.
 */

#include "servicios.h"

int main(){

	printf("creador1 comienza\n");

	if (crear_mutex("m1", NO_RECURSIVO)<0)
		printf("error creando m1. NO DEBE SALIR\n");

	if (crear_mutex("m1", NO_RECURSIVO)<0)
		printf("error creando m1. DEBE SALIR\n");

	if (crear_mutex("m2", NO_RECURSIVO)<0)
		printf("error creando m2. NO DEBE SALIR\n");

	if (crear_mutex("m3", NO_RECURSIVO)<0)
		printf("error creando m3. NO DEBE SALIR\n");

	if (crear_mutex("m4", NO_RECURSIVO)<0)
		printf("error creando m4. NO DEBE SALIR\n");

	printf("creador1 duerme 1 segundo\n");
	dormir(1);

	printf("creador1 termina\n");

	/* cierre implícito de mutex */
	return 0;
}
