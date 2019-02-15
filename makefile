projet : projet.o tas.o graph.o
	gcc projet.o tas.o graph.o -o projet -lm

run: projet
	./projet berlin52

projet.o : projet.c tas.h graph.h
	gcc -c projet.c

graph.o : graph.c graph.h
	gcc -c graph.c

tas.o : graph.o tas.c tas.h
	gcc -c tas.c -lm

graph.o : graph.c graph.h
	gcc -c graph.c

clean :
	rm -f *.o
