#include"hachage.h"

/*creer l'element dans la mémoire*/
hachage_t* creer_element(char* mot, char* valeur){
    hachage_t* element = malloc(sizeof(hachage_t));
    if (element == NULL) {
        /*pour quitter si l'element est vide*/
        free(element);
        return NULL;
    }
    /*on ajoute +1 pour le character '\0'*/
    element->mot = malloc(strlen(mot)+1); /* allocation de mémoire pour mot*/
    /*On verifie si le mot n'est pas null*/
    if (element->mot == NULL) {
        free(element);
        return NULL;
    }
    element->valeur = malloc(strlen(valeur)+1); /* allocation de mémoire pour valeur*/
    /*On verifie si la valeur n'est pas null*/
    if (element->valeur == NULL) {
        free(element->mot);
        free(element);
        return NULL;
    }
    strcpy(element->mot, mot);
    strcpy(element->valeur, valeur);
    element->suivant = NULL;
    return element;
}


/*creer la table dans la mémoire*/
HachTable_t* creer_table(int taille){
    HachTable_t* table = malloc(sizeof(HachTable_t));
    /*si l'allocation a echoué*/
    if (table == NULL){
        exit(0);
    }
    table->taille = taille;
    table->nb_element = 0;
    /*met tout les octets de la table a la valeur 0*/
    table->table = calloc(taille, sizeof(hachage_t*));
    /*On verifie si les element de la table ne sont pas égale a null donc on verifie si calloc a réussi */
    if (table->table == NULL) {
        free(table);
        return NULL;
    }
    return table;
}

/*supprimer de la mémoire l'élément*/
void liberer_element(hachage_t* element){
    free(element->valeur);
    free(element->mot);
    free(element);
}

/*supprimer de la mémoire le tableau*/
void liberer_table(HachTable_t* table){
    int i;
    for (i = 0; i < table->taille; i++){
        /*on regarde l'element a l'indice i dans la table*/
        hachage_t* element = table->table[i];
        /*si il est pas égale a NULL on supprime l'element grace a la methode liberer_element*/
        while  (element != NULL){
            hachage_t* tmp = element;
            element=element->suivant;
            liberer_element(tmp);
        }
    }
    /*on supprime le dernier element restant de la mémoire */
    free(table->table);
    /*on supprime maintenant la table de la mémoire*/
    free(table);
}

/*cette methode sert a avoir le milieu du mot */
int milieu_mot(char* mot,int taille_mot){
    int milieu = taille_mot / 2;
    if (taille_mot % 2 == 0) {
        return mot[milieu];
    } 
    else {
        /*milieu+1 pour si on venait a avoir un nombre impaire
        comme par exemple 7 si on veut obtenir 4 et non 3*/
        return mot[milieu+1];
    }
    return 0;
}

int hashMot(char* mot,int taille) {
    int nbHash = 0;
    int tailleMot = strlen(mot);
    if (tailleMot == 0) {
        return 0;
    }
    /*on prend le premier element du mot*/
    int debut = mot[0];
    /*on prend le dernier element du mot*/
    int fin = mot[tailleMot];
    /*pour prendre la lettre du milieu*/
    int milieu = mot[milieu_mot(mot,tailleMot)];
    /*parcours jusqu'a trouver le character nul "\0"*/
    int i;
    for (i = 0; mot[i]!='\0'; i++){
        nbHash += (mot[i]*(debut+milieu*fin));
    }
    return nbHash % taille;
}


void inserer_element(HachTable_t* table, char* mot, char* valeur){
    if (table == NULL || mot == NULL || valeur == NULL){
        exit(EXIT_FAILURE);
    }

    hachage_t* element = creer_element(mot,valeur);
    int hash = hashMot(mot,table->taille);

    hachage_t* elt_actuel = table->table[hash];

    /* Si la case est vide, on insère l'élément directement*/
    if (elt_actuel == NULL){
        table->table[hash] = element;
        table->nb_element++;
    }
    /* Sinon, on parcourt la liste chainée pour ajouter l'élément en fin de liste*/
    else {
        while (elt_actuel->suivant != NULL){
            elt_actuel = elt_actuel->suivant;
        }
        elt_actuel->suivant = element;
    }
}

/*donne l'index du mot mit en paramètre*/
int rechercher_index_mot(HachTable_t* table, char* mot){
    if (table == NULL){
        return -1;
    }

    int index = hashMot(mot,table->taille);
    hachage_t* element = table->table[index];

    while (element != NULL){
        if (strcmp(element->mot, mot) == 0){
            return index;
        }
        element = element->suivant;
    }

    /*si le mot n'est pas présent*/
    return -1;
}

/* Retourne l'identifiant unique du mot donné ou -1 si le mot n'est pas présent dans la table*/
int numero_cle(HachTable_t* table, char* mot){
    return rechercher_index_mot(table, mot);
}
/*recherche un mot grace a l'identifiant*/
char* rechercher_mot(HachTable_t* table, int id){
    /*verifier que la table n'est pas vide et que l'id est correct pour pas avoir 
    de segmentation fault */
    if (table == NULL || id < 0 || id >= table->taille){
        return NULL;
    }
    hachage_t* element = table->table[id];
    /*parcours la table en recherchant le mot correspondant a l'id*/
    while (element != NULL){
        if (element->mot != NULL && hashMot(element->mot, table->taille) == id){
            return element->mot;
        } 
        element = element->suivant;
    }
    /* si pas trouvé on retourne NULL*/
    return NULL;
}

#define TAILLE_MOT 100
int main(int argc, char *argv[]){
  HachTable_t* table = creer_table(1000);
  inserer_element(table, "chat", "animal domestique");
  inserer_element(table, "chien", "animal domestique");
  inserer_element(table, "voiture", "moyen de transport");
  inserer_element(table, "vélo", "moyen de transport");
  inserer_element(table, "pomme", "fruit");
  inserer_element(table, "banane", "fruit");
  inserer_element(table, "enanab", "fruit");
  inserer_element(table, "enanab", "fruit");
  int cle_chat = numero_cle(table, "chat");
  int cle_banane = numero_cle(table, "banane");
  int cle_enanab = numero_cle(table, "enanab");
  int cle_voiture = numero_cle(table, "voiture");
  int cle_domestique = numero_cle(table, "animal domestique");
  int cle_inexistant = numero_cle(table, "inexistant");
  printf("Cle chat : %d\n", cle_chat);
  printf("Cle voiture : %d\n", cle_voiture);
  printf("Cle banane : %d\n", cle_banane);
  printf("Cle enanab : %d\n", cle_enanab);
  printf("Cle domestique : %d\n", cle_domestique);
  printf("Cle inexistant : %d\n", cle_inexistant);
  char* mot1 = rechercher_mot(table, cle_chat);
  char* mot2 = rechercher_mot(table, cle_voiture);
  char* mot_inexistant = rechercher_mot(table, -1);
  printf("Mot 1 : %s\n", mot1);
  printf("Mot 2 : %s\n", mot2);
  printf("Mot inexistant : %s\n", mot_inexistant);

  liberer_table(table);
  return EXIT_SUCCESS;
}