#ifndef ARBORECNESCE_H
#define ARBORECNESCE_H
//A reflechir dans quelle sens imbriquer les choses
// struct noeud ;

#include <assert.h>
#include <stdbool.h>

#include <stdlib.h>
#include <stdio.h>

#include <string.h>

struct liste_noeud ;

struct noeud {
  bool est_dossier ;
  char nom [100];
  struct noeud * pere ;
  struct noeud * racine ;
  struct liste_noeud * fils ;
};

struct liste_noeud {
  struct noeud * no ;
  struct liste_noeud * succ ;
};

typedef struct noeud noeud ;

typedef struct liste_noeud liste_noeud ;

extern noeud *createNode (char *nom, noeud *p, noeud *racine, liste_noeud *fils);

extern void createRacine (noeud **racine, liste_noeud *fils);

extern void libereEspace(noeud *node);

extern void moveFils(noeud *aDeplacer, noeud *nouveauPere);

extern void suprimeNodeFromPere (noeud *depart, char *aSupprimer);

extern void suprimerSons (liste_noeud *liste_noeud);

extern void addFils(liste_noeud* fils,noeud* n);

#endif