/**
 * @file bandLink.h
 * @author Constanza Araya, Rodolfo Cifuentes, Bruno Martinez, Milton Hernández, Guliana Ruiz
 * @brief Cabeceras para funciones de bandLink.c
*/

#ifndef BAND_LINK_H
#define BAND_LINK_H

typedef struct _bandLinkNode BandLinkNode;
typedef BandLinkNode *PtrToBandLinkNode;
typedef PtrToBandLinkNode BandLinkPosition;
typedef PtrToBandLinkNode BandLinkList;

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include "errors.h"
#include "bands.h"
#include "utilities.h"


/** \struct _bandLinkNode
 * @brief Lista de enlaces a bandas
*/
struct _bandLinkNode {
    char* band /*!< Nombre de la banda */;
    PtrToBand bandNode; /*!< Banda en la red */
    BandLinkPosition next; /*!< Posicion siguiente en la lista */
};

// Funciones para el manejo de una lista de enlaces a bandas
BandLinkList create_empty_bandLinkList(BandLinkList linkList);
void delete_bandLinkList(BandLinkList linkList);
bool is_empty_bandLinkList(BandLinkList linkList);
void print_bandLinkList(BandLinkList linkList);
BandLinkPosition find_bandLinkList_node(BandLinkList linkList, char* band);
BandLinkPosition find_bandLinkList_prev_node(BandLinkPosition P, BandLinkList linkList);
BandLinkPosition insert_bandLinkList_node_basicInfo(BandLinkPosition prevPosition, char* band);
BandLinkPosition insert_bandLinkList_node_completeInfo(BandLinkPosition prevPosition, PtrToBand bandNode);
void delete_bandLinkList_node(BandLinkPosition P, BandLinkList linkList);

// Funciones de ordenamiento de listas de enlaces a usuarios
void split_bandLinkList(BandLinkPosition source, BandLinkPosition* frontRef, BandLinkPosition* backRef);
BandLinkPosition merge_bandLinkLists(BandLinkPosition a, BandLinkPosition b);
void sort_bandLinkList_byName(BandLinkPosition* headRef);

// Funciones de interaccion con el usuario
BandLinkPosition complete_bandLinkList_node(BandLinkPosition P, BandTable userTable);
BandLinkPosition bandLinkList_first(BandLinkList linkList);
BandLinkPosition bandLinkList_last(BandLinkList linkList);
BandLinkPosition bandLinkList_advance(BandLinkPosition P);

// Funciones de ordenamiento de listas de enlaces a bandas
BandLinkList bubbleSort_bandLinkList(BandLinkList linkList);
void swap_bandLinkList_nodes(BandLinkPosition a, BandLinkPosition b);

#endif