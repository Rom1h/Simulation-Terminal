#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Parseur.h"

int analyseCommandLine (const char* line, noeud **courant){
  printf("analyse %s \n",line);
  char *tmp = malloc ((strlen(line)+1)* sizeof(char));
  strcpy(tmp, line);
  char *commande = strtok(tmp , " ");
  if(!strcmp(commande,"ls\n")){
      free(tmp);
      return ls(*courant);
  } else if(!strcmp(commande,"cd")){
    char *chemain = strtok(NULL , "\n");
    if(!strcmp(chemain,"..")){
      free(tmp);
      return cdPere(courant);
    }
    int pathValide=analyseChemin(chemain,*courant);
    if(chemain==NULL || !strcmp(chemain,"\n") || !strcmp(chemain," ")){

      free(tmp);
      return cdTerm(courant);

    }else{
      if(pathValide==1){
        int res =cdPath(courant,chemain);
        free(tmp);
        return res;

      }
      free(tmp);
      return pathValide;
    }
  }else if(!strcmp(commande,"cd\n")){
      free(tmp);
      return cdTerm(courant);
  } else if (!strcmp(commande,"mkdir")){
    char *chemain = strtok(NULL , "\n");
    assert(chemain!=NULL);
    int res=mkdir(*courant, chemain);
  
    free(tmp);
    return res;
  } else if (!strcmp(commande,"pwd\n")){
      cmdPwd(*courant);
      free(tmp);
      return 1;
  } else if (!strcmp(commande,"rm")){
    char *chemain = strtok(NULL , "\n");
    int res = cmdRm(*courant, chemain);
    free(tmp);
    return res;
  } else if (!strcmp(commande,"touch")){
      char *chemain = strtok(NULL , "\n");
      int res = touch(*courant, chemain);
      free(tmp);
      return res;
  } else if (!strcmp(commande,"print\n")){
      free(tmp);
      return cmdprint(*courant);
  } else {
    char *chemain = strtok(NULL , " ");
    char *chemain2 = strtok(NULL , "\n");
    if(!strcmp(commande,"ls")||!strcmp(commande,"pwd")||!strcmp(commande,"print")){
      free(tmp);
      return -5;
    } else if (!strcmp(commande,"cp")){
      int res = cp(chemain, chemain2, *courant);
      free(tmp);
      return res;
    }else if(!strcmp(commande,"mv")){
      int res = cmdMv(chemain, chemain2, *courant);
      free(tmp);
      return res;
    } else {
      free(tmp);
      return -4;
    }
  }
  free(tmp);
  return 1;
}

int analyseChemin(const char* path, noeud* depart){
  assert(path!=NULL);
  char *tmp = malloc ((strlen(path)+1)* sizeof(char));
  
  strcpy(tmp, path);
 
  char *curr = NULL;
  noeud *courant = NULL;
  if(*path=='/'){ 
    curr=strtok(tmp,"/");
    courant=depart->racine;
  }
  else{

    curr=strtok(tmp , "/");
    courant=depart;
  }
  if (depart -> est_dossier) {
    if ( !searchListe(courant, curr, courant)){
      free(tmp);
      return -3;// une erreur
    }
    while(curr != NULL){
      if ( !searchListe(courant, curr, courant)){
        free(tmp);
        return 1;// une erreur
      }
      curr = strtok(NULL , "/");
    }
    if (courant == NULL){
        free(tmp);
        return -3;
    } else {
      free(tmp);
      return 1 ;
    }
  }
  free(tmp);
  return 1;
}

bool searchListe(noeud *depart, char *curr, noeud *courant){
  liste_noeud *tmpListeNoeud = depart -> fils;
  if (!strcmp(curr,"..")){
    courant = depart -> pere;
    return true;
  }else {
    while (tmpListeNoeud != NULL && tmpListeNoeud -> no != NULL && strcmp(tmpListeNoeud -> no -> nom , curr)!=0 ) {  
      tmpListeNoeud = tmpListeNoeud -> succ;
    }
    if(tmpListeNoeud==NULL){
      return false;
    }
    courant = tmpListeNoeud -> no;
    if (courant == NULL){
      //Une des erreurs a voir
      return false;
    }
    return true;
  }
}

void analyseFic(const char *pathToFile, noeud **courant){
  FILE *flux=fopen(pathToFile,"r");
  if(flux==NULL){
    perror("Probleme ouverture de fichier");
  }else{
    char * line = NULL;
    size_t len = 0;
    size_t read;
    while ((read = getline(&line, &len, flux)) != (size_t)-1) {
        int res = analyseCommandLine (line, courant);
        if(res != 1){
          error(res);
          free(line);
          return;
        }
    }

    if (line)
        free(line);
    int r=fclose(flux);
    if(r!=0){
      perror("Probleme fermeture de fichier");
    }
  }
}

void error(int error){
  switch (error)
  {
  case -1:
    puts("Un parametre est manquant");
    break;
  case -2:
    puts("Erreur syntaxique");
    break;
  case -3:
    puts("Destination inconnue");
    break;
  case -4:
    puts("Commande Inconnue");
    break;
  case -5:
    puts("Parametre en trop");
    break;  
  case -6:
    break;
  default:
    puts("Erreur non defini");
    break;
  }

}

noeud *lectureChemin(char *path, noeud *current){
  char *token = NULL;
  noeud *tmpNode = NULL;
  if (*path=='/'){
    token = strtok(path, "/");
    tmpNode = current -> racine;
  } else {
    token = strtok(path, "/");
    tmpNode = current;
  }
  char *toCompare = token;
  while (token != NULL) {
    toCompare = token;
    token = strtok(NULL, "/");
    liste_noeud *tmpListe = tmpNode -> fils;
    while (tmpListe != NULL) {
      noeud *fils = tmpListe->no;
      if (fils!=NULL&&strcmp(fils->nom, toCompare) == 0) {
        // Le nœud correspondant a été trouvé, on passe au suivant
          tmpNode = fils;
          break;
      }
      tmpListe = tmpListe->succ;
    }
    if (tmpListe == NULL) {
      // Le nœud correspondant n'a pas été trouvé, le chemin est invalide
      puts("Chemin invalide");
      return NULL;
    }
  }
  return tmpNode;
}

noeud *lectureCheminToCreate(char *path, noeud *current, char *newName){
  char *token = NULL;
  noeud *tmpNode = NULL;
  if (*path=='/'){
    tmpNode = current -> racine;
    token =strtok(path, "/");
  } else {
    tmpNode = current;
    token =strtok(path, "/");
  }
  char *toCompare = token;
  while (token != NULL) {
    toCompare = token;
    token = strtok(NULL, "/");
    if (token == NULL){
      strcpy(newName, toCompare);
      return tmpNode;
    }
    liste_noeud *tmpListe = tmpNode -> fils;
    while (tmpListe != NULL) {
      noeud *fils = tmpListe->no;
      if (strcmp(fils->nom, toCompare) == 0) {
        // Le nœud correspondant a été trouvé, on passe au suivant
          tmpNode = fils;
          break;
      }
      tmpListe = tmpListe->succ;
      }
      if (tmpListe == NULL) {
        // Le nœud correspondant n'a pas été trouvé, le chemin est invalide
        puts("Chemin invalide");
        return NULL;
      }
    }
  return tmpNode;
}

// -5 Parametre en trop
// -4 Commande inconnue
// -3 Fichier/dossier inconnue
// -2 Erreur syntaxique
// -1 Parametre manquant
//  1 Reussite
