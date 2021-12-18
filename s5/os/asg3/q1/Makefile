shared = sharedMem.c sharedMem.h
all: p1 p2 p3 

%.o: %.c $(shared) 
	gcc -c $<

p1: p1.o 
	gcc -o p1 p1.o sharedMem.c

p2: p2.o 
	gcc -o p2 p2.o sharedMem.c

p3: p3.o 
	gcc -o p3 p3.o sharedMem.c

clean:
	rm -f *.o p1 p2 p3