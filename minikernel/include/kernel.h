/*
 *  minikernel/include/kernel.h
 *
 *  Minikernel. Versi�n 1.0
 *
 *  Fernando P�rez Costoya
 *
 */

/*
 *
 * Fichero de cabecera que contiene definiciones usadas por kernel.c
 *
 *      SE DEBE MODIFICAR PARA INCLUIR NUEVA FUNCIONALIDAD
 *
 */

#ifndef _KERNEL_H
#define _KERNEL_H

#include "const.h"
#include "HAL.h"
#include "llamsis.h"

/*
 *
 * Definicion del tipo que corresponde con el BCP.
 * Se va a modificar al incluir la funcionalidad pedida.
 *
 */
typedef struct BCP_t *BCPptr;

typedef struct BCP_t {
        int id;				/* ident. del proceso */
        int estado;			/* TERMINADO|LISTO|EJECUCION|BLOQUEADO*/
        contexto_t contexto_regs;	/* copia de regs. de UCP */
        void * pila;			/* dir. inicial de la pila */
		BCPptr siguiente;		/* puntero a otro BCP */
		void *info_mem;			/* descriptor del mapa de memoria */
		int nsecs_bloqueo;		/* segundos totales de bloqueo */
		int start_bloqueo;		/* momento en el que empezo el bloqueo */
		int int_sistema;		/* interrupciones en modo sistema */
 		int int_usuario;		/* interrupciones en modo usuario */
		int ticks_left_rr; 		/* ticks restantes slice round-robin */
		int is_bloq_lectura;/* bloqueado por lectura */
} BCP;

/*
 *
 * Definicion del tipo que corresponde con la cabecera de una lista
 * de BCPs. Este tipo se puede usar para diversas listas (procesos listos,
 * procesos bloqueados en sem�foro, etc.).
 *
 */
typedef struct{
	BCP *primero;
	BCP *ultimo;
} lista_BCPs;

/*
 * Definicion del tipo que corresponde con la contabilidad
 * del uso del procesador por parte de un proceso
 */
struct tiempos_ejec {
    int usuario;
    int sistema;
};

/*
 * Variable global que identifica el proceso actual
 */

BCP * p_proc_actual=NULL;

/*
 * Variable global que representa la tabla de procesos
 */

BCP tabla_procs[MAX_PROC];

/*
 * Variable global que representa la cola de procesos listos
 */
lista_BCPs lista_listos= {NULL, NULL};

/*
 * Variable global que representa la cola de procesos listos
 */
lista_BCPs lista_bloqueados= {NULL, NULL};
/*
 * Variable global que representa el número de llamadas a int_reloj
 */
 int num_ticks = 0;

 /*
  * Variable global que representa el acceso a memoria de usuario
  */
 int acceso_param = 0;

/* 
 * Variable global que representa el id del proceso bloqueado por int sw
 */
 int id_proc_int_sw = 0;

 /*
  * Variable global que indica el número de caracteres en el buffer
  */
 int size_char_buf = 0;

 /*
  * Buffer de caracteres procesados del terminal
  */
 char char_buf[TAM_BUF_TERM];
 


/*
 *
 * Definici�n del tipo que corresponde con una entrada en la tabla de
 * llamadas al sistema.
 *
 */
typedef struct{
	int (*fservicio)();
} servicio;


/*
 * Prototipos de las rutinas que realizan cada llamada al sistema
 */
int sis_crear_proceso();
int sis_terminar_proceso();
int sis_escribir();
int sis2_obtener_id_pr(); // Ejercicio 1
int sis2_dormir(); // Ejercicio 2
int sis2_tiempos_proceso(); // Ejercicio 3
int sis2_leer_caracter(); // Ejercicio 3
/*
 * Variable global que contiene las rutinas que realizan cada llamada
 */
servicio tabla_servicios[NSERVICIOS]={	
	{sis_crear_proceso},
	{sis_terminar_proceso},
	{sis_escribir},
	{sis2_obtener_id_pr},
	{sis2_dormir},
	{sis2_tiempos_proceso},
	{sis2_leer_caracter}
	};

#endif /* _KERNEL_H */


