#ifndef COMMANDE_H
#define COMMANDE_H
#include "Arborecensce.h"
#include "Parseur.h"

extern int cmdprint(noeud *actuel);

extern int ls(noeud *actuel);

extern int cdTerm(noeud **current);

extern int cdPath(noeud **current,char *path);

extern int cdPere(noeud **current);

extern void cmdPwd(noeud *current);

extern int mkdir(noeud* courant,char* nom);

extern int touch(noeud* courant,char* nom);

extern int cp(char* path1,char* path2,noeud *curr);

extern int cmdMv(char* path1,char* path2,noeud* curr);

extern int cmdRm(noeud *current, char *path);

#endif