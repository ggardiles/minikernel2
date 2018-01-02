/*
 *  minikernel/kernel/include/llamsis.h
 *
 *  Minikernel. Versi�n 1.0
 *
 *  Fernando P�rez Costoya
 *
 */

/*
 *
 * Fichero de cabecera que contiene el numero asociado a cada llamada
 *
 * 	SE DEBE MODIFICAR PARA INCLUIR NUEVAS LLAMADAS
 *
 */

#ifndef _LLAMSIS_H
#define _LLAMSIS_H

/* Numero de llamadas disponibles */
#define NSERVICIOS 12

#define CREAR_PROCESO 0
#define TERMINAR_PROCESO 1
#define ESCRIBIR 2
#define OBTENER_ID_PR 3 // Ejercicio 1
#define DORMIR 4
#define TIEMPOS_PROCESO 5
#define LEER_CARACTER 6
#define CREAR_MUTEX 7
#define ABRIR_MUTEX 8
#define CERRAR_MUTEX 9
#define LOCK 10
#define UNLOCK 11

#endif /* _LLAMSIS_H */

