CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: caminho

caminho: caminho_main.c
	gcc $(CFLAGS) -c caminho_funcoes.c $(LDFLAGS)
	gcc $(CFLAGS) -c caminho_main.c $(LDFLAGS)
	gcc $(CFLAGS) -o caminho caminho_main.o caminho_funcoes.o $(LDFLAGS)

clean:
	rm -f caminho
	rm -f *.o
