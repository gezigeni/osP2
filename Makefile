output: logParse.o
	gcc logParse.c -o logParse
lopParse.o: logParse.c
	gcc -c logParse.c
clean: 
	rm *.o logParse

