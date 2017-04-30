#
# minikernel/Makefile
#	Makefile del sistema 
#

INCLUDEDIR=include
CC=gcc
CFLAGS=-g -Wall -fPIC -I$(INCLUDEDIR)

all: version kernel

version:
	@ln -sf HAL.o_`getconf LONG_BIT` HAL.o


OBJS_KER=kernel.o HAL.o 
BIB_KER=-ldl

kernel.o: $(INCLUDEDIR)/kernel.h $(INCLUDEDIR)/HAL.h $(INCLUDEDIR)/const.h $(INCLUDEDIR)/llamsis.h

HAL.o: $(INCLUDEDIR)/HAL.h $(INCLUDEDIR)/const.h

kernel: $(OBJS_KER)
	$(CC) -shared -o $@ $(OBJS_KER) $(BIB_KER)

clean:
	rm -f kernel.o kernel HAL.o
