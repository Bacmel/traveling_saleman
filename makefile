projet : projet.o tas.o graph.o prim.o
	gcc projet.o tas.o graph.o prim.o -o projet -lm

projet.o : projet.c tas.h
	gcc -c projet.c

tas.o : tas.c tas.h
	gcc -c tas.c

graph.o : graph.c graph.h
	gcc -c graph.c

prim.o : prim.c prim.h
	gcc -c prim.c

clean :
rm -f *.o
