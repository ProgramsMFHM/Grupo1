/**
 * @file json.c
 * @author Constanza Araya, Rodolfo Cifuentes, Bruno Martinez, Milton Hernández, Guliana Ruiz
 * @brief Funciones para manejo de archivos json a lo largo de las diferentes necesidades de loopweb
*/
#include "json.h"

/**
 * @brief Funcion para leer un arreglo de strings .json y almacenarlos en una matriz
 *
 * @param array_json  objeto json del tipo arreglo  que contiene los valores se van a leer
 * @param matriz  donde se acumularan los valores leidos del arreglo
 * @return cantidad de elementos leidos
 */
int read_list_json(json_t *array_json, char matriz[MAX_ELEMENTS][MAX_CADENA]) {
    size_t cantidad = json_array_size(array_json);/**<obtener el numero de elementos en el arreglo json*/
    if (cantidad > MAX_ELEMENTS) {/**< verificar que no supere la cantidad permitida*/
        printf("max elementos superado\n");
        cantidad = MAX_ELEMENTS;
    }

    for (size_t i = 0; i < cantidad; i++) {
        const char *valor = json_string_value(json_array_get(array_json, i));  /**< obtener el valor del string en el indice i de la matriz*/
        if (!valor) {
            printf("Elemento no valido en indice %zu.\n", i);
            return 0;
        }
        snprintf(matriz[i], MAX_CADENA, "%s", valor); /**<copia el valor del string donde corresponda en la matriz */
    }
    return (int)cantidad;
}

/**
 * @brief Funcion para leer el archivo json, en este caso usuarios.json
 *
 * @param nombre_archivo  archivo .json a leer
 * @param usuarios  usuario de la estructura antes creada en el que se guardaran los datos obtenidos
 * @param total_users  puntero a un entero en el que se guardara el numero total de usuarios leidos en el .json
 * @return int
 */
int read_archive_json(const char *nombre_archivo, User usuarios[], int *total_users) {
    FILE *archivo = fopen(nombre_archivo, "r");  /**< Abre el archivo .json en modo lectura */
    if (!archivo) {
        perror("No se pudo abrir el archivo JSON");
        return 1;
    }
    json_error_t error;     /**< declaracion de "variable" error basada en una funcion de la libreria jansson */
    json_t *json = json_loadf(archivo, 0, &error); /**<  puntero en el cual se guarda el archivo .json*/
    fclose(archivo);

    if (!json) {
        printf("Error al analizar el .json: %s\n", error.text);
        return 1;
    }

    *total_users = (int)json_array_size(json);  /**<  tamano total de usuarios basado en el arreglo json, utilizando una funcion de la libreria jansson*/
    for (int i = 0; i < *total_users; i++) {
        json_t *usuario_json = json_array_get(json, i); /**< Obtiene el objeto json, basada en el usuario[i] */

        /**<  Lectura de campos basicos*/
        const char *name = json_string_value(json_object_get(usuario_json, "nombre"));  /**<  almacena el nombre del usuario[i]*/
        json_int_t age = json_integer_value(json_object_get(usuario_json, "edad"));     /**<  almacena la edad del usuario[i]*/
        const char *nationality = json_string_value(json_object_get(usuario_json, "nacionalidad"));  /**< almacena la nacionalidad del usuario[i] */
        json_t *gustos_json = json_object_get(usuario_json, "gustos");  /**< almacena los gustos del usuario[i] */
        json_t *bands_json = json_object_get(usuario_json, "bandas");   /**< almacena las bandas del usuario[i] */
        json_t *friends_json = json_object_get(usuario_json, "amigos"); /**< almacena los amigos del usuario[i] */

        snprintf(usuarios[i].name, sizeof(usuarios[i].name), "%s", name);  /**<  copia el nombre a la estructura user*/
        usuarios[i].age = (int)age;                                        /**<  copia la edad a la estructura user*/
        snprintf(usuarios[i].nationality, sizeof(usuarios[i].nationality), "%s", nationality);   /**< copia la nacionalidad a la estructura user */

       /**< Lee y almacena las listas de gustos, bandas, amigos en la estructura user */
        read_list_json(gustos_json, usuarios[i].gustos);
        read_list_json(bands_json, usuarios[i].bands);
        read_list_json(friends_json, usuarios[i].friends);
    }

    json_decref(json); /**< libera la memoria utilizada por el json, funcion de la libreria jansson */
    return 0;
}