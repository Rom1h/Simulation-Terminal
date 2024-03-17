#include "Commande.h"
#include "Parseur.h"
#include <stdlib.h>

//TODO Il faut recouoer les fichiers et il faut mettre des ptit if pour par inclure plein de fois

int main(int argc, char const *argv[])
{
    if (argc > 1){
        liste_noeud *fils = malloc(sizeof(liste_noeud));
        assert(fils != NULL);
        fils->no = NULL;
        fils->succ = NULL;
        noeud *racine = malloc(sizeof(noeud));
        assert(racine != NULL);
        createRacine(&racine , fils);
        analyseFic(argv[1], &racine);
        libereEspace(racine);
        puts("Toute les instructions ont été effectués");
    } else {
        puts("Entrez un fichier lors de l'execution");
    }
    return EXIT_SUCCESS;
}
