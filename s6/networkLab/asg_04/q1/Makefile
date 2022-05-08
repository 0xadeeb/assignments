##
# Makefile for socket program
#
# @file
# @version 0.1
shared = socket.h socket.c
all : server client

%.o : %.c $(shared)
	gcc -c $<

server : server.o
	gcc -o server server.o socket.c

client : client.o
	gcc -o client client.o socket.c

clean :
	rm -f server client *.o

# end
