/**
 * @file genres.h
 * @author Constanza Araya, Rodolfo Cifuentes, Bruno Martinez, Milton Hernández, Guliana Ruiz
 * @brief Cabeceras para funciones de genres.c
*/

#ifndef GENRES_H
#define GENRES_H

#define GENRE_TABLE_SIZE 20 /**< Tamaño de la tabla hash de generos musicales */

typedef struct _genre Genre;
typedef Genre* PtrToGenre;
typedef PtrToGenre GenrePosition;
typedef PtrToGenre GenreList;
typedef struct _genreTable* GenreTable;

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "hash.h"
#include "comments.h"

/** \struct _genre
 * @brief Representa un genero musical en la lista de generos
 */
struct _genre {
    char* genre;             /**< genero musical almacenado */
    CommentList comments;    /**< Lista de comentarios relacionados con el genero */
    GenrePosition next; /**< Puntero al siguiente genero en la lista */
};

/** \struct _genreTable
 * @brief Representa una tabla hash para generos musicales
 */
struct _genreTable {
    GenreList buckets[GENRE_TABLE_SIZE];  /**< Arreglo de punteros a listas enlazadas de generos musicales */
    int genreCount;                              /**< Contador de generos musicales */
    bool modified;                              /**< Indica si la tabla ha sido modificada desde que se cargo */
};

// Funciones para listas de generos musicales
GenreList create_empty_genreList(GenreList genreList);
void delete_genreList(GenreList genreList);
bool is_empty_genreList(GenreList genreList);
void print_genreList(GenreList genreList);
GenrePosition find_genreList_genre(GenreList genreList, char* genre);
GenrePosition find_genreList_prev_genre(GenrePosition position, GenreList genreList);
GenrePosition insert_genreList_genre(GenrePosition prevPosition, char* genre, CommentList comments);
void delete_genreList_genre(GenrePosition position, GenreList genreList);

// Funciones de interaccion con el usuario
GenrePosition genreList_first(GenreList genreList);
GenrePosition genreList_last(GenreList genreList);
GenrePosition genreList_advance(GenrePosition position);
char* get_genre(GenrePosition position);

// Funciones para la tabla de generos musicales
GenreTable create_genresTable(GenreTable genresTable);
void print_genresTable(GenreTable genresTable);
GenrePosition insert_genre(char* genre, CommentList comments, GenreTable genresTable);
void delete_genresTable_genre(char* genre, GenreTable genresTable);
void delete_genresTable(GenreTable genresTable);
GenrePosition find_genresTable_genre(char* genre, GenreTable genresTable);
void save_genresTable(GenreTable bandTable);

#endif