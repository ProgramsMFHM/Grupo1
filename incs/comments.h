/**
 * @file comments.h
 * @author Constanza Araya, Rodolfo Cifuentes, Bruno Martinez, Milton Hernández, Guliana Ruiz
 * @brief Cabeceras para funciones de comments.c
*/
#ifndef COMMENTS_H
#define COMMENTS_H

#define COMMENTS_PATH "./build/comments/"
#define MAX_COMMENT_LENGTH 300
#define COMMENTS_TABLE_SIZE 10 /**< Tamaño de la tabla hash de comentarios */

typedef struct _commentNode CommentNode;
typedef CommentNode* PtrToComment;
typedef PtrToComment CommentPosition;
typedef PtrToComment CommentList;
typedef struct _commentHashTable* CommentTable;

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "errors.h"
#include "hash.h"
#include "user.h"
#include "userLink.h"
#include "genreLink.h"
#include "commentLink.h"

/** \struct _commentNode
 * @brief Estructura que representa un nodo de comentario.
*/
struct _commentNode {
    time_t ID;                    /**< Identificador del comentario */
    char* text;                   /**< Texto del comentario */
    bool complete;               /**< Indica si los tags del comentario están completos */
    UserLinkPosition user;            /**< Usuario del comentario */
    GenreLinkList genres;         /**< Gustos musicales del comentario */
    BandLinkList bands;           /**< Bandas del comentario */
    PtrToComment next;            /**< Puntero al siguiente nodo de la lista enlazada */
};

/** \struct _commentHashTable
 * @brief Representa una tabla hash para comentarios
 */
struct _commentHashTable {
    CommentList buckets[COMMENTS_TABLE_SIZE];  /**< Arreglo de punteros a listas enlazadas de comentarios */
    int commentCount;                             /**< Contador de comentarios */
    bool modified;                             /**< Indica si la tabla ha sido modificada desde que se cargo */
};

// Funciones para un nodo de usuario
void print_commentNode(PtrToComment comment);
void save_commentNode(PtrToComment comment);

// Funciones de la lista de usuarios
CommentList create_empty_CommentList(CommentList commentList);
void delete_CommentList(CommentList commentList);
bool is_empty_CommentList(CommentList commentList);
void print_CommentList(CommentList commentList);
CommentPosition find_CommentList_node(CommentList commentList, time_t ID);
CommentPosition find_CommentList_prev_node(CommentPosition P, CommentList commentList);
CommentPosition create_new_comment(time_t ID, const char *text, char* author);
CommentPosition insert_CommentList_node(CommentPosition prevPosition, CommentPosition newNode);
CommentPosition complete_commentList_node(CommentPosition P, char* text, char* author);
bool delete_CommentList_node(CommentPosition P, CommentList commentList);


// Funciones de interaccion con el usuario
CommentPosition commentList_first(CommentList commentList);
CommentPosition commentList_last(CommentList commentList);
CommentPosition commentList_advance(CommentPosition P);

// Funciones para la tabla de comentarios
CommentTable create_commentTable(CommentTable commentTable);
void print_commentTable(CommentTable commentTable);
CommentPosition insert_commentTable_comment(CommentPosition comment, CommentTable commentTable);
void delete_commentTable_comment(time_t ID, CommentTable commentTable);
void delete_commentTable(CommentTable commentTable);
CommentPosition find_commentTable_comment(time_t ID, CommentTable commentTable);
void save_commentTable(CommentTable commentTable);

// Ordenamiento y completacion
CommentPosition complete_comment_tags(CommentPosition comment);

#endif