main : projet.o tas.o graph.o
	gcc projet.o tas.o graph.o -o main -lm

projet.o : projet.c tas.h
	gcc -c projet.c

tas.o : tas.c tas.h
	gcc -c tas.c

graph.o : graph.c graph.h
	gcc -c graph.c

clean :
rm -f *.o
