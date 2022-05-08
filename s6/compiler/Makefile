all: lex.yy.c parser.tab.c compiler.c compiler.h linker
	gcc -o check lex.yy.c parser.tab.c compiler.c
	./check $(ARGV)
	./linker

lex.yy.c: lexser.l parser.tab.c
	flex lexser.l

parser.tab.c: parser.y
	bison -d parser.y

linker.c: linker.l
	flex -o linker.c linker.l

linker: linker.c
	gcc -o linker linker.c

clean:
	rm check linker lex.yy.c parser.tab.* linker.c *.xsm *.obj

del:
	trash-put check linker lex.yy.c parser.tab.* linker.c *.xsm *.obj
