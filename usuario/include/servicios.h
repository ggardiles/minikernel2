/*
 *  usuario/include/servicios.h
 *
 *  Minikernel. Versi�n 1.0
 *
 *  Fernando P�rez Costoya
 *
 */

/*
 *
 * Fichero de cabecera que contiene los prototipos de funciones de
 * biblioteca que proporcionan la interfaz de llamadas al sistema.
 *
 *      SE DEBE MODIFICAR AL INCLUIR NUEVAS LLAMADAS
 *
 */


/*
 * Definicion del tipo que corresponde con la contabilidad
 * del uso del procesador por parte de un proceso
 */
struct tiempos_ejec {
    int usuario;
    int sistema;
};

#ifndef SERVICIOS_H
#define SERVICIOS_H

/* Evita el uso del printf de la bilioteca est�ndar */
#define printf escribirf

/* Funcion de biblioteca */
int escribirf(const char *formato, ...);

/* Llamadas al sistema proporcionadas */
int crear_proceso(char *prog);
int terminar_proceso();
int escribir(char *texto, unsigned int longi);
int obtener_id_pr(); //Ejercicio 1
int dormir(unsigned int segundos); // Ejercicio 2 
int tiempos_proceso(struct tiempos_ejec *t_ejec); // Ejercicio 3
int leer_caracter(); // Ejercicio 5

#endif /* SERVICIOS_H */
