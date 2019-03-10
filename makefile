projet : projet.o tas.o graph.o prim.o utils.o poid_pi.o glouton.o union_find.o 1arbre.o
	gcc projet.o tas.o graph.o prim.o utils.o poid_pi.o glouton.o union_find.o 1arbre.o -o projet -lm

projet.o : projet.c tas.h graph.h prim.h utils.h poid_pi.h glouton.h union_find.h
	gcc -c projet.c

tas.o : tas.c tas.h graph.h poid_pi.h
	gcc -c tas.c

graph.o : graph.c graph.h poid_pi.h
	gcc -c graph.c

prim.o : prim.c prim.h graph.h tas.h utils.h poid_pi.h
	gcc -c prim.c

utils.o : utils.c utils.h graph.h poid_pi.h
	gcc -c utils.c

union_find.o : union_find.c union_find.h poid_pi.h
	gcc -c union_find.c

poid_pi.o : poid_pi.c poid_pi.h graph.h
	gcc -c poid_pi.c

glouton.o : glouton.c glouton.h graph.c utils.h union_find.h poid_pi.h
	gcc -c glouton.c

1arbre.o : 1arbre.c 1arbre.h graph.c prim.h poid_pi.h
	gcc -c 1arbre.c

clean :
	rm -f *.o *.dat *.gnu
