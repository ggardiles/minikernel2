/*
 * usuario/creador4.c
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

	printf("creador4 comienza\n");

	if (crear_mutex("m13", NO_RECURSIVO)<0)
		printf("error creando m13. NO DEBE SALIR\n");

	if (crear_mutex("m14", NO_RECURSIVO)<0)
		printf("error creando m14. NO DEBE SALIR\n");

	if (crear_mutex("m15", NO_RECURSIVO)<0)
		printf("error creando m15. NO DEBE SALIR\n");

	if (crear_mutex("m16", NO_RECURSIVO)<0)
		printf("error creando m16. NO DEBE SALIR\n");

	printf("creador4 duerme 1 segundo\n");
	dormir(1);

	printf("creador4 termina\n");

        /* cierre implícito de mutex */

	return 0;
}
