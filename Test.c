#include "Commande.h"
#include <stdlib.h>

//TODO Il faut recouoer les fichiers et il faut mettre des ptit if pour par inclure plein de fois

int main(int argc, char const *argv[])
{
    liste_noeud *s1 = malloc(sizeof(liste_noeud));
    liste_noeud *s2 = malloc(sizeof(liste_noeud));
    liste_noeud *s3 = malloc(sizeof(liste_noeud));
    liste_noeud *s4 = malloc(sizeof(liste_noeud));
    liste_noeud *s5 = malloc(sizeof(liste_noeud));
    liste_noeud *s6 = malloc(sizeof(liste_noeud));
    liste_noeud *s7 = malloc(sizeof(liste_noeud));

    liste_noeud *s9 = malloc(sizeof(liste_noeud));

    liste_noeud *s10 = malloc(sizeof(liste_noeud));
    liste_noeud *s11 = malloc(sizeof(liste_noeud));

    noeud *a1 = createRacine(s1);

    noeud *a2 = createNode("Cours", a1, a1, s4);
    noeud *a3 = createNode("Td", a1, a1, s6);
    noeud *a4 = createNode("edt", a1, a1, NULL);
    noeud *a5 = createNode("ProjetC", a2, a1, s10);
    noeud *a6 = createNode("Anglais", a2, a1, s9);
    noeud *a7 = createNode("td1", a3, a1, NULL);
    noeud *a8 = createNode("td2", a3, a1, NULL);

    noeud *a9 = createNode("Conisgne.pdf", a5, a1, NULL);
    noeud *a10 = createNode("Main.c", a5, a1, NULL);
    
    s1 -> succ = s2;
    s1 -> no = a2;

    s2 -> succ = s3;
    s2-> no = a3;

    s3 -> succ = NULL;
    s3-> no = a4;

    s4 -> succ = s5;
    s4 -> no = a5;

    s5 -> succ = NULL;
    s5 -> no = a6;

    s6 -> succ = s7;
    s6 -> no = a7;

    s7 -> succ = NULL;
    s7 -> no = a8;

    s10 -> succ = s11;
    s10 -> no = a9;

    s11 -> succ = NULL;
    s11 -> no = a10;
   
    noeud *current=a1;
    cp("Cours/ProjetC","test",current);
    cdPath(&current,"Cours/ProjetC");
    ls(current);
    cmdPwd(current);
    cdPere(&current);
    cmdPwd(current);
    ls(current);
    
    cmdprint(current);
    cmdMv(a3 , a5);
    cmdprint(current);
    cmdMv(a6 , a9);
    cmdprint(current);
    // cmdRm(current, "ProjetC");
    
    return EXIT_SUCCESS;
}
