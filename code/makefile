CFLAGS = -Wall
CLIBS = -lglut -lGL -lGLU  -lm -lX11


main: main.o moteur.o affichage.o
	gcc $(CFLAGS) main.o moteur.o affichage.o -o main  $(CLIBS)

main.o:	main.c moteur.h
	gcc $(CFLAGS) -c main.c

moteur.o:	moteur.c moteur.h
	gcc $(CFLAGS) -c moteur.c

affichage.o: affichage.c affichage.h
	gcc $(CFLAGS) -c affichage.c

clean:
	rm -f main
	rm -f *.o
