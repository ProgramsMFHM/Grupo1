/**
 * @file commentLink.h
 * @author Constanza Araya, Rodolfo Cifuentes, Bruno Martinez, Milton Hernández, Guliana Ruiz
 * @brief Cabeceras para funciones de commentLink.c
*/

#ifndef COMMENT_LINK_H
#define COMMENT_LINK_H

typedef struct _commentLinkNode CommentLinkNode;
typedef CommentLinkNode *PtrToCommentLinkNode;
typedef PtrToCommentLinkNode CommentLinkPosition;
typedef PtrToCommentLinkNode CommentLinkList;

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include "time.h"
#include "errors.h"
#include "comments.h"
#include "utilities.h"


/** \struct _commentLinkNode
 * @brief Lista de enlaces a comentarios
*/
struct _commentLinkNode {
    time_t commentID /*!< Nombre del Comentario */;
    PtrToComment commentNode; /*!< Comentario en la red */
    CommentLinkPosition next; /*!< Posicion siguiente en la lista */
};

// Funciones para el manejo de una lista de enlaces a comentarios
CommentLinkList create_empty_commentLinkList(CommentLinkList linkList);
void delete_commentLinkList(CommentLinkList linkList);
bool is_empty_commentLinkList(CommentLinkList linkList);
void print_commentLinkList(CommentLinkList linkList);
CommentLinkPosition find_commentLinkList_node(CommentLinkList linkList, time_t commentID);
CommentLinkPosition find_commentLinkList_prev_node(CommentLinkPosition P, CommentLinkList linkList);
CommentLinkPosition insert_commentLinkList_node_basicInfo(CommentLinkPosition prevPosition, time_t commentID);
CommentLinkPosition insert_commentLinkList_node_completeInfo(CommentLinkPosition prevPosition, PtrToComment commentNode);
void delete_commentLinkList_node(CommentLinkPosition P, CommentLinkList linkList);

// Funciones de interaccion con el comentario
CommentLinkPosition complete_commentLinkList_node(CommentLinkPosition P, CommentTable commentTable);
CommentLinkPosition commentLinkList_first(CommentLinkList linkList);
CommentLinkPosition commentLinkList_last(CommentLinkList linkList);
CommentLinkPosition commentLinkList_advance(CommentLinkPosition P);

// Funciones de ordenamiento de listas de enlaces a comentarios
void split_commentLinkList(CommentLinkPosition source, CommentLinkPosition* frontRef, CommentLinkPosition* backRef);
CommentLinkPosition merge_commentLinkLists(CommentLinkPosition a, CommentLinkPosition b);
void sort_commentLinkList_byID(CommentLinkPosition* headRef);
#endif