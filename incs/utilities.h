/**
 * @file utilities.h
 * @author Constanza Araya, Rodolfo Cifuentes, Bruno Martinez, Milton Hernández, Guliana Ruiz
 * @brief Cabecera para funciones de utilities.c
*/
#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "errors.h"


// Colores para texto
#define CLEAR_SCREEN "\033[H\033[J"
#define ANSI_COLOR_RED      "\x1b[31m"
#define ANSI_COLOR_GREEN    "\x1b[32m"
#define ANSI_COLOR_YELLOW   "\x1b[33m"
#define ANSI_COLOR_BLUE     "\x1b[34m"
#define ANSI_COLOR_MAGENTA  "\x1b[35m"
#define ANSI_COLOR_CYAN     "\x1b[36m"
#define ANSI_COLOR_RESET    "\x1b[0m"


// Para cadenas de caracteres
void to_low_case(char* s1);
void remove_punctuation(char* s1);
char* get_only_fileName(char* file);
bool is_valid_extension(char* extension);
void print_loopweb(char* str);

// Funciones para usar como parametros
bool increasing(double a, double b);
bool decreasing(double a, double b);

// Funciones para mostrar publicacion 
void printf_loopweb();

#endif