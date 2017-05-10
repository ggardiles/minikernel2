/*
 *  kernel/kernel.c
 *
 *  Minikernel. Versi�n 1.0
 *
 *  Fernando P�rez Costoya
 *
 */

/*
 *
 * Fichero que contiene la funcionalidad del sistema operativo
 *
 */

#include "kernel.h"	/* Contiene defs. usadas por este modulo */
#include <string.h>
/*
 *
 * Funciones relacionadas con la tabla de procesos:
 *	iniciar_tabla_proc buscar_BCP_libre
 *
 */


static int is_mutex_name_used(char *nombre){
	int i;
	//printk("NOMBRE: %s\n", nombre);
	for (i = 0; i < NUM_MUT; i++){
		mutex *mut = (mutex*) &(mutex_list[i]);
		/*if (strlen(mut->nombre)>0){
			printk("NOMBRE_LISTA=%s  ",mut->nombre);
			printk("CMP=%d\n",strcmp(mut->nombre, nombre));
		}*/
		
		if(strcmp(mut->nombre, nombre) == 0){
			return ERR_NAME_USED;
		}
	}
	return 0;
}

static int get_avail_mutex_des(int *mut){
	int i;
	for(i=0; i<NUM_MUT_PROC; i++){
		if (mut[i] == -1){
			return i;
		}
	}
	return -1;
}
/*
static void unblock_waiting_mutex(){
		// Unblock processes waiting for mutex
		BCP *proc_unblock = lista_bloqueados.primero;

		while(proc_unblock != NULL && proc_unblock->is_bloq_mutex == 1){
			
			proc_unblock->estado = LISTO;
			proc_unblock->is_bloq_mutex = 0;
			BCP *proc_next = proc_unblock->siguiente;

			int lvl_int = fijar_nivel_int(NIVEL_3);
			eliminar_elem(&lista_bloqueados, proc_unblock);
			insertar_ultimo(&lista_listos, proc_unblock);
			fijar_nivel_int(lvl_int);

			proc_unblock = proc_next;
			if(proc_unblock != NULL){
				proc_next = proc_unblock->siguiente;
			}
		}
}
*/
/*
 * Funci�n que inicia la tabla de procesos
 */
static void iniciar_tabla_proc(){
	int i;

	for (i=0; i<MAX_PROC; i++)
		tabla_procs[i].estado=NO_USADA;
}

/*
 * Funci�n que busca una entrada libre en la tabla de procesos
 */
static int buscar_BCP_libre(){
	int i;

	for (i=0; i<MAX_PROC; i++)
		if (tabla_procs[i].estado==NO_USADA)
			return i;
	return -1;
}

/*
 *
 * Funciones que facilitan el manejo de las listas de BCPs
 *	insertar_ultimo eliminar_primero eliminar_elem
 *
 * NOTA: PRIMERO SE DEBE LLAMAR A eliminar Y LUEGO A insertar
 */

/*
 * Inserta un BCP al final de la lista.
 */
static void insertar_ultimo(lista_BCPs *lista, BCP * proc){
	if (lista->primero==NULL)
		lista->primero= proc;
	else
		lista->ultimo->siguiente=proc;
	lista->ultimo= proc;
	proc->siguiente=NULL;
}

/*
 * Elimina el primer BCP de la lista.
 */
static void eliminar_primero(lista_BCPs *lista){

	if (lista->ultimo==lista->primero)
		lista->ultimo=NULL;
	lista->primero=lista->primero->siguiente;
}

/*
 * Elimina un determinado BCP de la lista.
 */
static void eliminar_elem(lista_BCPs *lista, BCP * proc){
	BCP *paux=lista->primero;

	if (paux==proc)
		eliminar_primero(lista);
	else {
		for ( ; ((paux) && (paux->siguiente!=proc));
			paux=paux->siguiente);
		if (paux) {
			if (lista->ultimo==paux->siguiente)
				lista->ultimo=paux;
			paux->siguiente=paux->siguiente->siguiente;
		}
	}
}

/*
 *
 * Funciones relacionadas con la planificacion
 *	espera_int planificador
 */

/*
 * Espera a que se produzca una interrupcion
 */
static void espera_int(){
	int nivel;

	//printk("-> NO HAY LISTOS. ESPERA INT\n");

	/* Baja al m�nimo el nivel de interrupci�n mientras espera */
	nivel=fijar_nivel_int(NIVEL_1);
	halt();
	fijar_nivel_int(nivel);
}

/*
 * Funci�n de planificacion que implementa un algoritmo FIFO.
 */
static BCP * planificador(){
	while (lista_listos.primero==NULL)
		espera_int();		/* No hay nada que hacer */

	// Assign slice to process
	BCP *proceso = lista_listos.primero;
 	proceso->ticks_left_rr = TICKS_POR_RODAJA;

	return lista_listos.primero;
}

/*
 *
 * Funcion auxiliar que termina proceso actual liberando sus recursos.
 * Usada por llamada terminar_proceso y por rutinas que tratan excepciones
 *
 */
static void liberar_proceso(){
	BCP * p_proc_anterior;
	printk("LIBERAR PROCESO\n");
	// Mutex
	int i;
	for (i = 0; i < NUM_MUT_PROC; i++){
		int mut_id = p_proc_actual->mutex_list_proc[i];
		if (mut_id == -1){
			continue;
		}
		
		mutex *mut_global = (mutex *) &(mutex_list[mut_id]);
		printk("MUT_ID: %d, ",mut_id);
		printk("NOMBRE: %s\n",mut_global->nombre);

		mut_global->procesos_count--;

		// Hay mas procesos con mutex -> pasar de eliminar este mutex
		if(mut_global->procesos_count > 0){
			printk("Liberar proceso: Hay mas procesos con mutex\n");
			continue;
		}

		/* Eliminar mutex */
		strcpy(mut_global->nombre,"");
		//mut_global = NULL;
		mutex_count--;

		// Unblock processes waiting for mutex
		BCP *proc_unblock = lista_bloqueados.primero;

		while(proc_unblock != NULL){
			BCP *proc_next = proc_unblock->siguiente;
			if(proc_unblock->is_bloq_mutex == 1){
				proc_unblock->estado = LISTO;
				proc_unblock->is_bloq_mutex = 0;
				
				int lvl_int = fijar_nivel_int(NIVEL_3);
				eliminar_elem(&lista_bloqueados, proc_unblock);
				insertar_ultimo(&lista_listos, proc_unblock);
				fijar_nivel_int(lvl_int);
				break;
			}

			proc_unblock = proc_next;
		}
		printk("FIN\n");
	}

	liberar_imagen(p_proc_actual->info_mem); /* liberar mapa */

	p_proc_actual->estado=TERMINADO;

	int lvl_int = fijar_nivel_int(NIVEL_3);
	eliminar_primero(&lista_listos); /* proc. fuera de listos */
	fijar_nivel_int(lvl_int);

	/* Realizar cambio de contexto */
	p_proc_anterior=p_proc_actual;
	p_proc_actual=planificador();

	printk("-> C.CONTEXTO POR FIN: de %d a %d\n",
			p_proc_anterior->id, p_proc_actual->id);

	liberar_pila(p_proc_anterior->pila);
	cambio_contexto(NULL, &(p_proc_actual->contexto_regs));
        return; /* no deber�a llegar aqui */
}

/*
 *
 * Funciones relacionadas con el tratamiento de interrupciones
 *	excepciones: exc_arit exc_mem
 *	interrupciones de reloj: int_reloj
 *	interrupciones del terminal: int_terminal
 *	llamadas al sistemas: llam_sis
 *	interrupciones SW: int_sw
 *
 */

/*
 * Tratamiento de excepciones aritmeticas
 */
static void exc_arit(){

	if (!viene_de_modo_usuario())
		panico("excepcion aritmetica cuando estaba dentro del kernel");


	printk("-> EXCEPCION ARITMETICA EN PROC %d\n", p_proc_actual->id);
	liberar_proceso();

        return; /* no deber�a llegar aqui */
}

/*
 * Tratamiento de excepciones en el acceso a memoria
 */
static void exc_mem(){
	if(acceso_param == 0){
		if (!viene_de_modo_usuario())
			panico("excepcion de memoria cuando estaba dentro del kernel");
	}

	printk("-> EXCEPCION DE MEMORIA EN PROC %d\n", p_proc_actual->id);
	liberar_proceso();

        return; /* no deber�a llegar aqui */
}

/*
 * Tratamiento de interrupciones de terminal
 */
static void int_terminal(){
	char car;

	car = leer_puerto(DIR_TERMINAL);
	printk("-> TRATANDO INT. DE TERMINAL %c\n", car);


	// Si sobrepasa el tamaño máximo del buffer de entrada -> no seguir
	if(size_char_buf >= TAM_BUF_TERM){
		return;
	}

	char_buf[size_char_buf] = car;
	size_char_buf++;	

	// liberar procesos bloqueados
	BCP *proc_bloq = lista_bloqueados.primero;

	int desbloqueado = 0;
	if (proc_bloq != NULL){
		// Si esta bloqueado por lectura
		if(proc_bloq->is_bloq_lectura == 1){
			// Desbloquear proceso
			desbloqueado = 1;
			proc_bloq->estado = LISTO;
			proc_bloq->is_bloq_lectura = 0;
			int lvl_int = fijar_nivel_int(NIVEL_3);
			eliminar_elem(&lista_bloqueados, proc_bloq);
			insertar_ultimo(&lista_listos, proc_bloq);
			fijar_nivel_int(lvl_int);
		}
	}
	
	while(desbloqueado == 0 && proc_bloq != lista_bloqueados.ultimo){
		proc_bloq = proc_bloq->siguiente;
		if(proc_bloq->is_bloq_lectura == 1){ // Podemos desbloquear este proceso bloqueado
			desbloqueado = 1;
			proc_bloq->estado = LISTO;
			proc_bloq->is_bloq_lectura = 0;
			int lvl_int = fijar_nivel_int(NIVEL_3);
			eliminar_elem(&lista_bloqueados, proc_bloq);
			insertar_ultimo(&lista_listos, proc_bloq);
			fijar_nivel_int(lvl_int);
		}
	}	
	
    return;
}

/*
 * Tratamiento de interrupciones de reloj
 */
static void int_reloj(){

	//printk("-> TRATANDO INT. DE RELOJ, tic: %d\n", num_ticks);
	
	BCP *proceso_listo = lista_listos.primero;
 	
 	// Rellenar contadores
 	if(proceso_listo != NULL){
 		if(viene_de_modo_usuario()){
 			p_proc_actual->int_usuario++;
		}
		else{
			p_proc_actual->int_sistema++;
		}

		// Ha terminado slice round robin?
		if(p_proc_actual->ticks_left_rr > 1){
			printk("Int. reloj tic=%d, Proceso(%d) remaining ticks %d\n",num_ticks, p_proc_actual->id, p_proc_actual->ticks_left_rr);	
			p_proc_actual->ticks_left_rr--;	// No ha terminado -> resto tiempo	
		}
		else{
			id_proc_int_sw = p_proc_actual->id;
			activar_int_SW(); // Ha terminado -> Interrupcion
		}
	}

	BCP *proceso_bloqueado = lista_bloqueados.primero;

	// Incrementa contador de llamadas a int_reloj
	num_ticks++;
	
	// Desbloquear siguiente bloqueado
	while(proceso_bloqueado != NULL){
		
		// Calcular tiempo de bloqueo
		int ticks_left = (proceso_bloqueado->nsecs_bloqueo * TICK) - (num_ticks - proceso_bloqueado->start_bloqueo);
		BCP *proc_next = proceso_bloqueado->siguiente;

		// Si han pasado los ticks necesarios -> Desbloquear
		if(ticks_left <= 0 &&
		proceso_bloqueado->is_bloq_lectura == 0 &&
		proceso_bloqueado->is_bloq_mutex == 0){
			
			// Proceso pasa a listo
			proceso_bloqueado->estado = LISTO;
			int lvl_int = fijar_nivel_int(NIVEL_3);
			eliminar_elem(&lista_bloqueados, proceso_bloqueado);
			insertar_ultimo(&lista_listos, proceso_bloqueado);
			fijar_nivel_int(lvl_int);
		}

		proceso_bloqueado = proc_next;
	}

	return;
}

/*
 * Tratamiento de llamadas al sistema
 */
static void tratar_llamsis(){
	int nserv, res;

	nserv=leer_registro(0);
	if (nserv<NSERVICIOS)
		res=(tabla_servicios[nserv].fservicio)();
	else
		res=-1;		/* servicio no existente */
	escribir_registro(0,res);
	return;
}

/*
 * Tratamiento de interrupciuones software
 */
static void int_sw(){

	printk("-> TRATANDO INT. SW\n");

	if(id_proc_int_sw != p_proc_actual->id){
		return;
	}

	BCP *proceso_listo = lista_listos.primero;

	// Situar proceso en ejecución al final de la cola de listos
	int lvl_int = fijar_nivel_int(NIVEL_3);
	eliminar_elem(&lista_listos, proceso_listo);
	insertar_ultimo(&lista_listos, proceso_listo);
	fijar_nivel_int(lvl_int);

	// Cambio de contexto por int sw -> planificacion round robin
	BCP *p_proc_bloq = p_proc_actual;
	p_proc_actual = planificador();
	cambio_contexto(&(p_proc_bloq->contexto_regs), &(p_proc_actual->contexto_regs));

	return;
}

/*
 *
 * Funcion auxiliar que crea un proceso reservando sus recursos.
 * Usada por llamada crear_proceso.
 *
 */
static int crear_tarea(char *prog){
	void * imagen, *pc_inicial;
	int error=0;
	int proc;
	BCP *p_proc;

	proc=buscar_BCP_libre();
	if (proc==-1)
		return -1;	/* no hay entrada libre */

	/* A rellenar el BCP ... */
	p_proc=&(tabla_procs[proc]);

	/* crea la imagen de memoria leyendo ejecutable */
	imagen=crear_imagen(prog, &pc_inicial);
	if (imagen)
	{
		p_proc->info_mem=imagen;
		p_proc->pila=crear_pila(TAM_PILA);
		fijar_contexto_ini(p_proc->info_mem, p_proc->pila, TAM_PILA,
			pc_inicial,
			&(p_proc->contexto_regs));
		p_proc->id=proc;
		p_proc->estado=LISTO;
		/* mutex initialization */
		int i;
		for (i=0; i<NUM_MUT_PROC;i++){
			p_proc->mutex_list_proc[i] = -1;
		}
		p_proc->mutex_proc_count = 0;

		/* lo inserta al final de cola de listos */
		int lvl_int = fijar_nivel_int(NIVEL_3);
		insertar_ultimo(&lista_listos, p_proc);
		fijar_nivel_int(lvl_int);

		error= 0;
	}
	else
		error= -1; /* fallo al crear imagen */

	return error;
}

/*
 *
 * Rutinas que llevan a cabo las llamadas al sistema
 *	sis_crear_proceso sis_escribir
 *
 */

/*
 * Tratamiento de llamada al sistema crear_proceso. Llama a la
 * funcion auxiliar crear_tarea sis_terminar_proceso
 */
int sis_crear_proceso(){
	char *prog;
	int res;

	printk("-> PROC %d: CREAR PROCESO\n", p_proc_actual->id);

	prog=(char *)leer_registro(1);

	res=crear_tarea(prog);

	return res;
}

/*
 * Tratamiento de llamada al sistema escribir. Llama simplemente a la
 * funcion de apoyo escribir_ker
 */
int sis_escribir()
{
	char *texto;
	unsigned int longi;

	texto=(char *)leer_registro(1);
	longi=(unsigned int)leer_registro(2);

	escribir_ker(texto, longi);
	return 0;
}

/*
 * Tratamiento de llamada al sistema terminar_proceso. Llama a la
 * funcion auxiliar liberar_proceso
 */
int sis_terminar_proceso(){

	printk("-> FIN PROCESO %d\n", p_proc_actual->id);

	liberar_proceso();

        return 0; /* no deber�a llegar aqui */
}

/*
 * EJERCICIO 1: Return ID Proceso
 */
int sis2_obtener_id_pr(){
	return p_proc_actual->id;
}

/*
 * EJERCICIO 2: Llamada dormir
 */
int sis2_dormir(){
	
	unsigned int nsecs;

	nsecs = (unsigned int) leer_registro(1);

	// Actualizar BCP a bloqueado
	p_proc_actual->estado = BLOQUEADO;
	p_proc_actual->nsecs_bloqueo = nsecs;
	p_proc_actual->start_bloqueo = num_ticks;

	// Fijar nivel de interrupción a 3
	int lvl_int = fijar_nivel_int(NIVEL_3);
	
	// Pasar proceso lista de listos -> bloqueados
	eliminar_elem(&lista_listos, p_proc_actual);
	insertar_ultimo(&lista_bloqueados, p_proc_actual);

	// Restaura nivel de interrupcion anterior
	fijar_nivel_int(lvl_int);

	// Cambio de contexto voluntario
	BCP *p_proc_dormido = p_proc_actual;
	p_proc_actual = planificador();
	cambio_contexto(&(p_proc_dormido->contexto_regs), &(p_proc_actual->contexto_regs));

	return 0;
}

/*
 * EJERCICIO 3: Llamada tiempos proceso
 */
int sis2_tiempos_proceso(){	 
 	struct tiempos_ejec *t_ejec;
 
 	// Recuperar argumento
 	t_ejec = (struct tiempos_ejec *)leer_registro(1);
 
 	if(t_ejec == NULL){
		 return num_ticks;
 	}
	
	int lvl_int = fijar_nivel_int(NIVEL_3);
	acceso_param = 1;
	fijar_nivel_int(lvl_int);

	// Guardar tiempos
	t_ejec->usuario = p_proc_actual->int_usuario;
	t_ejec->sistema = p_proc_actual->int_sistema;
 	return num_ticks;
  }		 




/*
 * Ejercicio 5
 */
int sis2_leer_caracter(){
	// Inhibir interrupciones <= nivel 2
	int lvl_int = fijar_nivel_int(NIVEL_2);

	// Bloqueo si vacio -> con loop en vez de condicion
	while(size_char_buf == 0){
		p_proc_actual->estado = BLOQUEADO;
		p_proc_actual->is_bloq_lectura = 1;
		int lvl_int = fijar_nivel_int(NIVEL_3);
		eliminar_elem(&lista_listos, p_proc_actual);
		insertar_ultimo(&lista_bloqueados, p_proc_actual);
		fijar_nivel_int(lvl_int);

		// Cambio de proceso actual con cambio de contexto
		BCP *proc_bloq = p_proc_actual;
		p_proc_actual = planificador();
		cambio_contexto(&(proc_bloq->contexto_regs), &(p_proc_actual->contexto_regs));
	}

	// Recuperar primer caracter
	char car = char_buf[0];

	// Reassign positions in buffer
	printk("Reassign positions in buffer, size = %d\n", size_char_buf);
	size_char_buf--;
	int i;
	for (i = 0; i < size_char_buf; i++){
		char_buf[i] = char_buf[i+1];
	}
	fijar_nivel_int(lvl_int);

	return car;
}


int sis2_crear_mutex(){
	char *nombre = (char *)leer_registro(1);
	int tipo = (int)leer_registro(2);

	printk("CREAR MUTEX: nombre: %s, tipo: %d\n",nombre,tipo);
	if(p_proc_actual->mutex_proc_count >= NUM_MUT_PROC){
		printk("ERR: ERR_MUT_PROC_COUNT\n");
		return ERR_MUT_PROC_COUNT;
	}
	if(strlen(nombre) > MAX_NOM_MUT){
		printk("ERR: ERR_NAME_LENGTH\n");
		return ERR_NAME_LENGTH;
	}	
	if(is_mutex_name_used(nombre)<0){
		printk("ERR: ERR_NAME_USED\n");
		return ERR_NAME_USED;
	}
	// Si alcanzado maximo mutex -> bloquear
	while(mutex_count >= NUM_MUT){
		printk("ALCANZADO NUM_MUT\n");
		// Bloquear proceso actual
		p_proc_actual->estado = BLOQUEADO;
		p_proc_actual->is_bloq_mutex = 1;
		int lvl_int = fijar_nivel_int(NIVEL_3);
		eliminar_elem(&lista_listos, p_proc_actual);
		insertar_ultimo(&lista_bloqueados, p_proc_actual);
		fijar_nivel_int(lvl_int);

		// CCV
		BCP *proceso_bloqueado = p_proc_actual;
		p_proc_actual = planificador();
		printk("OLD proc: %d, Nuevo proc: %d\n", proceso_bloqueado->id, p_proc_actual->id);
		cambio_contexto(&(proceso_bloqueado->contexto_regs), &(p_proc_actual->contexto_regs));	

		// Al volver, comprobar nombre no usado
		if(is_mutex_name_used(nombre)<0){
			return ERR_NAME_USED;
		}
	}

	// Crear mutex si hay hueco
	int mut_idx, i;
	for (i = 0; i < NUM_MUT; i++){
		mutex *new_mut =(mutex *) &(mutex_list[i]);
		if(strlen(new_mut->nombre)==0){

			strcpy(new_mut->nombre, nombre);
			new_mut->tipo = tipo;
			new_mut->procesos_count++;
			mut_idx = i;
			break;
		}
	}

	// Incrementar contador global de mutex
	mutex_count += 1;
	
	// Asignar id del mutex a proceso actual y devolver posicion en array del proceso como descriptor
	int des = get_avail_mutex_des(p_proc_actual->mutex_list_proc);
	p_proc_actual->mutex_list_proc[des] = mut_idx;
	printk("Descriptor: %d\n",des);
	return p_proc_actual->mutex_proc_count++;
}

int sis2_abrir_mutex(){

	char *nombre = (char *)leer_registro(1);
	printk("ABRIR MUTEX: nombre: %s\n",nombre);
	
	// Comprueba número de mutex del proceso
	if(p_proc_actual->mutex_proc_count >= NUM_MUT_PROC){
		printk("ERR_MUT_PROC_COUNT\n");
		return ERR_MUT_PROC_COUNT;
	}

	int i, mut_idx = -2;
	// Buscar indice del mutex en lista global y añadir proceso actual como usuario
	for (i = 0; i < NUM_MUT; i++){
		mutex *mut =(mutex *) &(mutex_list[i]);
		if(strcmp(mut->nombre, nombre) == 0){
			mut->procesos_count++;
			mut_idx = i;
			printk("ENCONTRADO MUTEX: %s\n",mut->nombre);
			break;
		}
	}

	if(mut_idx < 0){
		printk("ERR_NAME_NOT_EXISTS\n");
		return ERR_NAME_NOT_EXISTS;
	}

	// Asignar id del mutex a proceso actual y devolver posicion en array del proceso como descriptor
	int des = get_avail_mutex_des(p_proc_actual->mutex_list_proc);
	p_proc_actual->mutex_list_proc[des] = mut_idx;
	printk("Descriptor: %d\n",des);
	return p_proc_actual->mutex_proc_count++;
}

int sis2_cerrar_mutex(){

	// Indice en la lista de mutex del proceso
	unsigned int mut_des = (unsigned int)leer_registro(1);
	printk("CERRAR MUTEX: descriptor: %d\n",mut_des);
	if((mut_des > NUM_MUT_PROC - 1) || p_proc_actual->mutex_list_proc[mut_des] == -1){
		return MUT_NOT_EXIST;
	}

	// Elimina mutex de proceso y de usado
	int mut_id = p_proc_actual->mutex_list_proc[mut_des];
	mutex *mut_global = (mutex *) &(mutex_list[mut_id]);

	// Eliminar contador
	mut_global->procesos_count--;

	// Delete mutex local
	p_proc_actual->mutex_proc_count--;
	p_proc_actual->mutex_list_proc[mut_des] = -1;

	// Si otros procesos usan el mutex, no eliminarlo
	if(mut_global->procesos_count > 0){
		printk("Otros procesos tienen abierto el mutex\n");
		return 0;
	}
	
	/* Nadie mas lo usa -> Cerrar el mutex */
	// Delete global mutex
	//mut_global = NULL;
	strcpy(mut_global->nombre, "");
	mutex_count--;

	//unblock_waiting_mutex();
	// Unblock processes waiting for mutex
	BCP *proc_unblock = lista_bloqueados.primero;


	while(proc_unblock != NULL){
		BCP *proc_next = proc_unblock->siguiente;
		if (proc_unblock->is_bloq_mutex == 1){
			proc_unblock->estado = LISTO;
			proc_unblock->is_bloq_mutex = 0;
			

			int lvl_int = fijar_nivel_int(NIVEL_3);
			eliminar_elem(&lista_bloqueados, proc_unblock);
			insertar_ultimo(&lista_listos, proc_unblock);
			fijar_nivel_int(lvl_int);

			break;
		}
		proc_unblock = proc_next;
	}

	return 0;
}

int sis2_lock(){
	return -1;
}

int sis2_unlock(){
	return -1;
}

/*
 *
 * Rutina de inicializaci�n invocada en arranque
 *
 */
int main(){
	/* se llega con las interrupciones prohibidas */

	instal_man_int(EXC_ARITM, exc_arit); 
	instal_man_int(EXC_MEM, exc_mem); 
	instal_man_int(INT_RELOJ, int_reloj); 
	instal_man_int(INT_TERMINAL, int_terminal); 
	instal_man_int(LLAM_SIS, tratar_llamsis); 
	instal_man_int(INT_SW, int_sw); 

	iniciar_cont_int();		/* inicia cont. interr. */
	iniciar_cont_reloj(TICK);	/* fija frecuencia del reloj */
	iniciar_cont_teclado();		/* inici cont. teclado */

	iniciar_tabla_proc();		/* inicia BCPs de tabla de procesos */

	/* crea proceso inicial */
	if (crear_tarea((void *)"init")<0)
		panico("no encontrado el proceso inicial");
	
	/* activa proceso inicial */
	p_proc_actual=planificador();
	cambio_contexto(NULL, &(p_proc_actual->contexto_regs));
	panico("S.O. reactivado inesperadamente");
	return 0;
}
