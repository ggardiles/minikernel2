#
# boot/Makefile
#       Makefile para el boot
#

CC=gcc
CFLAGS= -g -Wall

all:
	@ln -sf boot_`getconf LONG_BIT` boot

boot: boot.o 
	$(CC) -o $@ boot.o -ldl

clean:
	rm -f boot.o boot
