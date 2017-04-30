/*
 * usuario/creador3.c
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

	printf("creador3 comienza\n");

	if (crear_mutex("m9", NO_RECURSIVO)<0)
		printf("error creando m9. NO DEBE SALIR\n");

	if (crear_mutex("m10", NO_RECURSIVO)<0)
		printf("error creando m10. NO DEBE SALIR\n");

	if (crear_mutex("m11", NO_RECURSIVO)<0)
		printf("error creando m11. NO DEBE SALIR\n");

	if (crear_mutex("m12", NO_RECURSIVO)<0)
		printf("error creando m12. NO DEBE SALIR\n");

	printf("creador3 duerme 1 segundo\n");
	dormir(1);

	printf("creador3 termina\n");

        /* cierre implícito de mutex */

	return 0;
}
