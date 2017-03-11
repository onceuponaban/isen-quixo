WARNING_FLAGS = -Wall -Wextra -Werror -pedantic -Wformat\
				-fstrict-overflow -Wstrict-overflow=5\
				-Wshadow -Wpointer-arith -Wcast-qual -Wstrict-prototypes\
				-Wmissing-prototypes -Wcast-align -pedantic-errors
CFLAGS = -std=c99 -O3 $(WARNING_FLAGS)

LFLAGS = libisentlib.a -lX11 -lGL -lglut -lGLU -lm -pthread

main: main.o moteur.o affichage.o libisentlib.a
	@echo "Edition de liens :"
	gcc main.o moteur.o affichage.o -o main $(LFLAGS)
	@echo ""

main.o: main.c GfxLib.h BmpLib.h ESLib.h moteur.h affichage.h
	@echo "Compilation module main :"
	gcc $(CFLAGS) -c main.c
	@echo ""

moteur.o: moteur.c moteur.h
	@echo "Compilation module moteur :"
	gcc $(CFLAGS) -c moteur.c
	@echo ""

affichage.o: affichage.c affichage.h
	@echo "Compilation module affichage/graphique :"
	gcc $(CFLAGS) -c affichage.c
	@echo ""

libisentlib.a: BmpLib.o ESLib.o GfxLib.o ErreurLib.o OutilsLib.o
	@echo "MAJ libisentlib.a :"
	ar r libisentlib.a BmpLib.o ESLib.o GfxLib.o ErreurLib.o OutilsLib.o
	ranlib libisentlib.a
	@echo ""

BmpLib.o: BmpLib.c BmpLib.h OutilsLib.h
	@echo "Compilation module BmpLib :"
	gcc -Wall -O2 -c BmpLib.c
	@echo ""

ESLib.o: ESLib.c ESLib.h ErreurLib.h
	@echo "Compilation module ESLib :"
	gcc -Wall -O2 -c ESLib.c
	@echo ""

GfxLib.o: GfxLib.c GfxLib.h ESLib.h
	@echo "Compilation module GfxLib :"
	gcc -Wall -O2 -c GfxLib.c -I/usr/include/GL
	@echo ""

OutilsLib.o: OutilsLib.c OutilsLib.h
	@echo "Compilation module OutilsLib :"
	gcc -Wall -O2 -c OutilsLib.c
	@echo ""

ErreurLib.o: ErreurLib.c ErreurLib.h
	@echo "Compilation module ErreurLib :"
	gcc -Wall -O2 -c ErreurLib.c
	@echo ""

clean:
	rm -f *~ *.o

deepclean: clean
	rm -f main libisentlib.a
