#include "utils.h"
#include <math.h>


double distance(Coordonnees c, int s1, int s2){
	struct coord *s1Coord = c->clist[s1];
	struct coord *s2Coord = c->clist[s2];
	return sqrt(pow(s1Coord->coordx - s2Coord->coordx, 2) + pow(s1Coord->coordy - s2Coord->coordy, 2));
}