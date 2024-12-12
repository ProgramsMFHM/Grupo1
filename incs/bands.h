/**
 * @file bands.h
 * @author Constanza Araya, Rodolfo Cifuentes, Bruno Martinez, Milton Hernández, Guliana Ruiz
 * @brief Cabeceras para funciones de bands.c
*/

#ifndef BANDS_H
#define BANDS_H

#define BANDS_TABLE_SIZE 20 /**< Tamaño de la tabla hash de bandas */

typedef struct _band Band;
typedef Band* PtrToBand;
typedef PtrToBand BandPosition;
typedef PtrToBand BandList;
typedef struct _bandHashTable* BandTable;

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "hash.h"
#include "commentLink.h"

/** \struct _band
 * @brief Representa un banda en la lista de bandas
 */
struct _band {
    char* band;               /**< banda almacenada */
    CommentLinkList comments; /**< Lista de comentarios relacionados con la banda */
    BandPosition next;        /**< Puntero a la siguiente banda en la lista */
};

/** \struct _bandHashTable
 * @brief Representa una tabla hash para bandas
 */
struct _bandHashTable {
    BandList buckets[BANDS_TABLE_SIZE];  /**< Arreglo de punteros a listas enlazadas de bandas */
    int bandCount;                       /**< Contador de bandas */
    bool modified;                       /**< Indica si la tabla ha sido modificada desde que se cargo */
};

// Funciones para listas de bandas
BandList create_empty_bandList(BandList bandList);
void delete_bandList(BandList bandList);
bool is_empty_bandList(BandList bandList);
void print_bandList(BandList bandList);
BandPosition find_bandList_band(BandList bandList, char* band);
BandPosition find_bandList_prev_band(BandPosition position, BandList bandList);
BandPosition insert_bandList_band(BandPosition prevPosition, char* band);
void delete_bandList_band(BandPosition position, BandList bandList);

// Funciones de interaccion con el usuario
BandPosition bandList_first(BandList bandList);
BandPosition bandList_last(BandList bandList);
BandPosition bandList_advance(BandPosition position);
char* get_band(BandPosition position);

// Funciones para la tabla de bandas
BandTable create_bandTable(BandTable bandTable);
void print_bandTable(BandTable bandTable);
BandPosition insert_bandTable_band(char* band, BandTable bandTable);
void delete_bandTable_band(char* band, BandTable bandTable);
void delete_bandTable(BandTable bandTable);
BandPosition find_bandTable_band(char* band, BandTable bandTable);
void save_bandTable(BandTable bandTable);

#endif