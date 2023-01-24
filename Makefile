CC=gcc
CFLAGS=-I.

client: client.c helpers.c buffer.c parson.c requests.c
	$(CC) -o client client.c buffer.c helpers.c parson.c requests.c -Wall -Wextra

run: client
	./client

clean:
	rm -f *.o client
