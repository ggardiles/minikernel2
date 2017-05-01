/*
 * usuario/prueba_RR2.c
 *
 *  Minikernel. Versión 1.0
 *
 *  Fernando Pérez Costoya
 *
 */

/*
 * Programa de usuario que realiza una prueba del round-robin usando
 * procesos que no hacen llamadas al sistema.
 */

#include "servicios.h"

int main(){
	int i;

	printf("prueba_RR2: comienza\n");

	for (i=1; i<=5; i++)
		if (crear_proceso("mudo")<0)
			printf("Error creando mudo\n");
	

	printf("prueba_RR2: termina\n");
	return 0; 
}
