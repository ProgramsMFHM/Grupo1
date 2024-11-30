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
#include "errors.h"
#include "userLink.h"
#include "genreLink.h"

UserTable get_users_from_file(const char *filePath, UserTable table);
UserPosition complete_user_from_json(UserPosition user);
UserLinkList read_friends_json(json_t *friends_json);
GenreLinkList read_genres_json(json_t *genres_json);

#endif