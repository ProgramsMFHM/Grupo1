/**
 * @file music_genres.h
 * @author Constanza Araya, Rodolfo Cifuentes, Bruno Martinez, Milton Hernández, Guliana Ruiz
 * @brief Cabeceras para funciones de music_genres.c
*/

#ifndef MUSIC_GENRES_H
#define MUSIC_GENRES_H

#define MUSIC_GENRES_HASH_SIZE 20

typedef struct _musicGenre MusicGenre;
typedef MusicGenre* PtrToMusicGenre;
typedef PtrToMusicGenre MusicGenrePosition;
typedef PtrToMusicGenre MusicGenreList;
typedef struct _musicHashTable* MusicGenresTable;

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "hash.h"

/** \struct _musicGenre
 * @brief Representa un genero musical en la lista de generos
 */
struct _musicGenre {
    char genre[25]; /**< genero musical almacenado */
    MusicGenrePosition next; /**< Puntero al siguiente genero en la lista */
};

/** \struct _musicHashTable
 * @brief Representa una tabla hash para generos musicales
 */
struct _musicHashTable {
    MusicGenreList genreList; /**< Lista de generos asociada a una clave hash */
    int nodeCount; /**< Numero de nodos asociados a la clave hash */
};

// Funciones para listas de generos musicales
MusicGenreList create_empty_musicGenreList(MusicGenreList genreList);
void delete_musicGenreList(MusicGenreList genreList);
bool is_empty_musicGenreList(MusicGenreList genreList);
void print_musicGenreList(MusicGenreList genreList);
MusicGenrePosition find_musicGenreList_genre(MusicGenreList genreList, char* genre);
MusicGenrePosition find_musicGenreList_prev_genre(MusicGenrePosition position, MusicGenreList genreList);
MusicGenrePosition insert_musicGenreList_genre(MusicGenrePosition prevPosition, char* genre);
void delete_musicGenreList_genre(MusicGenrePosition position, MusicGenreList genreList);

// Funciones de interaccion con el usuario
MusicGenrePosition musicGenreList_first(MusicGenreList genreList);
MusicGenrePosition musicGenreList_last(MusicGenreList genreList);
MusicGenrePosition musicGenreList_advance(MusicGenrePosition position);
char* get_genre(MusicGenrePosition position);

// Funciones para la tabla de generos musicales
MusicGenresTable create_musicGenresTable(MusicGenresTable genresTable);
MusicGenresTable read_musicGenre_file(char* fileName, MusicGenresTable genresTable);
void print_musicGenresTable(MusicGenresTable genresTable);
MusicGenrePosition insert_musicGenre(char* genre, MusicGenresTable genresTable);
void delete_musicGenresTable_genre(char* genre, MusicGenresTable genresTable);
void delete_musicGenresTable(MusicGenresTable genresTable);
MusicGenrePosition find_musicGenresTable_genre(char* genre, MusicGenresTable genresTable);

#endif