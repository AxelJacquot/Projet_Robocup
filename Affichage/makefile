all: affichage

affichage: control.o calcul.o serial.o
gcc -o affichage control.o calcul.o serial.o

control.o: controller.c calcul.h serial.h
gcc -o control.o -c controller.c -W -Wall -ansi -pedantic

calcul.o: calcul.c
gcc -o calcul.o -c calcul.c -W -Wall -ansi -pedantic

serial.o: serial.c
gcc -o serial.o -c serial.c -W -Wall -ansi -pedantic

clean:
rm -rf *.o


