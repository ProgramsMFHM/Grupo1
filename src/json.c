/**
 * @file json.c
 * @author Constanza Araya, Rodolfo Cifuentes, Bruno Martinez, Milton Hernández, Guliana Ruiz
 * @brief Funciones para manejo de archivos json a lo largo de las diferentes necesidades de loopweb
*/
#include "json.h"

/**
 * @brief Funcion para leer un archivo json y almacenar los datos en una tabla de usuarios (Nombres y amigos)
 *
 * @param filename Ruta del archivo json
 * @param table Puntero a la tabla de usuarios a crear
 * @return Puntero a la tabla de usuarios creada
*/
UserTable get_users_from_file(const char *filePath, UserTable table)
{
    if(table == NULL){
        table = create_userTable(table);
    }

    // Crear estructura JSON
    FILE *file = fopen(filePath, "r");  // Abre el archivo .json en modo lectura
    if (!file) {
        print_error(100, (char*)filePath, NULL);
        return table;
    }
    json_error_t error;     // declaracion de "variable" error basada en una funcion de la libreria jansson
    json_t *json = json_loadf(file, 0, &error); //<  puntero en el cual se guarda el archivo .json
    fclose(file);
    if (!json) {
        print_error(101, error.text, NULL);
        return table;
    }

    size_t total_users;
    total_users = json_array_size(json);  // Tamano total de usuarios basado en el arreglo json

    // Leemos y procesamos cada uno de los usuarios
    for (size_t i = 0; i < total_users; i++) {
        json_t *user_json = json_array_get(json, i); // Obtiene el objeto json, basada en el usuario[i]

        // Lectura de campos basicos
        const char *userName = json_string_value(json_object_get(user_json, "userName")); // almacena el nombre del usuario[i]
        json_t *friends_json = json_object_get(user_json, "friends"); // almacena los amigos del usuario[i]
        UserLinkList friends = read_friends_json(friends_json);
        insert_userTable_node(table, userName, 0, "NULL", NULL, NULL, friends);
    }
    json_decref(json); // libera la memoria utilizada por el json

    return table;
}

/**
 * @brief Funcion para completar un usuario leido desde un archivo json
 *
 * @param user Puntero al usuario a completar
 * @return Puntero al usuario completado
*/
UserPosition complete_user_from_json(UserPosition user)
{
    if(user == NULL){
        print_error(202, NULL, NULL);
    }

    // Crear estructura JSON
    char filePath[200];
    snprintf(filePath, 200, USERS_PATH"%s.json", user->username);
    FILE *file = fopen(filePath, "r");  // Abre el archivo .json en modo lectura
    if (!file){
        print_error(100, (char*)filePath, NULL);
        return user;
    }
    json_error_t error;     // declaracion de "variable" error basada en una funcion de la libreria jansson
    json_t *json = json_loadf(file, 0, &error); //<  puntero en el cual se guarda el archivo .json
    fclose(file);
    if (!json) {
        print_error(101, error.text, NULL);
        return user;
    }
    int age = (int)json_integer_value(json_object_get(json, "age"));
    const char *nationality = json_string_value(json_object_get(json, "nationality"));

    json_t *genres_json = json_object_get(json, "genres"); // almacena los generos del usuario
    GenreLinkList genres = read_genres_json(genres_json);

    json_t *bands_json = json_object_get(json, "artists"); // almacena las bandas del usuario
    BandLinkList bands = read_band_json(bands_json);

    complete_userList_node(user, age, nationality, genres, bands);

    json_decref(json); // libera la memoria utilizada por el json
    return user;
}

/**
 * @brief Funcion para leer el arreglo json de amigos y crear una lista de enlaces a usuarios
 *
 * @param friends_json Puntero al arreglo json de amigos
 * @return Puntero a la lista de enlaces a usuarios creada
*/
UserLinkList read_friends_json(json_t *friends_json){
    if(friends_json == NULL){
        return NULL;
    }

    size_t quantity = json_array_size(friends_json); //obtener el numero de elementos en el arreglo json
    UserLinkList friends = create_empty_userLinkList(NULL);

    for (size_t i = 0; i < quantity; i++) {
        char *friendName = (char*)json_string_value(json_array_get(friends_json, i));  // obtener el valor del string en el indice i del arreglo
        if (!friendName) {
            print_error(302, NULL, "Nombre del amigo no valido");
            continue;
        }
        insert_userLinkList_node_basicInfo(friends, friendName);
    }
    return friends;
}

/**
 * @brief Funcion para leer el arreglo json de generos y crear una lista de enlaces a generos
 *
 * @param genres_json Puntero al arreglo json de generos
 * @return Puntero a la lista de enlaces a generos creada
*/
GenreLinkList read_genres_json(json_t *genres_json){
    if(genres_json == NULL){
        return NULL;
    }

    size_t quantity = json_array_size(genres_json); //obtener el numero de elementos en el arreglo json
    GenreLinkList genres = create_empty_genreLinkList(NULL);

    for (size_t i = 0; i < quantity; i++) {
        char *genreName = (char*)json_string_value(json_array_get(genres_json, i));  // obtener el valor del string en el indice i del arreglo
        if (!genreName) {
            print_error(302, NULL, "Nombre del genero no valido");
            continue;
        }
        insert_genreLinkList_node_basicInfo(genres, genreName);
    }
    return genres;
}

/**
 * @brief Funcion para leer el arreglo json de bandas y crear una lista de enlaces a bandas
 *
 * @param genres_json Puntero al arreglo json de bandas
 * @return Puntero a la lista de enlaces a bandas creada
*/
BandLinkList read_band_json(json_t *bands_json){
    if(bands_json == NULL){
        return NULL;
    }

    size_t quantity = json_array_size(bands_json); //obtener el numero de elementos en el arreglo json
    BandLinkList bands = create_empty_bandLinkList(NULL);

    for (size_t i = 0; i < quantity; i++) {
        char *bandName = (char*)json_string_value(json_array_get(bands_json, i));  // obtener el valor del string en el indice i del arreglo
        if (!bandName) {
            print_error(302, NULL, "Nombre de la banda no valido");
            continue;
        }
        insert_bandLinkList_node_basicInfo(bands, bandName);
    }
    return bands;
}