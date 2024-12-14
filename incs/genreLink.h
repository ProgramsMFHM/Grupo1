/**
 * @file genreLink.h
 * @author Constanza Araya, Rodolfo Cifuentes, Bruno Martinez, Milton Hernández, Guliana Ruiz
 * @brief Cabeceras para funciones de genreLink.c
*/

#ifndef GENRE_LINK_H
#define GENRE_LINK_H

typedef struct _genreLinkNode GenreLinkNode;
typedef GenreLinkNode *PtrToGenreLinkNode;
typedef PtrToGenreLinkNode GenreLinkPosition;
typedef PtrToGenreLinkNode GenreLinkList;

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include "errors.h"
#include "genres.h"
#include "utilities.h"


/** \struct _genreLinkNode
 * @brief Lista de enlaces a generos
*/
struct _genreLinkNode {
    char* genre          /*!< Nombre del Genero */;
    PtrToGenre genreNode; /*!< Genero en la red */
    GenreLinkPosition next; /*!< Posicion siguiente en la lista */
};

// Funciones para el manejo de una lista de enlaces a generos
GenreLinkList create_empty_genreLinkList(GenreLinkList linkList);
void delete_genreLinkList(GenreLinkList linkList);
bool is_empty_genreLinkList(GenreLinkList linkList);
void print_genreLinkList(GenreLinkList linkList);
GenreLinkPosition find_genreLinkList_node(GenreLinkList linkList, char* genre);
GenreLinkPosition find_genreLinkList_prev_node(GenreLinkPosition P, GenreLinkList linkList);
GenreLinkPosition insert_genreLinkList_node_basicInfo(GenreLinkPosition prevPosition, char* genre);
GenreLinkPosition insert_genreLinkList_node_completeInfo(GenreLinkPosition prevPosition, PtrToGenre genreNode);
void delete_genreLinkList_node(GenreLinkPosition P, GenreLinkList linkList);

// Funciones de ordenamiento de listas de enlaces a generos
void split_genreLinkList(GenreLinkPosition source, GenreLinkPosition* frontRef, GenreLinkPosition* backRef);
GenreLinkPosition merge_genreLinkLists(GenreLinkPosition a, GenreLinkPosition b);
void sort_genreLinkList_byName(GenreLinkPosition* headRef);

// Operaciones de conjunto sobre LES
GenreLinkList union_genreLinkList(GenreLinkList list1, GenreLinkList list2, int* size);
GenreLinkList intersection_genreLinkList(GenreLinkList list1, GenreLinkList list2, int* size);
double jacardIndex_genreLinkList(GenreLinkList list1, GenreLinkList list2);

// Funciones de interaccion con el genero
GenreLinkPosition complete_genreLinkList_node(GenreLinkPosition P, GenreTable userTable);
GenreLinkPosition genreLinkList_first(GenreLinkList linkList);
GenreLinkPosition genreLinkList_last(GenreLinkList linkList);
GenreLinkPosition genreLinkList_advance(GenreLinkPosition P);

// Funciones de ordenamiento de listas de enlaces a generos
GenreLinkList bubbleSort_genreLinkList(GenreLinkList linkList);
void swap_genreLinkList_nodes(GenreLinkPosition a, GenreLinkPosition b);

#endif