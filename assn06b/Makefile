CC = gcc
CFLAGS = -Wall -g

all: prob1.o prob2.o

prob1.o: callback_ps.c
	$(CC) $(CFLAGS) -o prob1.o callback_ps.c

prob2.o: hash_ps.c
	$(CC) $(CFLAGS) -o prob2.o hash_ps.c

clean:
	rm -f *.o
