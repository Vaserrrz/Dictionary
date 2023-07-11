all: diccionario main.o func.o

func.o: func.c
		gcc -c func.c
main.o: main.c
		gcc -c main.c
diccionario: main.o func.o
	gcc -o diccionario func.o main.o