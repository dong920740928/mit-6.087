CC = gcc
CFLAGS = -g -O0 -Wall

all : encode decode encode-large

encode: encode.c
	$(CC) $(CFLAGS) encode.c -o encode

decode: decode.c
	$(CC) $(CFLAGS) decode.c -o decode

encode-large: encode-large.c
	$(CC) $(CFLAGS) encode-large.c -o encode-large

clean:
	rm -f encode decode encode-large *.o
