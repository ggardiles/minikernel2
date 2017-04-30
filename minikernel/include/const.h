/*
 *  minikernel/include/const.h
 *
 *  Minikernel. Versión 1.0
 *
 *  Fernando Pérez Costoya
 *
 */

/*
 *
 * Fichero de cabecera que contiene definiciones de constantes
 *
 *	NO SE DEBE MODIFICAR
 *
 */

#ifndef _CONST_H
#define _CONST_H

#ifndef NULL
#define NULL (void *) 0		/* por si acaso no esta ya definida */
#endif

#define MAX_PROC 10		/* dimension de tabla de procesos */

#define TAM_PILA 32768


/*
 * Posibles estados del proceso
 */
#define NO_USADA 0		/* Entrada de tabla de procs. no usada */
#define TERMINADO 0		/* Proc. TERMINADO == entrada NO_USADA */
#define LISTO 1
#define EJECUCION 2
#define BLOQUEADO 3

/*
 * Niveles de ejecución del procesador. 
 */
#define NUM_NIVELES 3
#define NIVEL_1 1 /* Int. SW */
#define NIVEL_2 2 /* Int. Terminal */
#define NIVEL_3 3 /* Int. Reloj */

/*
 *
 *  Definicion de constantes relacionadas con vectores de interrupcion
 *
 */

/* Numero de vectores de interrupcion disponibles */
#define NVECTORES 6

/* Numeros de vector */
#define EXC_ARITM 0     /* excepcion aritmetica */
#define EXC_MEM 1       /* excepcion en acceso a memoria */
#define INT_RELOJ 2     /* interrupcion de reloj */
#define INT_TERMINAL 3  /* interrupcion de entrada de terminal */
#define LLAM_SIS 4      /* vector usado para llamadas */
#define INT_SW 5	/* vector usado para interrupciones software */

/* frecuencia de reloj requerida (ticks/segundo) */
#define TICK 100

/* constante usada en implementacion de round robin */
#define TICKS_POR_RODAJA 10

/* constantes usada en implementacion de mutex */
#define NUM_MUT 16 /* numero total de mutex en el sistema */
#define NUM_MUT_PROC 4 /* numero maximo de mutex que puede tener
			  abiertos un proceso */
#define MAX_NOM_MUT 8 /* longitud maxima de un nombre de mutex */

/* constante usada en implementacion de manejador de terminal */
#define TAM_BUF_TERM 8 /* tamaño del buffer del terminal */

/* dirección de puerto de E/S del terminal */
#define DIR_TERMINAL 1

#endif /* _CONST_H */

