/*
 * usuario/prueba_mutex.c
 *
 *  Minikernel. Versión 1.0
 *
 *  Fernando Pérez Costoya
 *
 */

/*
 * Programa de usuario que realiza una prueba de los mutex
 *
 */

#include "servicios.h"

int main(){
	int desc1, desc2;

	printf("prueba_mutex comienza\n");

	if ((desc1=crear_mutex("m1", NO_RECURSIVO))<0)
		printf("error creando m1. NO DEBE APARECER\n");

	/* Probamos a bloquear un mutex usando un descriptor erróneo */
	if (lock(desc1+1)<0)
		printf("error en lock de mutex. DEBE APARECER\n");

	if ((desc2=crear_mutex("m2", RECURSIVO))<0)
		printf("error creando m2. NO DEBE APARECER\n");

	if (lock(desc1)<0)
		printf("error en lock de mutex. NO DEBE APARECER\n");

	/* segundo lock sobre semáforo no recursivo -> error */
	if (lock(desc1)<0)
		printf("segundo lock en mutex no recursivo. DEBE APARECER\n");

	if (lock(desc2)<0)
		printf("error en lock de mutex. NO DEBE APARECER\n");

	/* segundo lock sobre semáforo recursivo -> correcto */
	if (lock(desc2)<0)
		printf("error en lock de mutex. NO DEBE APARECER\n");

	if (crear_proceso("mutex1")<0)
		printf("Error creando mutex1\n");

	if (crear_proceso("mutex2")<0)
		printf("Error creando mutex2\n");

	printf("prueba_mutex duerme 1 seg.: ejecutarán los procesos mutex1 y mutex2 que se bloquearán en lock de mutex\n");
	dormir(1);

	/* No debe despertar a nadie */
	if (unlock(desc2)<0)
		printf("error en unlock de mutex. NO DEBE APARECER\n");

	printf("prueba_mutex duerme 1 seg.: no ejecutará ningún proceso ya que los mutex están bloqueados\n");
	dormir(1);

	/* Debe despertar al proceso mutex1 */
	if (unlock(desc2)<0)
		printf("error en unlock de mutex. NO DEBE APARECER\n");

	printf("prueba_mutex duerme 1 seg.: debe ejecutar mutex1 ya que se ha liberado el mutex m2\n");
	dormir(1);

	printf("prueba_mutex termina: debe ejecutar mutex2 ya que el cierre implícito de m1 debe despertarlo y mutex1 está dormido\n");

	/* cierre implícito de semáforos: debe despertar a mutex2 */
	return 0;
}
