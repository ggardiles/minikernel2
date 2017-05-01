/*
 * usuario/creador2.c
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

	printf("creador2 comienza\n");

	if (crear_mutex("m5", NO_RECURSIVO)<0)
		printf("error creando m5. NO DEBE SALIR\n");

	if (crear_mutex("m6", NO_RECURSIVO)<0)
		printf("error creando m6. NO DEBE SALIR\n");

	if (crear_mutex("m7", NO_RECURSIVO)<0)
		printf("error creando m7. NO DEBE SALIR\n");

	if (crear_mutex("m8", NO_RECURSIVO)<0)
		printf("error creando m8. NO DEBE SALIR\n");

	printf("creador2 duerme 1 segundo\n");
	dormir(1);

	printf("creador2 termina\n");

        /* cierre implícito de mutex */

	return 0;
}
