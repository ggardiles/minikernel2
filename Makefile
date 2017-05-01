#
# Makefile
# 	Makefile global del sistema
#
all: arranque sistema programas

arranque:
	@cd boot; make

sistema:
	cd minikernel; make

programas:
	cd usuario; make

clean:
	@cd boot; make clean
	cd minikernel; make clean
	cd usuario; make clean
