/*
 * usuario/prueba_tiempos.c
 *
 *  Minikernel. Versión 1.0
 *
 *  Fernando Pérez Costoya
 *
 */

/*
 * Programa de usuario que realiza una prueba de la llamada tiempos_proceso
 */

#include "servicios.h"

#define TOT_ITER_FASE1 50000   /* ponga las que considere oportuno */
#define TOT_ITER_FASE2 20000000      /* ponga las que considere oportuno */

static void imp_tiempos(int real, int usuario, int sistema) {
	printf("Ticks: Real %d Usuario %d Sistema %d\n",
		real, usuario, sistema);
}

int main(){

        int i, tot, j=5;
	struct tiempos_ejec tiempos_f1, tiempos_f2, tiempos_f3;
	int t0, t1, t2, t3;

	printf("prueba_tiempos: comienza\n");
	t0=tiempos_proceso(0);

	printf("PRIMERA FASE: HACE LLAMADAS AL SISTEMA\n");
	
        for (i=0; i<TOT_ITER_FASE1; i++)
                printf("prueba_tiempos: i %d\n", i);

	printf("FIN PRIMERA FASE\n");
	t1=tiempos_proceso(&tiempos_f1);
	imp_tiempos(t1-t0, tiempos_f1.usuario, tiempos_f1.sistema);

	printf("SEGUNDA FASE: TODO CPU\n");

        for (i=0; i<TOT_ITER_FASE2; i++)
                tot=j*i;

	printf("FIN SEGUNDA FASE\n");
	t2=tiempos_proceso(&tiempos_f2);
	imp_tiempos(t2-t1, tiempos_f2.usuario-tiempos_f1.usuario,
		tiempos_f2.sistema-tiempos_f1.sistema);


	printf("TERCERA FASE: DORMIDO\n");

	dormir(1);

	printf("FIN TERCERA FASE\n");
	t3=tiempos_proceso(&tiempos_f3);
	imp_tiempos(t3-t2, tiempos_f3.usuario-tiempos_f2.usuario,
		tiempos_f3.sistema-tiempos_f2.sistema);


	printf("PASANDO ARGUMENTO ERRONEO\n");

	/* Debe sobrevivir después de abortar el proceso */ 
	if (crear_proceso("simplon")<0)
		printf("Error creando simplon\n");

	tiempos_proceso((struct tiempos_ejec *) main);
        tot--;
        t0--;

	printf("prueba_tiempos: termina. NO DEBE SALIR\n");
	return 0; 
}
