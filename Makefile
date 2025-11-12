CFLAGS=-Wall -Werror -std=c99 -pedantic -g
LFLAGS=-lm

all: 20252_ej3

20252_ej3: main.o sprite.o sprites.o
	gcc $(CFLAGS) main.o sprite.o sprites.o -o 20252_ej3 $(LFLAGS)

main.o: main.c sprite.h sprites.h 
	gcc $(CFLAGS) -c main.c

sprite.o: sprite.c sprite.h
	gcc $(CFLAGS) -c sprite.c

sprites.o: sprites.c sprites.h
	gcc $(CFLAGS) -c sprites.c

valgrind: 20252_ej3
	valgrind --leak-check=full --track-origins=yes ./20252_ej3 20252_ej3.bin kuchipatchi

clean:
	rm *.o 20252_ej3