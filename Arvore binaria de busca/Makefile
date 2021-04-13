CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: mensageiro

mensageiro: mensageiro_main.c
	gcc $(CFLAGS) -c mensageiro.c $(LDFLAGS)
	gcc $(CFLAGS) -c mensageiro_main.c $(LDFLAGS)
	gcc $(CFLAGS) -o mensageiro mensageiro_main.o mensageiro.o $(LDFLAGS)
clean:
	rm -f mensageiro
