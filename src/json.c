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

    size_t total_users  = json_array_size(json);  // Tamano total de usuarios basado en el arreglo json

    // Leemos y procesamos cada uno de los usuarios
    for (size_t i = 0; i < total_users; i++) {
        json_t *user_json = json_array_get(json, i); // Obtiene el objeto json, basada en el usuario[i]

        // Lectura de campos basicos
        const char *userName = json_string_value(json_object_get(user_json, "userName")); // almacena el nombre del usuario[i]
        json_t *friends_json = json_object_get(user_json, "friends"); // almacena los amigos del usuario[i]
        UserLinkList friends = read_friends_json(friends_json);
        insert_userTable_node(table, userName, 0, "NULL", "NULL", NULL, NULL, friends, NULL);
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

    if(user->bands && user->friends && user->comments && user->genres && user->nationality && user->description){
        return user;
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
    int age = (int)json_integer_value(json_object_get(json, "age")); // 0 si no existe
    const char *nationality = json_string_value(json_object_get(json, "nationality"));
    if(!nationality){
        nationality = "Empty";
    }
    const char *description = json_string_value(json_object_get(json, "description"));
    if(!description){
        description = "Empty";
    }

    json_t *genres_json = json_object_get(json, "genres"); // almacena los generos del usuario
    GenreLinkList genres = read_genres_json(genres_json);

    json_t *bands_json = json_object_get(json, "bands"); // almacena las bandas del usuario
    BandLinkList bands = read_band_json(bands_json);

    json_t *comments_json = json_object_get(json, "comments"); // almacena los comentarios del usuario
    CommentLinkList comments = read_comments_json(comments_json);

    complete_userList_node(user, age, nationality, description, genres, bands, comments);

    json_decref(json); // libera la memoria utilizada por el json
    return user;
}

/**
 * @brief Funcion para completar un comentario leido desde un archivo json
 *
 * @param user Puntero al comentario a completar
 * @return Puntero al comentario completado
*/
CommentPosition complete_comment_from_json(CommentPosition comment)
{
    if(comment == NULL){
        print_error(202, NULL, NULL);
    }

    // Crear estructura JSON
    char filePath[200];
    snprintf(filePath, 200, COMMENTS_PATH"%ld.json", comment->ID);
    FILE *file = fopen(filePath, "r");  // Abre el archivo .json en modo lectura
    if (!file){
        print_error(100, (char*)filePath, NULL);
        return comment;
    }
    json_error_t error;     // declaracion de "variable" error basada en una funcion de la libreria jansson
    json_t *json = json_loadf(file, 0, &error); //<  puntero en el cual se guarda el archivo .json
    fclose(file);
    if (!json) {
        print_error(101, error.text, NULL);
        return comment;
    }
    const char *text = json_string_value(json_object_get(json, "text")); // almacena el texto del comentario[i]
    if(!text){
        text = "Empty";
    }
    const char *author = json_string_value(json_object_get(json, "author")); // almacena el autor del comentario[i]
    if(!author){
        author = "Empty";
    }

    complete_commentList_node(comment, (char*)text, (char*)author);

    json_decref(json); // libera la memoria utilizada por el json
    return comment;
}

/**
 * @brief Lee bandas de un archivo e inserta en una tabla de bandas
 * @param fileName Nombre del archivo a leer
 * @param bandTable Tabla de bandas donde insertar los bandas
 * @return Tabla de bandas con los bandas leidos
*/
BandTable get_bands_from_file(const char* filePath, BandTable table)
{
    if(table == NULL){
        table = create_bandTable(table);
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

    size_t total_bands;
    total_bands = json_array_size(json);  // Tamano total de bandas basado en el arreglo json

    // Leemos y procesamos cada una de las bandas
    for (size_t i = 0; i < total_bands; i++) {
        json_t *band_json = json_array_get(json, i); // Obtiene el objeto json, basado en la banda[i]

        // Lectura de campos basicos
        const char *band = json_string_value(json_object_get(band_json, "band")); // almacena el nombre de la banda[i]
        json_t *comments_json = json_object_get(band_json, "comments"); // almacena las bandas del usuario[i]
        CommentLinkList comments = read_comments_json(comments_json);
        BandPosition bandPosition = insert_bandTable_band((char*)band, table);
        delete_commentLinkList(bandPosition->comments);
        bandPosition->comments = comments;
    }
    json_decref(json); // libera la memoria utilizada por el json

    return table;
}

/**
 * @brief Lee generos de un archivo e inserta en una tabla de generos musicales
 * @param fileName Nombre del archivo a leer
 * @param bandTable Tabla de generos donde insertar los bandas
 * @return Tabla de generos con los generos leidos
*/
GenreTable get_genres_from_file(const char* filePath, GenreTable genreTable)
{
    if(genreTable == NULL){
        genreTable = create_genresTable(genreTable);
    }

    // Crear estructura JSON
    FILE *file = fopen(filePath, "r");  // Abre el archivo .json en modo lectura
    if (!file) {
        print_error(100, (char*)filePath, NULL);
        return genreTable;
    }
    json_error_t error;     // declaracion de "variable" error basada en una funcion de la libreria jansson
    json_t *json = json_loadf(file, 0, &error); //<  puntero en el cual se guarda el archivo .json
    fclose(file);
    if (!json) {
        print_error(101, error.text, NULL);
        return genreTable;
    }

    size_t total_genres = json_array_size(json);  // Tamano total de generos basado en el arreglo json

    // Leemos y procesamos cada uno de los generos
    for (size_t i = 0; i < total_genres; i++) {
        json_t *genre_json = json_array_get(json, i); // Obtiene el objeto json, basado en el genero[i]

        // Lectura de campos basicos
        const char *genre = json_string_value(json_object_get(genre_json, "genre")); // almacena el nombre del genero[i]
        json_t *comments_json = json_object_get(genre_json, "comments"); // almacena loc omentarios del genero[i]
        CommentLinkList comments = read_comments_json(comments_json);
        GenrePosition genrePosition = insert_genre((char*)genre, genreTable);
        delete_commentLinkList(genrePosition->comments);
        genrePosition->comments = comments;
    }
    json_decref(json); // libera la memoria utilizada por el json

    return genreTable;
}

/**
 * @brief Lee los comentarios de un archivo e inserta en una tabla de comentarios
 * @param fileName Nombre del archivo a leer
 * @param commentTable Tabla de comentarios donde insertar los comentarios leidos
 * @return Tabla de comentarios con los comentarios leidos
*/
CommentTable get_comments_from_file(const char* filePath, CommentTable commentTable)
{
    if(commentTable == NULL){
        commentTable = create_commentTable(commentTable);
    }

    // Crear estructura JSON
    FILE *file = fopen(filePath, "r");  // Abre el archivo .json en modo lectura
    if (!file) {
        print_error(100, (char*)filePath, NULL);
        return commentTable;
    }
    json_error_t error;     // declaracion de "variable" error basada en una funcion de la libreria jansson
    json_t *json = json_loadf(file, 0, &error); //<  puntero en el cual se guarda el archivo .json
    fclose(file);
    if (!json) {
        print_error(101, error.text, NULL);
        return commentTable;
    }

    size_t total_comments = json_array_size(json);  // Tamano total de comentarios basado en el arreglo json

    // Leemos y procesamos cada una de las bandas
    for (size_t i = 0; i < total_comments; i++) {
        time_t comment = json_integer_value(json_array_get(json, i));  // obtener el valor comentario en el indice i del arreglo
        if (!comment) {
            print_error(302, NULL, "ID de comentario no valido");
            continue;
        }
        insert_commentTable_comment(create_new_comment(comment, "NULL", "NULL"), commentTable);
    }
    json_decref(json); // libera la memoria utilizada por el json

    return commentTable;
}

/**
 * @brief Funcion para leer el arreglo json de amigos y crear una lista de enlaces a usuarios
 *
 * @param friends_json Puntero al arreglo json de amigos
 * @return Puntero a la lista de enlaces a usuarios creada
*/
UserLinkList read_friends_json(json_t *friends_json){
    UserLinkList friends = create_empty_userLinkList(NULL);
    if(friends_json == NULL){
        return friends;
    }

    size_t quantity = json_array_size(friends_json); //obtener el numero de elementos en el arreglo json

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
    GenreLinkList genres = create_empty_genreLinkList(NULL);
    if(genres_json == NULL){
        return genres;
    }

    size_t quantity = json_array_size(genres_json); //obtener el numero de elementos en el arreglo json

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
 * @param bands_json Puntero al arreglo json de bandas
 * @return Puntero a la lista de enlaces a bandas creada
*/
BandLinkList read_band_json(json_t *bands_json){
    BandLinkList bands = create_empty_bandLinkList(NULL);

    if(bands_json == NULL){
        return bands;
    }

    size_t quantity = json_array_size(bands_json); //obtener el numero de elementos en el arreglo json

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

/**
 * @brief Funcion para leer el arreglo json de comentarios y crear una lista de comentarios
 *
 * @param comments_json Puntero al arreglo json de comentarios
 * @return Puntero a la lista de comentarios creada
*/
CommentLinkList read_comments_json(json_t *comments_json)
{
    CommentLinkList comments = create_empty_commentLinkList(NULL);
    if(comments_json == NULL){
        return comments;
    }

    size_t quantity = json_array_size(comments_json); //obtener el numero de elementos en el arreglo json

    for (size_t i = 0; i < quantity; i++) {
        time_t commentID = (time_t)json_integer_value(json_array_get(comments_json, i));  // obtener el valor del ID en el indice i del arreglo
        if (!commentID) {
            print_error(302, NULL, "ID de comentario no valido");
            continue;
        }
        insert_commentLinkList_node_basicInfo(comments, commentID);
    }
    return comments;
}