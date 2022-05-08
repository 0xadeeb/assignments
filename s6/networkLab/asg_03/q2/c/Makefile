##
# Makefile for socket program
#
# @file
# @version 0.1

all : server client

%.o : %.c socket.h
	gcc -c $<

server : server.o
	gcc -o server server.o socket.h

client : client.o
	gcc -o client client.o socket.h

clean :
	rm -f server client *.o

# end
