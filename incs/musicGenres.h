/**
 * @file music_genres.h
 * @author Constanza Araya, Rodolfo Cifuentes, Bruno Martinez, Milton Hernández, Guliana Ruiz
 * @brief Cabeceras para funciones de music_genres.c
*/

#ifndef MUSIC_GENRES_H
#define MUSIC_GENRES_H

#define MUSIC_GENRES_TABLE_SIZE 20 /**< Tamaño de la tabla hash de generos musicales */

typedef struct _musicGenre MusicGenre;
typedef MusicGenre* PtrToMusicGenre;
typedef PtrToMusicGenre MusicGenrePosition;
typedef PtrToMusicGenre MusicGenreList;
typedef struct _musicHashTable* MusicGenresTable;

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "hash.h"
#include "comments.h"

/** \struct _musicGenre
 * @brief Representa un genero musical en la lista de generos
 */
struct _musicGenre {
    char* genre;             /**< genero musical almacenado */
    CommentList comments;    /**< Lista de comentarios relacionados con el genero */
    MusicGenrePosition next; /**< Puntero al siguiente genero en la lista */
};

/** \struct _musicHashTable
 * @brief Representa una tabla hash para generos musicales
 */
struct _musicHashTable {
    MusicGenreList buckets[MUSIC_GENRES_TABLE_SIZE];  /**< Arreglo de punteros a listas enlazadas de generos musicales */
    int genreCount;                              /**< Contador de generos musicales */
    bool modified;                              /**< Indica si la tabla ha sido modificada desde que se cargo */
};

// Funciones para listas de generos musicales
MusicGenreList create_empty_musicGenreList(MusicGenreList genreList);
void delete_musicGenreList(MusicGenreList genreList);
bool is_empty_musicGenreList(MusicGenreList genreList);
void print_musicGenreList(MusicGenreList genreList);
MusicGenrePosition find_musicGenreList_genre(MusicGenreList genreList, char* genre);
MusicGenrePosition find_musicGenreList_prev_genre(MusicGenrePosition position, MusicGenreList genreList);
MusicGenrePosition insert_musicGenreList_genre(MusicGenrePosition prevPosition, char* genre, CommentList comments);
void delete_musicGenreList_genre(MusicGenrePosition position, MusicGenreList genreList);

// Funciones de interaccion con el usuario
MusicGenrePosition musicGenreList_first(MusicGenreList genreList);
MusicGenrePosition musicGenreList_last(MusicGenreList genreList);
MusicGenrePosition musicGenreList_advance(MusicGenrePosition position);
char* get_genre(MusicGenrePosition position);

// Funciones para la tabla de generos musicales
MusicGenresTable create_musicGenresTable(MusicGenresTable genresTable);
void print_musicGenresTable(MusicGenresTable genresTable);
MusicGenrePosition insert_musicGenre(char* genre, CommentList comments, MusicGenresTable genresTable);
void delete_musicGenresTable_genre(char* genre, MusicGenresTable genresTable);
void delete_musicGenresTable(MusicGenresTable genresTable);
MusicGenrePosition find_musicGenresTable_genre(char* genre, MusicGenresTable genresTable);

#endif