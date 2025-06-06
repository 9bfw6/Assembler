project1:	main.o symbols.o  directives.o instructions.o fileHandler.o headers.h
	gcc -o project2 -Wall  -O0 main.o symbols.o directives.o instructions.o fileHandler.o

main.o:	main.c headers.h
	gcc -c -Wall  -O0 main.c

symbols.o:	symbols.c headers.h
	gcc -c -Wall  -O0 symbols.c

directives.o:	directives.c headers.h
	gcc -c -Wall  -O0 directives.c

instructions.o: instructions.c headers.h
	gcc -c -Wall -O0 instructions.c

fileHandler.o: fileHandler.c headers.h
	gcc -c -Wall -O0 fileHandler.c

clean:
	rm *.o -f
	touch *.c
	rm project2 -f
