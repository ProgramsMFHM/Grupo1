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

#define MAX_USERS 100
#define MAX_ELEMENTS 10
#define MAX_CADENA 50

/**< estructura para almacenar los datos de cada usuario */
struct _user{
    char name[100];
    int age;
    char nationality[50];
    char gustos[MAX_ELEMENTS][MAX_CADENA];
    char bands[MAX_ELEMENTS][MAX_CADENA];
    char friends[MAX_ELEMENTS][MAX_CADENA];
};
typedef struct _user User;

int read_list_json(json_t *array_json, char matriz[MAX_ELEMENTS][MAX_CADENA]);
int read_archive_json(const char *nombre_archivo, User usuarios[], int *total_users);

#endif