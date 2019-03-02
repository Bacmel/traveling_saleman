projet : projet.o tas.o graph.o prim.o utils.o poid_pi.o glouton.o union_find.o
	gcc projet.o tas.o graph.o prim.o utils.o poid_pi.o glouton.o union_find.o -o projet -lm

projet.o : projet.c tas.h graph.h prim.h utils.h poid_pi.h glouton.h union_find.h
	gcc -c projet.c

tas.o : tas.c tas.h graph.h
	gcc -c tas.c

graph.o : graph.c graph.h
	gcc -c graph.c

prim.o : prim.c prim.h graph.h tas.h utils.h
	gcc -c prim.c

utils.o : utils.c utils.h graph.h
	gcc -c utils.c

union_find.o : union_find.c union_find.h
	gcc -c union_find.c

poid_pi.o : poid_pi.c poid_pi.h graph.h
	gcc -c poid_pi.c

glouton.o : glouton.c glouton.h graph.c utils.h union_find.h
	gcc -c glouton.c

clean :
	rm -f *.o *.dat *.gnu
