#!/bin/sh

rm -f ./minikernel.2016.tar.gz
tar -cvzf minikernel.2016.tar.gz minikernel/kernel.c minikernel/include/llamsis.h minikernel/include/kernel.h usuario/include/servicios.h usuario/lib/serv.c autores memoria.txt entregar.sh
rsync -avz minikernel.2016.tar.gz decompress.sh y16a042@triqui4.fi.upm.es:/homefi/alumnos/y/y16a042/DATSI/SOA/minikernel.2016
