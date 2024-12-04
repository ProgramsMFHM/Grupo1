/**
 * @file userLink.h
 * @author Constanza Araya, Rodolfo Cifuentes, Bruno Martinez, Milton Hernández, Guliana Ruiz
 * @brief Cabeceras para funciones de userLink.c
*/

#ifndef USER_LINK_H
#define USER_LINK_H

typedef struct _userLinkNode UserLinkNode;
typedef UserLinkNode *PtrToUserLinkNode;
typedef PtrToUserLinkNode UserLinkPosition;
typedef PtrToUserLinkNode UserLinkList;

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include "errors.h"
#include "user.h"
#include "utilities.h"


/** \struct _userLinkNode
 * @brief Lista de enlaces a usuarios
*/
struct _userLinkNode {
    char* userName;        /*!< Nombre del usuario */
    double coefficient;    /*!< Coeficiente del nodo (usado en varias funciones) */
    PtrToUser userNode;    /*!< Usuario de la red */
    UserLinkPosition next; /*!< Posicion siguiente en la lista */
};

// Funciones para el manejo de una lista de enlaces a usuarios
UserLinkList create_empty_userLinkList(UserLinkList linkList);
void delete_userLinkList(UserLinkList linkList);
bool is_empty_userLinkList(UserLinkList linkList);
void print_userLinkList(UserLinkList linkList);
UserLinkPosition find_userLinkList_node(UserLinkList linkList, char* userName);
UserLinkPosition find_userLinkList_prev_node(UserLinkPosition P, UserLinkList linkList);
UserLinkPosition insert_userLinkList_node_basicInfo(UserLinkPosition prevPosition, char* userName);
UserLinkPosition insert_userLinkList_node_completeInfo(UserLinkPosition prevPosition, PtrToUser userNode);
void delete_userLinkList_node(UserLinkPosition P, UserLinkList linkList);

// Funciones de interaccion con el usuario
UserLinkPosition complete_userLinkList_node(UserLinkPosition P, UserTable userTable);
UserLinkPosition userLinkList_first(UserLinkList linkList);
UserLinkPosition userLinkList_last(UserLinkList linkList);
UserLinkPosition userLinkList_advance(UserLinkPosition P);

#endif