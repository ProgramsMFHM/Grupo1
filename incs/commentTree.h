/**
 * @file commentTree.h
 * @author Constanza Araya, Rodolfo Cifuentes, Bruno Martinez, Milton Hernández, Guliana Ruiz
 * @brief Cabeceras para funciones de commentTree.c
*/
#ifndef COMMENT_TREE_H
#define COMMENT_TREE_H

typedef struct _commentTreeNode CommentTreeNode;
typedef CommentTreeNode* PtrToCommentTreeNode;
typedef PtrToCommentTreeNode CommentTreePosition;
typedef PtrToCommentTreeNode CommentTree;

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "user.h"
#include "genreLink.h"
#include "bandLink.h"
#include "utilities.h"

#define max(a,b) (((a) > (b)) ? (a) : (b))

struct _commentTreeNode
{
    unsigned int commentID;
    time_t timestamp;
    char* commentText;
    UserPosition user;
    GenreLinkPosition genres;
    BandLinkPosition bands;
	CommentTreePosition left;
	CommentTreePosition right;
	int height;
};

// Utilidades para el AVL
int height(CommentTree tree);
CommentTree make_empty_commentTree(CommentTree tree);
CommentTreePosition add_comment_tags(CommentTreePosition comment);

// Funciones de diccionario
CommentTreePosition insert_commentTree_node(CommentTree tree, unsigned int commentID, time_t timestamp, char* commentText, UserPosition user, GenreLinkPosition genres, BandLinkPosition bands);
CommentTreePosition find_commentTree_node(CommentTree tree, unsigned int commentID);
CommentTree delete_commentTree_node(CommentTree tree, unsigned int commentID);
void delete_commentTree(CommentTree tree);
CommentTreePosition find_commentTree_min(CommentTree tree);
CommentTreePosition find_commentTree_max(CommentTree tree);

// Rotaciones
CommentTreePosition single_rotate_with_right(CommentTreePosition A);
CommentTreePosition single_rotate_with_left(CommentTreePosition A);
CommentTreePosition double_rotate_with_right(CommentTreePosition A);
CommentTreePosition double_rotate_with_left(CommentTreePosition A);

// Impresion y recorrido en AVL
void print_commentTree_node(CommentTreePosition node);
void print_commentTree(CommentTree tree);
void complete_tree_tags(CommentTree tree);

#endif