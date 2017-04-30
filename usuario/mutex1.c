/*
 * usuario/mutex1.c
 *
 *  Minikernel. Versi�n 1.0
 *
 *  Fernando P�rez Costoya
 *
 */

/*
 * Programa de usuario que forma parte de una prueba de los mutex
 *
 */

#include "servicios.h"

int main(){
	int desc;

	printf("mutex1 comienza\n");

	if ((desc=abrir_mutex("m2"))<0)
		printf("error abriendo m2. NO DEBE APARECER\n");

	if (lock(desc)<0)
		printf("error en lock de mutex. NO DEBE APARECER\n");

	/* segundo lock sobre sem�foro recursivo -> correcto */
	if (lock(desc)<0)
		printf("error en lock de mutex. NO DEBE APARECER\n");

	printf("mutex1 duerme 2 segs.: no debe ejecutar ning�n proceso, ya que prueba_mutex est� dormido y mutex2 bloqueado en mutex m1\n");
	dormir(2);

	/* cierre de sem�foro: debe despertar a mutex2 */
	if (cerrar_mutex(desc)<0)
		printf("error al cerrar mutex. NO DEBE APARECER\n");

	printf("mutex1 duerme 1 seg.: debe ejecutar mutex2 ya que cierre de m2 debe desbloquearlo\n");
	dormir(1);

	printf("mutex1 termina\n");

	return 0;
}
