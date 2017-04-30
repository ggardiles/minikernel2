/*
 * usuario/init.c
 *
 *  Minikernel. Versi�n 1.0
 *
 *  Fernando P�rez Costoya
 *
 */

/* Programa inicial que arranca el S.O. S�lo se ejecutar�n los programas
   que se incluyan aqu�, que, evidentemente, pueden ejecutar otros
   programas...
*/

/*
 *
 * Contiene las mismas pruebas que se realizan para evaluar la pr�ctica.
 * Para llevar a cabo cada prueba, comente y descomente
 * las l�neas correspondientes. En la versi�n inicial, la parte descomentada
 * se corresponde con funcionalidad ya implementada en el material de apoyo.
 *
 */

#include "servicios.h"

int main(){

	printf("init: comienza\n");

/* EJEMPLO DE PRUEBA INICIAL QUE YA FUNCIONA PUESTO QUE CORRESPONDE CON LA
FUNCIONALIDAD YA IMPLEMENTADA EN EL MATERIAL DE APOYO. UNA VEZ QUE IMPLEMENTE
ALGO COMENTE ESTA PARTE Y DESCOMENTE LA PRUEBA CORRESPONDIENTE */

	if (crear_proceso("simplon")<0)
                printf("Error creando simplon\n");

	if (crear_proceso("excep_arit")<0)
		printf("Error creando excep_arit\n");

	if (crear_proceso("excep_mem")<0)
		printf("Error creando excep_mem\n");
	
	if (crear_proceso("noexiste")<0)
		printf("Error creando noexiste\n");

/* FIN PRUEBA INICIAL */

// PRUEBA DE LA LLAMADA OBTENER_ID_PR
{
        int i;
        for (i=1; i<=2; i++)
                if (crear_proceso("yosoy")<0)
                        printf("Error creando yosoy\n");
}


/* PRUEBA DE LA LLAMADA DORMIR*/
	if (crear_proceso("prueba_dormir")<0)
		printf("Error creando prueba_dormir\n");


/* PRUEBA DE LA LLAMADA TIEMPOS_PROCESO */
	if (crear_proceso("prueba_tiempos")<0)
		printf("Error creando prueba_tiempos\n");


/* PRIMERA PRUEBA DE MUTEX
	if (crear_proceso("prueba_mutex1")<0)
		printf("Error creando prueba_mutex1\n");
*/

/* SEGUNDA PRUEBA DE MUTEX
	if (crear_proceso("prueba_mutex2")<0)
		printf("Error creando prueba_mutex2\n");
*/

/* PRIMERA PRUEBA DE ROUND-ROBIN
	if (crear_proceso("prueba_RR1")<0)
		printf("Error creando prueba_RR1\n");
*/

/* SEGUNDA PRUEBA DE ROUND-ROBIN
	if (crear_proceso("prueba_RR2")<0)
		printf("Error creando prueba_RR2\n");
*/

/* PRUEBA DEL TERMINAL
	if (crear_proceso("prueba_term")<0)
		printf("Error creando prueba_term\n");
*/

	printf("init: termina\n");
	return 0; 
}
