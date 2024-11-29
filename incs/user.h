/**
 * @file user.h
 * @author Constanza Araya, Rodolfo Cifuentes, Bruno Martinez, Milton Hernández, Guliana Ruiz
 * @brief Cabeceras para funciones de user.c
*/
#ifndef USER_H
#define USER_H

#define USERS_PATH "./build/users/"

typedef struct _userNode UserNode;
typedef UserNode* PtrToUser;
typedef PtrToUser UserPosition;
typedef PtrToUser UserList;
typedef struct _userTable* UserTable;

#define USER_TABLE_SIZE 20 /**< Tamaño de la tabla hash de usuarios */
#include <stdlib.h>
#include <string.h>
#include "errors.h"
#include "hash.h"
#include "userLink.h"

/** \struct _userNode
 * @brief Estructura que representa un nodo de usuario.
*/
struct _userNode {
    char* username;               /**< Nombre del usuario */
    int age;                         /**< Edad del usuario */
    char* nationality;            /**< Nacionalidad del usuario */
    char* musicTaste;             /**< Gusto musical del usuario */
    UserLinkList friends;            /**< Lista de enlaces a usuarios que son amigos de este usuario */
    PtrToUser next;          /**< Puntero al siguiente nodo de la lista enlazada */
};

/** \struct _userUserTable
 * @brief Estructura que representa la tabla hash de usuarios.
*/
struct _userTable {
    UserList buckets[USER_TABLE_SIZE];   /**< Arreglo de punteros a listas enlazadas de usuarios */
    int userCount;                       /**< Contador de usuarios */
    bool modified;                       /**< Indica si la tabla ha sido modificada desde que se cargo */
};

// Funciones de la lista de usuarios
UserList create_empty_UserList(UserList userList);
void delete_UserList(UserList userList);
bool is_empty_UserList(UserList userList);
void print_UserList(UserList userList);
UserPosition find_UserList_node(UserList userList, const char *name);
UserPosition find_UserList_prev_node(UserPosition P, UserList userList);
UserPosition createNewUser(const char *username, int age, const char *nationality, const char *musicTaste, UserLinkList friends);
UserPosition insert_UserList_node(UserPosition prevPosition, UserPosition newNode);
UserPosition complete_userList_node(UserPosition P, int age, const char *nationality, const char *musicTaste);
UserPosition complet_userList_node(UserPosition P, int age, const char *nationality, const char *musicTaste);
bool delete_UserList_node(UserPosition P, UserList userList);


// Funciones de interaccion con el usuario
UserPosition userList_first(UserList userList);
UserPosition userList_last(UserList userList);
UserPosition userList_advance(UserPosition P);
char *get_username(UserPosition P);

// Funciones de la tabla de usuarios
UserTable create_userTable(UserTable table);
void delete_userTable(UserTable table);
UserPosition insert_userTable_node(UserTable table, const char *username, int age, const char *nationality, const char *musicTaste, UserLinkList friends);
UserPosition find_userTable_node(UserTable table, const char *username);
void delete_userTable_node(UserTable table, const char* username);
void print_userTable(UserTable table);

#endif