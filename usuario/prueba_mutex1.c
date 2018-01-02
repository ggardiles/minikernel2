/*
 * usuario/prueba_mutex1.c
 *
 *  Minikernel. Versión 1.0
 *
 *  Fernando Pérez Costoya
 *
 */

/*
 * Programa de usuario que realiza una prueba de las llamadas crear,
 * abrir y cerrar de mutex
 */

#include "servicios.h"

int main(){


	printf("prueba_mutex1: comienza\n");

	if (crear_proceso("creador1")<0)
		printf("Error creando creador1\n");
	
	if (crear_proceso("creador2")<0)
		printf("Error creando creador2\n");
	
	if (crear_proceso("creador3")<0)
		printf("Error creando creador3\n");
	
	if (crear_proceso("creador4")<0)
		printf("Error creando creador4\n");
	
	if (crear_proceso("abridor")<0)
		printf("Error creando abridor\n");

	printf("prueba_mutex1: termina\n");
	return 0; 
}
