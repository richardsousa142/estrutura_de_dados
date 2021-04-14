CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: diadeuber

diadeuber: diadeuber_main.c
	gcc $(CFLAGS) -c diadeuber.c $(LDFLAGS)
	gcc $(CFLAGS) -c diadeuber_main.c $(LDFLAGS)
	gcc $(CFLAGS) -o diadeuber diadeuber_main.o diadeuber.o $(LDFLAGS)

clean:
	rm -f diadeuber
	rm -f *.o
