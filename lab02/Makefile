CC = gcc
CFLAGS = -g -O0 -Wall

all : encode decode

encode: encode.c
	$(CC) $(CFLAGS) encode.c -o encode

decode: decode.c
	$(CC) $(CFLAGS) decode.c -o decode

clean:
	rm -f encode decode *.o
