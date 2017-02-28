WARNING_FLAGS = -Wall -Wextra -Werror -pedantic -Wformat\
				-fstrict-overflow -Wstrict-overflow=5\
				-Wshadow -Wpointer-arith -Wcast-qual -Wstrict-prototypes\
				-Wmissing-prototypes -Wcast-align -pedantic-errors
CFLAGS = -std=c99 -O3 $(WARNING_FLAGS)

LFLAGS = libisentlib.a -lGL -lglut -lGLU -lm fmodapi43206linux64/api/lib/libfmodex64.so -pthread

main: main.o moteur.o affichage.o libisentlib.a
	@echo "Edition de liens"
	gcc $(CFLAGS) main.o moteur.o affichage.o $(LFLAGS) -o main  $(CLIBS)
	@echo ""

main.o:	main.c moteur.h
	@echo "Compilation module du main"
	gcc $(CFLAGS) -c main.c
	@echo ""

moteur.o:	moteur.c moteur.h
	@echo "Compilation module moteur"
	gcc $(CFLAGS) -c moteur.c
	@echo ""

affichage.o: affichage.c affichage.h
	@echo "Compilation module affichage/graphique"
	gcc $(CFLAGS) -c affichage.c
	@echo ""

clean:
	rm -f main
	rm -f *.o
