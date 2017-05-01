/*
 * usuario/prueba_term.c
 *
 *  Minikernel. Versión 1.0
 *
 *  Fernando Pérez Costoya
 *
 */

/*
 * Programa de usuario que realiza una prueba del terminal
 */

#include "servicios.h"

int main(){
	int i;

	printf("prueba_term: comienza\n");

	for (i=1; i<=2; i++)
		if (crear_proceso("lector")<0)
			printf("Error creando lector\n");
	

	printf("prueba_term: termina\n");
	return 0; 
}
