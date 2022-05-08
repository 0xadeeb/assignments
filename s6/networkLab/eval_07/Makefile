##
# Assignment 7 make file
#
# @file
# @version 0.1
shared = socket.c socket.h

all: sserver pserver client

%.o: %.c $(shared)
	gcc -c $<

sserver: smtpserver.o
	gcc -pthread -o sserver smtpserver.o socket.c

pserver: popServer.o
	gcc -pthread -o pserver popServer.o socket.c

client: client.o
	gcc -o client client.o socket.c

clean:
	rm *.o sserver pserver client

# end
