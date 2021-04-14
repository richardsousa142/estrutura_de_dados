CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: listas_legais

listas_legais: listas_legais_main.c
	gcc $(CFLAGS) -c listas_legais.c $(LDFLAGS)
	gcc $(CFLAGS) -c listas_legais_main.c $(LDFLAGS)
	gcc $(CFLAGS) -o listas_legais listas_legais_main.o listas_legais.o $(LDFLAGS)

clean:
	rm -f listas_legais
	rm -f *.o
