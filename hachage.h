/**
Fichier hachage.h
*/
#ifndef __HACHAGE_H__
#define __HACHAGE_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*Vous travaillerez ici
*/
typedef struct hachage {
    char* mot;
    char* valeur;
    struct hachage* suivant;
} hachage_t;

typedef struct HashTable{
    hachage_t** table;
    int taille;
    int nb_element;
} HachTable_t;

/*
creer l'element dans la mémoire
@param mot est le mot associé a l'élément
@param valeur est la valeur associé au mot
@ensure si resultat==NULL alors l'allocation de mémoire a échoué
@ensure resultat->mot !=NULL && resultat->valeur !=NULL
compléxité: temps O(1)
            espace O(1) 
*/
hachage_t* creer_element(char* mot, char* valeur);

/*
creer la table dans la mémoire
@param taille est la taille de la table de hachage
@ensure si resultat==NULL alors l'allocation de mémoire a echoué
@ensure resultat->nb_element = 0 && resultat->table != NULL && resultat->taille == taille
compléxité: temps O(1)
            espace O(taille)
*/
HachTable_t* creer_table(int taille);

/*
supprimer de la mémoire l'élément
@param element l'element a liberer
compléxité: temps O(1)
            espace O(1)
*/
void liberer_element(hachage_t* element);

/*
supprimer de la mémoire le tableau
@param table la table a libérer
compléxité: temps O(n)
            espace O(1)
*/
void liberer_table(HachTable_t* table);

/*
cette methode sert a avoir le milieu du mot
@param mot le mot dont ou souhaite avoir le caractere du milieu
@param taille_mot taille du mot
@return la valeur ASCII du caractère du milieu du mot
compléxité: temps O(1)
            espace O(1)
*/
int milieu_mot(char* mot,int taille_mot);

/*
fonction de hachage
@param mot le mot dont on veut calculer le hash
@param taille la taille de la table de hashage
@return la valeur du hash du mot donné en paramètre
compléxité: temps O(n)
            espace O(1)
*/
int hashMot(char* mot,int taille);

/*
permet d'inserer un element dans la table de hachage
@param table la table dans la quel on veut inserer l'element
@param mot le mot qu'on souhaite insérer
@param valeur la valeur associé au mot qu'on souhaite insérer
compléxité: temps O(1), dans le pire des cas O(n)
            espace O(1)
*/
void inserer_element(HachTable_t* table, char* mot, char* valeur);

/*
donne l'index du mot mit en paramètre (si il est dans la table)
@param table la table ou l'on l'on cherche le mot
@param mot le mot qu'on souhaite rechercher
@return l'index du mot dans la table de hachage donné en paramètre
compléxité: temps O(n)
            espace O(1)
*/
int rechercher_index_mot(HachTable_t* table, char* mot);

/* 
Retourne l'identifiant unique du mot donné ou -1 si le mot n'est pas présent dans la table
@param table la table ou l'on cherche l'identifiant du mot
@param mot le mot pour lequel on cherche son identifiant unique
@return l'identifiant du mot ou sinon -1 si on le trouve pas
compléxité: temps O(1), dans le pire des cas O(n)
            espace O(1)
*/
int numero_cle(HachTable_t* table, char* mot);

/*
recherche un mot grace a l'identifiant
@param table la table ou l'on cherche le mot
@param id l'identifiant qui va nous permettre de trouver le mot
@return le mot qui correspond a l'id donné en parmètre ou sinon NULL
compléxité: temps O(n), dans le pire des cas O(n)
            espace O(1)
*/
char* rechercher_mot(HachTable_t* table, int id);

#endif
