all: q3 

q3: q3.o bankersAlgo.o check.o io.o
	gcc -o q3 $^ 

%.o: %.c q3.h
	gcc -c $< 

clean:
	rm -f q3 *.o 