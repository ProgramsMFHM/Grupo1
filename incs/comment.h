/**
 * @file comment.h
 * @author Constanza Araya, Rodolfo Cifuentes, Bruno Martinez, Milton Hernández, Guliana Ruiz
 * @brief Cabeceras para funciones de comment.c
*/
# ifndef COMMENT_H
# define COMMENT_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h> 
#include <ctype.h>


# define MAX_COMMENT_LENGTH 500
# define MAX_TAGS 10
# define MAX_TAG_LENGTH 50

typedef struct _Comment Comment;
typedef Comment* PtrToComment;
typedef PtrToComment CommentPosition;
typedef PtrToComment CommentList;

/*\struct _Comment
* @brief Estructura para almacenar los comentarios de un usuario
*/
struct _Comment {
	char Text[MAX_COMMENT_LENGTH];
	char GenreLikes[MAX_TAGS][MAX_TAG_LENGTH];
	char BandLikes[MAX_TAGS][MAX_TAG_LENGTH];
	int GenreCount;
    int BandCount;
    CommentPosition next;
};

//funciones para manejae lista enlazada
CommentList make_empty_comment_list(CommentList list);
CommentPosition create_comment_node(const char* text);
CommentPosition append_comment(CommentPosition prev, const char* text);
CommentList read_comments_from_file(CommentList list, const char* filename);
void delete_comment_list(CommentList list);
void print_comments(CommentList list);

//funciones para manejar tags
CommentList add_tags(CommentList comment);


#endif