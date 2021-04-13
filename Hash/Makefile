CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: corretor

corretor: corretor_main.c
	gcc $(CFLAGS) -c corretor.c $(LDFLAGS)
	gcc $(CFLAGS) -c corretor_main.c $(LDFLAGS)
	gcc $(CFLAGS) -o corretor corretor_main.o corretor.o $(LDFLAGS)

clean:
	rm -f corretor
