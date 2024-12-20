

all: exec

exec: main.o tree.o

main.o: main.c settings.h
	gcc -c main.c -o main.o

tree.o: tree.c settings.h
	gcc -c tree.c -o tree.o
clean:
	rm -f *.o
	rm -f exec