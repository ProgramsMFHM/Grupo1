/**
 * @file errors.c
 * @author Constanza Araya, Rodolfo Cifuentes, Bruno Martinez, Milton Hernández, Guliana Ruiz
 * @brief Funciones para manejo de errores
*/
#include "errors.h"

/**
 * @brief Funcion para imprimir un error
 * @param num Codigo de error
 * @param target Algun parametro que puede ser necesario para el error
 * @param obs Algun texto que puede acompañar el error
*/
void print_error(int num, char* target, char* obs) {
    if(num>=100 && num<200){
        printf(ANSI_COLOR_RED "Error %d: " ANSI_COLOR_RESET, num);
    }
    else
    if(num>=200 && num<300){
        printf(ANSI_COLOR_RED "Fatal Error %d: " ANSI_COLOR_RESET, num);
    }
    else if(num>=300 && num<400){
        printf(ANSI_COLOR_YELLOW "Warning %d: " ANSI_COLOR_RESET, num);
    }
    switch(num) {
        case 100:
            printf("No se pudo leer el archivo %s\n", target);
            break;
        case 101:
            printf("Error al leer el archivo JSON: %s\n", target);
            break;
        case 102:
            printf("Error al transformar fecha\n");
            break;
        case 103:
            printf("Error al leer entrada por terminal\n");
            break;
        case 200:
            printf("No hay memoria disponible\n");
            exit(-1);
            break;
        case 201:
            printf("No se pudo acceder al sistema\n");
            exit(-1);
            break;
        case 202:
            printf("Se intento acceder a un puntero nulo\n");
            exit(-1);
            break;
        case 300:
            printf("Usuario %s no encontrado\n", target);
            break;
        case 301:
            printf("Usuario ya presente en la tabla\n");
            break;
        case 302:
            printf("Error al leer campo JSON\n");
            break;
        case 303:
            printf("Comentario %s no encontrado\n", target);
            break;
        case 304:
            printf("Banda %s no encontrada\n", target);
            break;
        case 305:
            printf("Genero %s no encontrado\n", target);
            break;
        default:
            printf("Codigo de error desconocido\n");
    }
    if (obs != NULL) {
        printf("%s\n", obs);
    }
}