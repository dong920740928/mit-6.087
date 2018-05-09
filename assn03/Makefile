CC = gcc
CFLAGS = -O0 -Wall
all: prob1.o wc.o

prob1.o: prob1.c
	$(CC) $(CFLAGS) prob1.c -o prob1.o

wc.o: wc.c
	$(CC) $(CFLAGS) wc.c -o wc.o

clean:
	rm -f *.o

