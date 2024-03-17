#ifndef PARSEUR_H
#define PARSEUR_H

#include "Commande.h"
#include "Arborecensce.h"

extern int analyseCommandLine(const char* line, noeud **courant);

extern int analyseChemin(const char* path, noeud* depart);

extern bool searchListe(noeud *depart, char *curr, noeud *courant);

extern void analyseFic(const char *pathToFile, noeud **courant);

extern void error(int error);

extern noeud *lectureChemin(char *path, noeud *current);

extern noeud *lectureCheminToCreate(char *path, noeud *current, char *newName);

#endif