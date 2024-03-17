#include <assert.h>
#include <stdbool.h>

#include <stdlib.h>
#include <stdio.h>

#include <string.h>
#include "Arborecensce.h"

noeud *createNode (char *nom, noeud *p, noeud *racine, liste_noeud *fils){
  noeud *res = malloc(sizeof(noeud));
  assert (res != NULL);
  assert (racine != NULL);
  assert (strlen(nom)<100);
  strcpy(res -> nom, nom);
  res -> racine = racine;
  res ->est_dossier = fils != NULL;
  res -> fils = fils;
  res -> pere=p;
  return res;  
}

void createRacine (noeud **racine , liste_noeud *fils){
  assert (racine != NULL);
  (*racine) -> nom[0] = '\0';
  (*racine) -> racine = (*racine);
  (*racine) -> est_dossier = fils != NULL;
  (*racine) -> fils = fils;
  (*racine) -> pere = (*racine);
}

void libereEspace(noeud *node);

void suprimeNodeFromPere (noeud *pere, char *aSupprimer){
  //Supprime un liste_noeud d'une liste(verifie grace au nom);
  if (pere != NULL){
    if (pere -> fils != NULL){
      liste_noeud *curr = pere -> fils;
      if (curr -> succ == NULL){
        pere -> fils = NULL;
        if(curr->no!=NULL&&!strcmp(curr->no->nom,aSupprimer)){
          free(curr);
        }  
        return;
      }else if(curr ->no != NULL && !strcmp(curr -> no -> nom, aSupprimer)){
        pere -> fils = curr -> succ;
        free(curr);
        return;
      }else {
        while (curr -> succ != NULL){
          if (curr-> succ -> no != NULL && !strcmp(curr -> succ -> no -> nom, aSupprimer)){
            liste_noeud *aSuppr = curr -> succ;
            curr -> succ = aSuppr -> succ;
            free(aSuppr);
            return;
          }else {
            curr = curr -> succ;
          }
        }
      }
    }
  }
}

void libereEspace(noeud *node) {
  //Supprimer Noeud et tout ce qui le relie sauf sont lien avec -> pere
  if (node != NULL){
    if (node -> est_dossier){
      suprimerSons(node ->fils);
      node -> fils = NULL;
    }
    free(node);
  }
}

void suprimerSons (liste_noeud *liste_noeud){
  //But est de supprimer une liste de noeud
  if (liste_noeud != NULL){
    if (liste_noeud -> succ != NULL){
      suprimerSons(liste_noeud -> succ);
    }
    if (liste_noeud -> no != NULL){
      libereEspace(liste_noeud -> no);
    }
    free(liste_noeud);
  }
}

void moveFils(noeud *aDeplacer, noeud *nouveauPere){
  if (nouveauPere -> est_dossier){
    liste_noeud *frere =  NULL;
    if (nouveauPere -> fils != NULL){
      frere =  nouveauPere -> fils;
      //Ici on recupe le dernier de la liste des fils de l'endroit ou l'on dit placer
      while (frere -> succ != NULL){
        frere = frere -> succ;
      }
    }
    liste_noeud *listeAPlacer = malloc(sizeof(liste_noeud));
    listeAPlacer -> no = aDeplacer;
    listeAPlacer -> succ = NULL;
    if (frere != NULL){
      if (nouveauPere -> fils -> no == NULL){
        frere -> no = aDeplacer;
        free(listeAPlacer);
      } else {
        //On place
        frere -> succ = listeAPlacer;  
      }
      //On va chercher a supprimer le noeud d'ou il vient
      noeud *pere = aDeplacer -> pere ; 
      suprimeNodeFromPere(pere, aDeplacer -> nom);
    } else {
      nouveauPere -> fils = listeAPlacer;
    }  
    aDeplacer -> pere = nouveauPere;
  }
}


void addFils(liste_noeud* fils,noeud* n){
  assert(fils!=NULL);
  assert(n!=NULL);
  if(fils->no==NULL){
    fils->no=n;
    fils->succ=NULL;
    return;
  } 
  liste_noeud* nouveau=malloc(sizeof(liste_noeud));
  nouveau->no=n;
  nouveau->succ=NULL;
  liste_noeud* tmp=fils;
  while(tmp->succ!=NULL){
    tmp -> no = tmp->no;
    tmp=tmp->succ;
  }
  tmp->succ=nouveau;
 
}
