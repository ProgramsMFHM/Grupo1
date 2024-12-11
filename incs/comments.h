/**
 * @file comments.h
 * @author Constanza Araya, Rodolfo Cifuentes, Bruno Martinez, Milton Hernández, Guliana Ruiz
 * @brief Cabeceras para funciones de comments.c
*/
#ifndef COMMENTS_H
#define COMMENTS_H

#define COMMENTS_PATH "./build/comments/"
#define MAX_COMMENT_LENGTH 300

typedef struct _commentNode CommentNode;
typedef CommentNode* PtrToComment;
typedef PtrToComment CommentPosition;
typedef PtrToComment CommentList;

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "errors.h"
#include "hash.h"
#include "user.h"
#include "userLink.h"
#include "genreLink.h"
#include "bandLink.h"

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
CommentPosition complete_commentList_node(CommentPosition P, UserTable userTable);
bool delete_CommentList_node(CommentPosition P, CommentList commentList);


// Funciones de interaccion con el usuario
CommentPosition commentList_first(CommentList commentList);
CommentPosition commentList_last(CommentList commentList);
CommentPosition commentList_advance(CommentPosition P);

// Ordenamiento y completacion
CommentPosition complete_comment_tags(CommentPosition comment);

#endif