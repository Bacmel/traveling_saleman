main : projet.o tas.o graph.o
	gcc projet.o graph.o tas.o -o main -lm

run: main
	./main berlin52
projet.o : projet.c tas.h graph.h
	gcc -c projet.c
	
graph.o : graph.c graph.h
	gcc -c graph.c

tas.o : graph.o tas.c tas.h
	gcc -c tas.c -lm

clean :
	rm -f *.o
