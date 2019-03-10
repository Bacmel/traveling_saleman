#ifndef POID_PI_H
#define POID_PI_H

#include "graph.h"
#include "utils.h"

/**
 * Calcule le 'poid' de l'arête {s1,s2}
 *
 * Si 'pi' est à NULL alors le poid est la distance entre s1 et s2
 * @param distance_tab Matrice des distances entre les sommets du graphe
 * @param pi Tableau des poids de chaque sommet du graphe (peut être NULL)
 * @param s1 Sommet de l'arête
 * @param s2 Sommet de l'arête
 * @return le 'poid' de l'arête {s1, s2}
 */
double omega_pi(double **distance_tab, double pi[], Sommet s1, Sommet s2);

/**
 * Calcule le 'poid' du graphe
 *
 * Somme le poid de chaque arête du graphe
 * @param graphe Graphe dont on désir connaitre le poid
 * @param distance_tab Matrice des distances entre les sommets du graphe
 * @param pi Tableau des poids de chaque sommet du graphe
 * @return le 'poid' du graphe
 */
double omega_pi_graphe(Graphe graphe, double **distance_tab, double pi[]);

/**
 * Calcule le coefficient 't' à l'itération i
 *
 * @param graphe Graphe de l'itération i-1
 * @param distance_tab Matrice des distances entre les sommets du graphe
 * @param pi Tableau des poids de chaque sommet du graphe à l'itération i-1
 * @param lambda Coefficient multiplicateur à l'itération i-1
 * @param ub Longueur de la tournée optimale
 * @return le coefficient 't' à l'itération i
 */
double t(Graphe graphe, double **distance_tab, double pi[], double lambda, double ub);

/**
 * Calcule le 'poid' du sommet 's' à l'itération i
 *
 * @param sommet Sommet dont on souhaite connaitre le 'poid' à l'itération i
 * @param pi Tableau des poids de chaque sommet du graphe à l'itération i-1
 * @param graphe Graphe de l'itération i-1
 * @param t coefficient 't' à l'itération i
 * @return le 'poid' du sommet 's' à l'itération i
 */
double pi_s(Sommet sommet, double *pi, Graphe graphe, double t);

/**
 * Construit le tableau des poids pi pour chaque sommet du graphe à l'itération i
 *
 * @param pi Tableau des poids de chaque sommet du graphe à l'itération i-1
 * @param graphe Graphe de l'itération i-1
 * @param distance_tab Matrice des distances entre les sommets du graphe
 * @param lambda Coefficient multiplicateur à l'itération i-1
 * @param ub Longueur de la tournée optimale
 * @return le tableau des poids pi pour chaque sommet du graphe à l'itération i
 */
double *construire_nouv_pi(double pi[], Graphe graphe, double **distance_tab, double lambda, double ub);

/**
 * Construit le 1-arbre s'approchant au plus la tournée
 * @param coordonnees Coordonnées de chaque sommet faisant parti du graphe à constuire
 * @param ub Valeur de la tournée optimale
 * @return le 1-arbre s'approchant au plus la tournée
 */
Graphe borne_inferieur(Coordonnees coordonnees, double ub);

#endif //POID_PI_H
