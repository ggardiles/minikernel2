#
# usuario/Makefile
#	Makefile de programas de usuario
#
# NOTA: EN LA VERSIÓN INICIAL SÓLO COMPILARÁN CORRECTAMENTE LOS PROGRAMAS
# init, excep_arit, excep_mem y simplon, YA QUE LOS DEMÁS USAN LLAMADAS QUE
# NO TIENE QUE IMPLEMENTAR EL ALUMNO 
#


MAKEFLAGS=-k
INCLUDEDIR=include
LIBDIR=lib

BIBLIOTECA=$(LIBDIR)/libserv.a

CC=cc
CFLAGS=-Wall -fPIC -Werror -g -I$(INCLUDEDIR)

PROGRAMAS=init excep_arit excep_mem simplon prueba_dormir prueba_tiempos dormilon prueba_mutex1 creador1 creador2 creador3 creador4 abridor prueba_mutex2 mutex1 mutex2 prueba_RR1 yosoy prueba_RR2 mudo prueba_term lector

all: biblioteca $(PROGRAMAS)

biblioteca:
	cd lib; make

init.o: $(INCLUDEDIR)/servicios.h
init: init.o $(BIBLIOTECA)
	$(CC) -shared -o $@ init.o -L$(LIBDIR) -lserv

excep_arit.o: $(INCLUDEDIR)/servicios.h
excep_arit: excep_arit.o $(BIBLIOTECA)
	$(CC) -shared -o $@ excep_arit.o -L$(LIBDIR)  -lserv 

excep_mem.o: $(INCLUDEDIR)/servicios.h
excep_mem: excep_mem.o $(BIBLIOTECA)
	$(CC) -shared -o $@ excep_mem.o -L$(LIBDIR) -lserv 

simplon.o: $(INCLUDEDIR)/servicios.h
simplon: simplon.o $(BIBLIOTECA)
	$(CC) -shared -o $@ simplon.o -L$(LIBDIR) -lserv 

prueba_dormir.o: $(INCLUDEDIR)/servicios.h
prueba_dormir: prueba_dormir.o $(BIBLIOTECA)
	$(CC) $(LDFLAGS) -shared -o $@ prueba_dormir.o -L$(LIBDIR) -lserv

prueba_tiempos.o: $(INCLUDEDIR)/servicios.h
prueba_tiempos: prueba_tiempos.o $(BIBLIOTECA)
	$(CC) $(LDFLAGS) -shared -o $@ prueba_tiempos.o -L$(LIBDIR) -lserv

dormilon.o: $(INCLUDEDIR)/servicios.h
dormilon: dormilon.o $(BIBLIOTECA)
	$(CC) $(LDFLAGS) -shared -o $@ dormilon.o -L$(LIBDIR) -lserv

prueba_mutex1.o: $(INCLUDEDIR)/servicios.h
prueba_mutex1: prueba_mutex1.o $(BIBLIOTECA)
	$(CC) $(LDFLAGS) -shared -o $@ prueba_mutex1.o -L$(LIBDIR) -lserv

creador1.o: $(INCLUDEDIR)/servicios.h
creador1: creador1.o $(BIBLIOTECA)
	$(CC) $(LDFLAGS) -shared -o $@ creador1.o -L$(LIBDIR) -lserv

creador2.o: $(INCLUDEDIR)/servicios.h
creador2: creador2.o $(BIBLIOTECA)
	$(CC) $(LDFLAGS) -shared -o $@ creador2.o -L$(LIBDIR) -lserv

creador3.o: $(INCLUDEDIR)/servicios.h
creador3: creador3.o $(BIBLIOTECA)
	$(CC) $(LDFLAGS) -shared -o $@ creador3.o -L$(LIBDIR) -lserv

creador4.o: $(INCLUDEDIR)/servicios.h
creador4: creador4.o $(BIBLIOTECA)
	$(CC) $(LDFLAGS) -shared -o $@ creador4.o -L$(LIBDIR) -lserv

abridor.o: $(INCLUDEDIR)/servicios.h
abridor: abridor.o $(BIBLIOTECA)
	$(CC) $(LDFLAGS) -shared -o $@ abridor.o -L$(LIBDIR) -lserv

prueba_mutex2.o: $(INCLUDEDIR)/servicios.h
prueba_mutex2: prueba_mutex2.o $(BIBLIOTECA)
	$(CC) $(LDFLAGS) -shared -o $@ prueba_mutex2.o -L$(LIBDIR) -lserv

mutex1.o: $(INCLUDEDIR)/servicios.h
mutex1: mutex1.o $(BIBLIOTECA)
	$(CC) $(LDFLAGS) -shared -o $@ mutex1.o -L$(LIBDIR) -lserv

mutex2.o: $(INCLUDEDIR)/servicios.h
mutex2: mutex2.o $(BIBLIOTECA)
	$(CC) $(LDFLAGS) -shared -o $@ mutex2.o -L$(LIBDIR) -lserv

prueba_RR1.o: $(INCLUDEDIR)/servicios.h
prueba_RR1: prueba_RR1.o $(BIBLIOTECA)
	$(CC) $(LDFLAGS) -shared -o $@ prueba_RR1.o -L$(LIBDIR) -lserv

yosoy.o: $(INCLUDEDIR)/servicios.h
yosoy: yosoy.o $(BIBLIOTECA)
	$(CC) $(LDFLAGS) -shared -o $@ yosoy.o -L$(LIBDIR) -lserv

prueba_RR2.o: $(INCLUDEDIR)/servicios.h
prueba_RR2: prueba_RR2.o $(BIBLIOTECA)
	$(CC) $(LDFLAGS) -shared -o $@ prueba_RR2.o -L$(LIBDIR) -lserv

mudo.o: $(INCLUDEDIR)/servicios.h
mudo: mudo.o $(BIBLIOTECA)
	$(CC) $(LDFLAGS) -shared -o $@ mudo.o -L$(LIBDIR) -lserv

prueba_term.o: $(INCLUDEDIR)/servicios.h
prueba_term: prueba_term.o $(BIBLIOTECA)
	$(CC) $(LDFLAGS) -shared -o $@ prueba_term.o -L$(LIBDIR) -lserv

lector.o: $(INCLUDEDIR)/servicios.h
lector: lector.o $(BIBLIOTECA)
	$(CC) $(LDFLAGS) -shared -o $@ lector.o -L$(LIBDIR) -lserv

clean:
	rm -f *.o $(PROGRAMAS)
	cd lib; make clean

