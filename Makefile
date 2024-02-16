CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS = -lm -lssl -lcrypto

all: server client

server: serverBreaker.c designServer.c
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

client: hashBreaker.c stringHash.c gil_design.c
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
 
