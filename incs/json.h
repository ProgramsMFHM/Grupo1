/**
 * @file json.h
 * @author Constanza Araya, Rodolfo Cifuentes, Bruno Martinez, Milton Hernández, Guliana Ruiz
 * @brief Cabeceras para funciones de json.c
*/

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <jansson.h>
#include <stdio.h>
#include <string.h>
#include "time.h"
#include "errors.h"
#include "userLink.h"
#include "genreLink.h"
#include "bandLink.h"

UserTable get_users_from_file(const char *filePath, UserTable table);
BandTable get_bands_from_file(const char* filePath, BandTable table);
GenreTable get_genres_from_file(const char* filePath, GenreTable genreTable);
CommentTable get_comments_from_file(const char* filePath, CommentTable commentTable);
UserPosition complete_user_from_json(UserPosition user);
CommentPosition complete_comment_from_json(CommentPosition comment);
UserLinkList read_friends_json(json_t *friends_json);
GenreLinkList read_genres_json(json_t *genres_json);
BandLinkList read_band_json(json_t *comments_json);
CommentList read_comments_json(json_t *comments_json);

#endif