#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "Commande.h"

void cmdprintRecu(noeud *n, int niv, liste_noeud *nextNode, noeud *actuel);

int cmdprint(noeud *actuel){
    if (actuel != NULL){
        cmdprintRecu(actuel -> racine, 0, NULL, actuel);
        return 1;
    } else {
        puts("Le dossier racine / n'existe pas");
        return -6;
    }
}

void cmdprintRecu(noeud *n, int niv , liste_noeud *nextNode, noeud *actuel){
    char r = 'f';
    if (n != NULL){
        if (n -> est_dossier) r = 'd';
        for (int i = 0; i < niv; i++){printf("   ");}

        if (n->nom!=NULL&&n->nom[0] == '\0'){
            if (n == actuel){
                printf("/ *(%c)\n", r);
            } else {
                printf("/ (%c)\n", r);
            }
        } else {
            if (n == actuel){
                printf("%s *(%c)\n", n->nom , r);
            } else {
                printf("%s (%c)\n", n->nom , r);
            }
        }

        if (n -> est_dossier){
            
            if(n -> fils != NULL ){
               
               if(n -> fils -> no != NULL){
            
                cmdprintRecu(n -> fils -> no , niv + 1, n -> fils, actuel);
            }
            }
            
    
        }
        if (nextNode != NULL){
            if (nextNode -> succ != NULL){
                if (nextNode -> succ -> no != NULL){
                    cmdprintRecu(nextNode -> succ -> no , niv, nextNode -> succ, actuel);
                }
            }
        }
        return;
    }
}

noeud* searchFolder(noeud* depart,char *curr);

noeud* getFolder(const char* path, noeud* depart){
    char *tmp = malloc ((strlen(path)+1)* sizeof(char));
    strcpy(tmp, path);
    char *curr = strtok(tmp , "/");
    noeud *courant = depart;
    if (depart == NULL) {
        return NULL;
    }
    if (depart -> est_dossier) {
        while(curr != NULL){
            courant=searchFolder(courant, curr);
            if (courant == NULL) {
                return NULL;
            }
            curr = strtok(NULL , "/");
        }
        free(tmp);
        return courant;
    }
    free(tmp);
    return NULL;
}


noeud* searchFolder(noeud *depart, char *curr){
    if(depart==NULL){
        return NULL;
    }
    liste_noeud *tmpListeNoeud = depart -> fils;
    while (tmpListeNoeud!= NULL && strcmp(tmpListeNoeud -> no -> nom , curr) !=0) {
        tmpListeNoeud = tmpListeNoeud -> succ;
    }
    if(tmpListeNoeud!=NULL){
        return tmpListeNoeud -> no;
    }
    else{
        printf("le dossier %s n'existe pas\n",curr);
        return NULL;
    }
  
}
int cdTerm(noeud **current){
    if(current!=NULL){
        if((*current)->est_dossier){
             *current=(*current)->racine;
             return 1;
        }
        puts("Ce n'est pas un dossier.");
        return -6;
            
    }
    puts("Le noeud courrant est null");
    return -6;

};
int cdPere(noeud **current){

    if(current!=NULL){
        if((*current)->est_dossier){
            if(*current==(*current)->racine){
                puts("Vous etes dans la racine");
                return 1;
            }
            else{
                *current=(*current)->pere;
                return 1;
            }
        }
        puts("Le noeud courrant n'est pas un dossier");
        return -6;
    }
    return -6;
}

int cdPath(noeud **current,char *path){
    *current=lectureChemin(path,*current);
    if(current==NULL)return -6;
    return 1;
}

int ls(noeud *current){
     if(current!=NULL&&current->est_dossier){
        if(current->fils!=NULL){      
            liste_noeud *tmp=current->fils;
            if(tmp->no==NULL){
                puts("Le dossier est vide");
                return 1;
            }
            if (current->nom[0] == '\0'){
                printf("/ :\n");
            }else {
                printf("%s :\n",current -> nom);
            }
            while(tmp!=NULL){
                if(tmp->no->est_dossier){
                    printf("  /%s\n",tmp->no->nom);
                }
                else{
                     printf("  %s\n",tmp->no->nom);
                }
                tmp=tmp->succ;

            }
        }
        return 1;
   }
   puts("Le noeud courrant est null ou bien n'est pas un dossier");
   return -6;

}


void cmdPwdRecu (noeud *current);

void cmdPwd(noeud *current){
    cmdPwdRecu(current);
    puts("");
}

void cmdPwdRecu (noeud *current){
    if (current -> pere == current)
    {
        printf("/");
    }else {
        cmdPwdRecu(current -> pere);
        printf("%s/", current -> nom);
    }
}
int isPere(noeud *node,noeud* curr);
int cmdRm(noeud *current, char *path){
    
    assert(current != NULL);
    //on test si on supprime pas le noeud courant;
    noeud* noeuSupr=lectureChemin(path,current);
    if(isPere(noeuSupr,current)){
        puts("Vous supprimez le noeud courant.");

        return -6;
    }
    suprimeNodeFromPere(noeuSupr -> pere , noeuSupr -> nom);
    libereEspace(noeuSupr);
    return 1;
}
int isPere(noeud* node,noeud* curr){
    if(curr==curr->racine)return 0;
    if(curr->pere==node)return 1;
    return isPere(node,curr->pere);
}
bool exist(liste_noeud* fils,char* nom);
bool wrongName(char* nom,bool isFile);

int mkdir(noeud* courant,char *nom){
    assert(courant!=NULL);
    assert(courant->est_dossier);
    if(courant->fils==NULL){
        liste_noeud* currF=malloc(sizeof(liste_noeud));
        assert(currF!=NULL);
        courant->fils=currF;

    }
    if (exist(courant->fils,nom)){
        printf("%s existe déjà.\n",nom);
        return -6;
    }

    if(wrongName(nom,false)){
        printf("%s n'est pas un nom valide.\n",nom);
        return -6;
    }
    noeud* newFolder=createNode(nom,courant,courant->racine,NULL);
    newFolder->est_dossier=true;
    liste_noeud* fils=malloc(sizeof(liste_noeud));
    assert(fils!=NULL);
    fils->no=NULL;
    fils->succ=NULL;
    newFolder->fils=fils;
    addFils(courant->fils,newFolder);
   
    return 1;

}

int touch(noeud* courant,char* nom){
    assert(courant!=NULL);
    assert(courant->est_dossier);
    if(wrongName(nom,true)){
        printf("%s n'est pas un nom valide.\n",nom);
        return -6;
    }
    if(exist(courant->fils,nom)){
        printf("%s existe déjà.\n",nom);
        return -6;
    }
    noeud* newFile=createNode(nom,courant,courant->racine,NULL);
    newFile->est_dossier=false;
     if(courant->fils==NULL){
        liste_noeud* currF=malloc(sizeof(liste_noeud));
        courant->fils=currF;
    }
    addFils(courant->fils,newFile);
    return 1;
}

bool exist(liste_noeud* fils,char* nom){
    if (fils == NULL){
        return false;
    }
    liste_noeud* tmp=fils;
    while (tmp!=NULL){
        if(tmp -> no != NULL){
      
            if(tmp->no->nom!=NULL&&strcmp(tmp->no->nom,nom)==0){
                return true;
            }
        }
        tmp=tmp->succ;
    }
    return false;
}

bool wrongName(char* nom,bool isFile){
    assert(strlen(nom)<100);
    for(size_t i=0;i<strlen(nom);++i){
        if(isalnum(nom[i])==0&&!isFile){
            return true;
        }
        else if(isalnum(nom[i])==0&&nom[i]!='.'){
            return true;
            
         }
    }
    return false;
}

noeud* copyNoeud(const noeud* n1,noeud* p);
//cette fonction renvoie le dernier nom du chemin et modifie path2 en retirant le dernier nom du chemin

char* getPath(const char* path) {
    size_t len = 0;
    for (size_t i = 0; i < strlen(path); i++) {
        if (*(path + i) == '/') {
            len = 0;
        } else {
            ++len;
        }
    }

    if ((strlen(path) - len) <= 1 || len == strlen(path)) {
        char* newPath = NULL;

        if (*path == '/') {
            newPath = malloc(2 * sizeof(char));
            *newPath = '/';
            *(newPath + 1) = '\0';
        } else {
            newPath = malloc(2 * sizeof(char));
            *newPath = '.';
            *(newPath + 1) = '\0';
        }

        return newPath;
    } else {
        char* newPath = malloc((strlen(path) - len + 1) * sizeof(char));
        strncpy(newPath, path, strlen(path) - len);
        newPath[strlen(path) - len] = '\0';
        return newPath;
    }
}


char* getLast(char* path) {

    size_t len = 0;
    char* tmp = NULL;

    for (size_t i = 0; i < strlen(path); i++) {
        if(*(path+i)=='/'){
            len=0;
            tmp=NULL;
       }
       else if(*(path+(i-1))=='/'){
            tmp=path+i;
            ++len;
       }
       else{
            ++len;
       }
    }

    if (len == strlen(path)) {
        return path;
    }

    char* res = malloc((len + 1) * sizeof(char));
    strncpy(res, tmp, len);
    res[len] = '\0';

    return res;
}



liste_noeud* copyListe(liste_noeud* l, noeud* p) {
    liste_noeud* tmp = l;
    liste_noeud* tmp2 = malloc(sizeof(liste_noeud));
    tmp2->no = NULL;
    tmp2->succ = NULL;

    while (tmp != NULL) {
        noeud* a = copyNoeud(tmp->no, p);
        if (a != NULL) {
            addFils(tmp2, a);
        }
        tmp = tmp->succ;
    }

    return tmp2;
}

noeud* copyNoeud(const noeud* n1,noeud* p){
     if(n1==NULL){
        return NULL;

    }
    noeud* res=malloc(sizeof(noeud));
    memmove(res,n1,sizeof(noeud)); 
    res->pere=p;
    if(res->est_dossier){
        res->fils=copyListe(n1->fils,res);
    }
    return res;
}
char *getAbsolPath(noeud *curr);
int cmdMv(char* path1,char* path2,noeud* curr){
    noeud *filsAdeplacer = lectureChemin(path1, curr);
    char *newName = malloc(sizeof(char)*100);
    noeud *newPere = lectureCheminToCreate(path2, curr, newName);

    if(newPere==NULL||filsAdeplacer==NULL){
        puts("chemin incorrect");
        return -6;
    }
    if(!newPere->est_dossier){
        printf("%s n'est pas un dossier.\n",newPere->nom);
        return -6;
    }
    if(wrongName(newName,filsAdeplacer->est_dossier)){
        printf("%s est un nom incorrect.\n", newName);
        return -6;
    }
    if(exist(newPere->fils,newName)){
        printf("le fichier/dossier %s existe déja.\n",newName);
        return -6;
    }

    char *absPathD = getAbsolPath(newPere);
    char *absPathF = getAbsolPath(filsAdeplacer);
    if(strstr(absPathD,absPathF)){
        free(absPathD);
        free(absPathF);
        puts("impossible de copier le dossier dans lui mème.");
        return -6;
    }

    free(absPathD);
    free(absPathF);
    moveFils(filsAdeplacer, newPere);
    strcpy(filsAdeplacer->nom, newName);
    free(newName);
    return 1;

}
int cp(char* path1,char* path2,noeud* curr){
    char* pathDes=getPath(path2);
    noeud* des;
    if(!strcmp(pathDes,".")){des=curr;}
    else if(!strcmp(pathDes,"/")){des=curr->racine;}
    else{
        des=lectureChemin(pathDes,curr);
        if(des==NULL){
            puts("le chemin de destination est incorrect.");
            free(pathDes);
            return -6;
        }
    }
    

    noeud* first=lectureChemin(path1,curr);
    if(des!=NULL&&!des->est_dossier){
        printf("%s n'est pas un dossier.\n",pathDes);
        free(pathDes);
        return -6;
    }


    char *a = getLast(path2);


    if(wrongName(a,first->est_dossier)){
        printf("%s est un nom incorrect.\n", a);
        free(pathDes);
        free(a);
        return -6;
    }
    
    if(pathDes!=NULL){
        if(!strcmp(pathDes,".")&&!strcmp(pathDes,"/")&&analyseChemin(pathDes,curr)){
            puts("chemin incorrect.");
            free(pathDes);
            free(a);
            return -6;
        }
    }

    if(exist(des->fils,a)){
        printf("le fichier/dossier %s existe déja.\n",a);
        free(pathDes);
        free(a);
        return -6;
    }
    if(des!=des->racine){
        char *absPathD = getAbsolPath(des);
        char *absPathF = getAbsolPath(first);
        if(strstr(absPathD,absPathF)){
            free(absPathD);
            free(absPathF);
            puts("impossible de copier le dossier dans lui mème.");
            free(pathDes);
            free(a);
            return -6;
        }
        free(absPathD);
        free(absPathF);
    }

    noeud* copy=copyNoeud(first,curr);
    strcpy(copy->nom,a);
    if(exist(des->fils,copy->nom)){
        printf("le fichier/dossier %s existe déja.\n",copy->nom);
        free(pathDes);
        free(a);
        return -6;
    }
    if(des->fils==NULL){
        liste_noeud* currF=malloc(sizeof(liste_noeud));
        des->fils=currF;
    }
    copy->pere=des;
    addFils(des->fils,copy);
    free(pathDes);
    
    return 1;

}

char *absolPathRec(char *path,noeud *curr);
char *getAbsolPath(noeud *curr){
    char *res=absolPathRec("",curr);
    return res;
}
char *absolPathRec(char *path, noeud *curr) {
    if (curr -> pere == curr) {
        strcat(path,"/");
        return path;
    } else {
        size_t sizestr = strlen(curr->nom) + 2 + strlen(path) +1;
        char *tmp = malloc(sizestr * sizeof(char));
        strcpy(tmp, "/");
        strcat(tmp, curr->nom);
        strcat(tmp,path);
        //free(path);
        return absolPathRec(tmp, curr->pere);
    }
}

