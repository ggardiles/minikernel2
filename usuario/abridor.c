/*
 * usuario/abridor.c
 *
 *  Minikernel. Versión 1.0
 *
 *  Fernando Pérez Costoya
 *
 */

/*
 * Programa de usuario que prueba la funcionalidad de las primitivas
 * que crean, abren y cierran mutex
 */

#include "servicios.h"

int main(){
	int desc;

	printf("abridor comienza\n");

	/* abre mutex que no existe */
	if (abrir_mutex("m0")<0)
		printf("error abriendo m0. DEBE SALIR\n");

	if ((desc=abrir_mutex("m1"))<0)
		printf("error abriendo m1. NO DEBE SALIR\n");

	if (abrir_mutex("m2")<0)
		printf("error abriendo m2. NO DEBE SALIR\n");

	if (abrir_mutex("m3")<0)
		printf("error abriendo m3. NO DEBE SALIR\n");

	if (abrir_mutex("m4")<0)
		printf("error abriendo m4. NO DEBE SALIR\n");

	/* Error: ha agotado los descriptores */
	if (abrir_mutex("m5")<0)
		printf("error abriendo m5. DEBE SALIR\n");

	/* libera un descriptor de mutex (m1) */
	cerrar_mutex(desc);

	/* Agotado num mutex del sistema. Debe bloquearse */
	if (crear_mutex("m17", 0)<0)
		printf("error creando m17. NO DEBE SALIR\n");
	/* se desbloqueará cuando se elimine m1 */

	/* intenta crear el mismo mutex: devuelve un error porque ya existe */
	if (crear_mutex("m17", 0)<0)
		printf("error creando m17. DEBE SALIR\n");

	printf("abridor termina\n");
	return 0;
}
