main : projet.o tas.o
	gcc projet.o tas.o -o main -lm

projet.o : projet.c tas.h
	gcc -c projet.c

tas.o : tas.c tas.h
	gcc -c tas.c

clean :
	rm -f *.o
