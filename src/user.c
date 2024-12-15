/**
 * @file user.c
 * @author Constanza Araya, Rodolfo Cifuentes, Bruno Martinez, Milton Hernández, Guliana Ruiz
 * @brief Funciones para manejo de usuarios dentro de loopweb
*/
#include "user.h"

// Funciones para un nodo de usuario

/**
 * @brief Imprime un usuario en su archivo en formato JSON
 *
 * @param user Puntero al nodo de usuario
*/
void save_userNode(PtrToUser user){
    #ifdef DEBUG
        printf("Guardando usuario %s...\n", user->username);
        if(!user){
            printf("\tUsuario Nulo\n");
        }
        if (!user->username){
            printf("\tNombre de usuario nulo\n");
        }
        if (!user->nationality){
            printf("\tNacionalidad nula\n");
        }
        if (!user->description){
            printf("\tDescripcion nula\n");
        }
        if (!user->genres){
            printf("\tGustos musicales nulos\n");
        }
        if (!user->bands){
            printf("\tBandas nulas\n");
        }
        if (!user->friends){
            printf("\tAmigos nulos\n");
        }
        if (!user->comments){
            printf("\tComentarios nulos\n");
        }
    #endif
    if(user == NULL
        || user->username == NULL
        || user->nationality == NULL
        || user->description == NULL
        || user->genres == NULL
        || user->bands == NULL
        || user->friends == NULL
        || user->comments == NULL){
        print_error(202, NULL, NULL);
    }

    char filename[strlen(user->username) + strlen(USERS_PATH) + 5];
    sprintf(filename, USERS_PATH"%s.json", user->username);

    #ifdef DEBUG
        printf("Guardando usuario %s en el archivo %s\n", user->username, filename);
    #endif

    FILE *file = fopen(filename, "w");
    if(file == NULL){
        print_error(100, filename, NULL);
        return;
    }

    fprintf(file, "{\n");
    fprintf(file,"\t\"username\": \"%s\",\n", user->username);
    fprintf(file,"\t\"age\": %d,\n", user->age);
    fprintf(file,"\t\"nationality\": \"%s\",\n", user->nationality);
    fprintf(file,"\t\"description\": \"%s\",\n", user->description);

    // Gustos musicales de la lista de gustos musicales
    #ifdef DEBUG
        printf("Guardando gustos musicales de la lista de gustos musicales: \n");
        print_genreLinkList(user->genres);
        printf("\n");
    #endif
    fprintf(file,"\t\"genres\": [");
    GenreLinkPosition aux = user->genres->next;
    while (aux != NULL) {
        fprintf(file,"\"%s\"", aux->genre);
        if (aux->next != NULL) {
            fprintf(file,", ");
        }
        aux = aux->next;
    }
    fprintf(file,"],\n");

    // Bandas de la lista de bandas
    #ifdef DEBUG
        printf("Guardando bandas de la lista de bandas: \n");
        print_bandLinkList(user->bands);
        printf("\n");
    #endif
    fprintf(file,"\t\"bands\": [");
    BandLinkPosition aux2 = user->bands->next;
    while (aux2 != NULL) {
        fprintf(file,"\"%s\"", aux2->band);
        if (aux2->next != NULL) {
            fprintf(file,", ");
        }
        aux2 = aux2->next;
    }
    fprintf(file,"],\n");

    // Comentarios de la lista de comentarios
    #ifdef DEBUG
        printf("Guardando comentarios de la lista de comentarios: \n");
        print_commentLinkList(user->comments);
        printf("\n");
    #endif
    fprintf(file,"\t\"comments\": [");
    CommentLinkPosition aux3 = user->comments->next;
    while (aux3 != NULL) {
        fprintf(file,"%ld", aux3->commentID);
        if (aux3->next != NULL) {
            fprintf(file,", ");
        }
        aux3 = aux3->next;
    }
    fprintf(file,"],\n");

    // Amigos de la lista de amigos
    #ifdef DEBUG
        printf("Guardando amigos de la lista de amigos: \n");
        print_userLinkList(user->friends);
        printf("\n");
    #endif
    fprintf(file,"\t\"friends\": [");
    UserLinkPosition aux4 = user->friends->next;
    while (aux4 != NULL) {
        fprintf(file,"\"%s\"", aux4->userName);
        if (aux4->next != NULL) {
            fprintf(file,", ");
        }
        aux4 = aux4->next;
    }
    fprintf(file,"]\n");

    fprintf(file,"}\n");

    fclose(file);
}

/**
 * @brief Imprime el perfil completo de un usuario por terminal
 *
 * @param user Nodo de usuario a imprimir
*/
void print_user(UserPosition user)
{
    complete_user_from_json(user);
    if (user == NULL) {
        printf("\n** Error: Usuario no encontrado **\n");
        return;
    }

    // Imprimir la información general del usuario con color
    printf(ANSI_COLOR_CYAN"+----------------------+\n");
    printf(ANSI_COLOR_CYAN"|                      |\n");
    printf(ANSI_COLOR_CYAN"|"ANSI_COLOR_RESET"        ******        "ANSI_COLOR_CYAN"|   Nombre: "ANSI_COLOR_RESET"%s\n", user->username);
    printf(ANSI_COLOR_CYAN"|"ANSI_COLOR_RESET"       ********       "ANSI_COLOR_CYAN"|\n");
    printf("|"ANSI_COLOR_RESET"      **********      "ANSI_COLOR_CYAN"|\n");
    printf("|"ANSI_COLOR_RESET"      **********      "ANSI_COLOR_CYAN"|   Edad: "ANSI_COLOR_RESET"%d\n", user->age);
    printf(ANSI_COLOR_CYAN"|"ANSI_COLOR_RESET"       ********       "ANSI_COLOR_CYAN"|\n");
    printf("|"ANSI_COLOR_RESET"        ******        "ANSI_COLOR_CYAN"|\n");
    printf("|"ANSI_COLOR_RESET"    **************    "ANSI_COLOR_CYAN"|   Nacionalidad: "ANSI_COLOR_RESET"%s\n", user->nationality);
    printf(ANSI_COLOR_CYAN"|"ANSI_COLOR_RESET"  ******************  "ANSI_COLOR_CYAN"|\n");
    printf("|"ANSI_COLOR_RESET"  ******************  "ANSI_COLOR_CYAN"|\n");
    printf("+----------------------+\n"ANSI_COLOR_RESET);

    // Imprime la descripción utilizando la función printf_loopweb
    print_loopweb(user->description); printf("\n");

    // Imprime los géneros musicales favoritos
    printf(ANSI_COLOR_CYAN"\nMis géneros favoritos:\n"ANSI_COLOR_RESET);
    GenreLinkList genres = user->genres;
    if (genres != NULL && genres->next != NULL) {
        genres = genres->next; // Avanzamos al primer nodo real
        while (genres != NULL) {
            printf(ANSI_COLOR_RESET "  - %s" ANSI_COLOR_RESET, genres->genre);
            if (genres->next != NULL) {
                printf("\n");
            }
            genres = genres->next;
        }
        printf("\n");
    } else {
        printf("  No tengo generos favoritos.\n");
    }

    // Imprime las bandas favoritas
    printf(ANSI_COLOR_CYAN"\nMis bandas favoritas:\n"ANSI_COLOR_RESET);
    BandLinkList bands = user->bands;
    if (bands != NULL && bands->next != NULL) {
        bands = bands->next; // Avanzamos al primer nodo real
        while (bands != NULL) {
            printf(ANSI_COLOR_RESET "  - %s" ANSI_COLOR_RESET, bands->band);
            if (bands->next != NULL) {
                printf("\n");
            }
            bands = bands->next;
        }
        printf("\n");
    } else {
        printf("  No tengo bandas favoritas.\n");
    }

    // Imprime los amigos del usuario
    printf(ANSI_COLOR_CYAN"\nMis amigos:\n"ANSI_COLOR_RESET);
    UserLinkList friends = user->friends;
    if (friends != NULL && friends->next != NULL) {
        friends = friends->next; // Avanzamos al primer nodo real
        while (friends != NULL) {
            printf(ANSI_COLOR_RESET "  - %s" ANSI_COLOR_RESET, friends->userName);
            if (friends->next != NULL) {
                printf("\n");
            }
            friends = friends->next;
        }
        printf("\n");
    } else {
        printf("  No tengo amigos.\n");
    }
    printf("\n");
}

/**
 * @brief Obtiene los comentarios relevantes para un usuario (todos aquellos que tienen enlazados a sus bandas o generos)
 *
 * @param user Puntero al nodo de usuario
 * @param bandTable Tabla de bandas
 * @param genreTable Tabla de generos
 * @param commentTable Tabla de comentarios
 * @return Lista de comentarios
 */
CommentLinkList get_user_feed(UserPosition user, BandTable bandTable, GenreTable genreTable, CommentTable commentTable)
{
    complete_user_from_json(user);
    BandLinkPosition auxBand = user->bands->next;
    GenreLinkPosition auxGenre = user->genres->next;
    CommentLinkList feedComments = create_empty_commentLinkList(NULL);
    CommentLinkPosition auxComment;

    // Obtener los comentarios de los bandas del usuario
    while(auxBand != NULL){
        #ifdef DEBUG
            printf("Procesando banda: %s\n", auxBand->band);
        #endif
        BandPosition bandNode = find_bandTable_band(auxBand->band, bandTable);
        if(!bandNode){
            print_error(304, auxBand->band, NULL);
            auxBand = auxBand->next;
            continue;
        }
        auxComment = bandNode->comments->next;
        while(auxComment != NULL)
        {
            CommentPosition commentNode = find_commentTable_comment(auxComment->commentID, commentTable);
            insert_commentLinkList_node_completeInfo(feedComments, commentNode);
            auxComment = auxComment->next;
        }
        auxBand = auxBand->next;
    }

    // Obtener los comentarios de los bandas del usuario
    while(auxGenre != NULL){
        #ifdef DEBUG
            printf("Procesando genero: %s\n", auxGenre->genre);
        #endif
        GenrePosition genreNode = find_genresTable_genre(auxGenre->genre, genreTable);
        if(!genreNode){
            print_error(305, auxGenre->genre, NULL);
            auxGenre = auxGenre->next;
            continue;
        }
        auxComment = genreNode->comments->next;
        while(auxComment != NULL)
        {
            CommentPosition commentNode = find_commentTable_comment(auxComment->commentID, commentTable);
            if(!find_commentLinkList_node(feedComments, auxComment->commentID)){
                insert_commentLinkList_node_completeInfo(feedComments, commentNode);
            }
            auxComment = auxComment->next;
        }
        auxGenre = auxGenre->next;
    }

    if(feedComments->next == NULL){ // Si no hay comentarios el feed seran todos los comentarios del programa
        for(int i=0; i<COMMENTS_TABLE_SIZE; i++){
            CommentPosition aux = commentTable->buckets[i]->next;
            while(aux != NULL){
                printf("Procesando comentario %ld\n", aux->ID);
                insert_commentLinkList_node_basicInfo(feedComments, aux->ID);
                aux = aux->next;
            }
        }
    }
    return feedComments;
}

/**
 * @brief Imprime el feed de publicaciones de un usuario (Los comentarios que tiene enlazados a sus bandas o generos)
 *
 * @param user Puntero al nodo de usuario
 * @param bandTable Puntero a la tabla de bandas
 * @param genreTable Puntero a la tabla de generos
 * @param commentTable Puntero a la tabla de comentarios
*/
void print_user_feed(UserPosition user, BandTable bandTable, GenreTable genreTable, CommentTable commentTable)
{
    CommentLinkList feedComments = get_user_feed(user, bandTable, genreTable, commentTable);
    sort_commentLinkList_byID(&feedComments->next);
    CommentLinkPosition aux = feedComments->next;
    #ifdef DEBUG
        sleep(1);
    #endif
    printf(CLEAR_SCREEN"Feed de publicaciones para "ANSI_COLOR_CYAN"%s"ANSI_COLOR_RESET":\n", user->username);
    printf("\n");

    while (aux != NULL) {
        complete_commentLinkList_node(aux, commentTable);
        complete_comment_from_json(aux->commentNode);
        print_commentNode(aux->commentNode);
        aux = aux->next;
    }

    delete_commentLinkList(feedComments);
}

// Funciones de la lista de usuarios
/**
 * @brief Crea una lista vacia de usuarios
 *
 * @param userList Puntero a una lista de usuarios a vaciar, si es necesario
 * @return Puntero al nodo centinela de la lista
*/
UserList create_empty_UserList(UserList userList){
    if(!is_empty_UserList(userList)){
        delete_UserList(userList);
    }
    UserList newList = (UserList) malloc(sizeof(struct _userNode));
    if(newList == NULL){
        print_error(200, NULL, NULL);
    }
    newList->next = NULL;
    return newList;
}

/**
 * @brief Borra una lista de usuarios
 *
 * @param userList Puntero a la lista de usuarios a borrar
*/
void delete_UserList(UserList userList){
    if(is_empty_UserList(userList)){
        return;
    }
    UserPosition aux = userList_first(userList);
    while(aux != NULL){
        delete_UserList_node(aux, userList);
        aux = userList_first(userList);
    }
    free(userList);
}

/**
 * @brief Verifica si una lista de usuarios esta vacia
 *
 * @param userList Puntero a la lista de usuarios
 * @return true si la lista esta vacia, false en caso contrario
*/
bool is_empty_UserList(UserList userList){
    return userList == NULL;
}

/**
 * @brief Imprime una lista de usuarios en la consola
 *
 * @param userList Puntero a la lista de usuarios
*/
void print_UserList(UserList userList){
    UserPosition current = userList->next;
    if (current == NULL) {
        printf("Empty\n");
    } else {
        while (current != NULL) {
            printf("[%s, %d, %s, ", current->username, current->age, current->nationality);
            print_genreLinkList(current->genres);
            printf(", ");
            print_bandLinkList(current->bands);
            printf(", ");
            print_commentLinkList(current->comments);
            printf(", ");
            print_userLinkList(current->friends);
            printf("]\n\t-> ");
            current = current->next;
        }
        printf("NULL\n");
    }
}

/**
 * @brief Busca un usuario en la lista de usuarios por su username
 *
 * @param userList Lista de usuarios
 * @param username Nombre del usuario a buscar
 * @return Puntero al nodo encontrado, NULL si no se encuentra
*/
UserPosition find_UserList_node(UserList userList, const char *username){
    if(is_empty_UserList(userList)){
        return NULL;
    }
    UserPosition P = userList_first(userList);
    while (P != NULL && strcmp(P->username, username) != 0) {
        P = P->next;
    }
    return P;
}

/**
 * @brief Encuentra el nodo anterior a un nodo dado en la lista de usuarios
 *
 * @param P Nodo del cual se busca el anterior
 * @param userList Puntero a la lista de usuarios
 * @return Puntero al nodo anterior a @p P
*/
UserPosition find_UserList_prev_node(UserPosition P, UserList userList){
    UserPosition aux = userList;
    while (aux != NULL && strcmp(aux->next->username, P->username) != 0){
        aux = aux->next;
    }
    return aux;
}

/**
 * @brief Crea el nodo correspondiente a un usuario
 *
 * @param username Nombre del usuario
 * @param age Edad del usuario
 * @param nationality Nacionalidad del usuario
 * @param genres0 Gustos musicales del usuario
 * @return Puntero al nodo creado
*/
UserPosition create_new_user(const char *username, int age, const char *nationality, const char *description, GenreLinkList genres, BandLinkList bands, UserLinkList friends, CommentLinkList comments){
    PtrToUser newUser = (PtrToUser) malloc(sizeof(UserNode));
    if (newUser == NULL) {
        print_error(200, NULL, NULL);
    }

    newUser->username = malloc(strlen(username) + 1);
    if(newUser->username == NULL){
        print_error(200, NULL, NULL);
    }
    strcpy(newUser->username, username);

    newUser->nationality = malloc(strlen(nationality) + 1);
    if(newUser->nationality == NULL){
        print_error(200, NULL, NULL);
    }
    strcpy(newUser->nationality, nationality);

    newUser->description = malloc(strlen(description) + 1);
    if(newUser->description == NULL){
        print_error(200, NULL, NULL);
    }
    strcpy(newUser->description, description);

    newUser->comments = comments;
    newUser->age = age;
    newUser->genres = genres;
    newUser->bands = bands;
    newUser->friends = friends;
    newUser->next = NULL;
    return newUser;
}

/**
 * @brief Inserta un nodo de usuario en una lista de usuarios
 *
 * @param prevPosition Puntero al nodo anterior al que se desea insertar
 * @param newNode Puntero al nodo a insertar
 * @return Puntero al nodo insertado
*/
UserPosition insert_UserList_node(UserPosition prevPosition, UserPosition newNode){
    newNode->next = prevPosition->next;
    prevPosition->next = newNode;
    return newNode;
}

/**
 * @brief Completa un nodo de una lista de usuarios
 *
 * @param P Puntero al nodo a completar
 * @param age Edad del usuario
 * @param nationality Nacionalidad del usuario
 * @param genres Gustos musicales del usuario
 * @return Puntero al nodo completado
*/
UserPosition complete_userList_node(UserPosition P, int age, const char *nationality, const char *description, GenreLinkList genres, BandLinkList bands, CommentLinkList comments){
    if(P == NULL){
        print_error(202, NULL, NULL);
    }
    P->age = age;

    P->nationality = (char*)realloc(P->nationality, strlen(nationality) + 1);
    strcpy(P->nationality, nationality);

    P->description = (char*)realloc(P->description, strlen(description) + 1);
    strcpy(P->description, description);

    P->comments = comments;
    P->genres = genres;
    P->bands = bands;
    return P;
}

/**
 * @brief Borra un nodo de una lista de usuarios
 *
 * @param P Puntero al nodo a borrar
 * @param userList Puntero a la lista de usuarios a la que pertenece @p P
 * @return true si el nodo fue borrado, false en caso contrario (si no existe)
*/
bool delete_UserList_node(UserPosition P, UserList userList){
    if(P == NULL){
        print_error(202, NULL, NULL);
    }
    UserPosition prevNode = find_UserList_prev_node(P, userList);
    if(prevNode == NULL){
        print_error(300, P->username, NULL);
        return false;
    }
    prevNode->next = P->next;
    delete_commentLinkList(P->comments);
    delete_userLinkList(P->friends);
    delete_genreLinkList(P->genres);
    delete_bandLinkList(P->bands);
    free(P->username);
    free(P->nationality);
    free(P->description);
    free(P);
    return true;
}

// Funciones de interaccion con el usuario
/**
 * @brief Obtiene el primer nodo de una lista de usuarios
 *
 * @param userList Puntero a la lista de usuarios
 * @return Puntero al primer usuario de la lista
*/
UserPosition userList_first(UserList userList){
    return userList->next;
}

/**
 * @brief Obtiene el ultimo nodo de una lista de usuarios
 *
 * @param userList Puntero a la lista de usuarios
 * @return Puntero al ultimo usuario de la lista
*/
UserPosition userList_last(UserList userList){
    UserPosition P = userList->next;
    while (P->next != NULL) {
        P = P->next;
    }
    return P;
}

/**
 * @brief Avanza al siguiente nodo en la lista de usuarios
 *
 * @param P Puntero al usuario actual
 * @return Puntero al siguiente usuario de la lista
*/
UserPosition userList_advance(UserPosition P){
    return P->next;
}

/**
 * @brief Obtiene el nombre de usuario usuario almacenado en un nodo
 *
 * @param P Nodo de usuario
 * @return Nombre de usuario
*/
char *get_username(UserPosition P){
    return P->username;
}

// Funciones de la tabla de usuarios

/**
 * @brief Crea una tabla de usuarios
 *
 * @param table Puntero a la tabla de usuarios a crear
*/
UserTable create_userTable(UserTable table){
    if(table != NULL){
        delete_userTable(table);
    }

    table = (UserTable)malloc(sizeof(struct _userTable));
    if(!table){
        print_error(200,NULL,NULL);
    }

    for(int i = 0; i < USER_TABLE_SIZE; i++)
    {
        table->buckets[i] = create_empty_UserList(NULL);
        table->userCount = 0;
        table->modified = false;
    }

    return table;
}

/**
 * @brief Borra una tabla de usuarios
 *
 * @param table Puntero a la tabla de usuarios a borrar
*/
void delete_userTable(UserTable table){
    for(int i = 0; i < USER_TABLE_SIZE; i++){
        delete_UserList(table->buckets[i]);
    }
    free(table);
}

/**
 * @brief Inserta un usuario en una tabla de usuarios
 *
 * @param table Puntero a la tabla de usuarios
 * @param username Nombre del usuario
 * @param age Edad del usuario
 * @param nationality Nacionalidad del usuario
 * @param genres Gustos musicales del usuario
 * @return Puntero al nodo insertado
*/
UserPosition insert_userTable_node(UserTable table, const char *username, int age, const char *nationality, const char *description, GenreLinkList genres, BandLinkList bands, UserLinkList friends, CommentLinkList comments){
    if(find_userTable_node(table, username) != NULL){
        print_error(301, NULL, NULL);
        return NULL;
    }

    unsigned int index = jenkins_hash((char*)username) % USER_TABLE_SIZE;

    PtrToUser newUser = create_new_user(username, age, nationality, description, genres, bands, friends, comments);
    if (!newUser) {
        print_error(200, NULL, NULL);
    }
    if(insert_UserList_node(table->buckets[index], newUser)){
        table->userCount++;
        table->modified = true;
    }

    return newUser;
}

/**
 * @brief Busca un usuario por nombre en una tabla de usuarios
 *
 * @param table Puntero a la tabla de usuarios
 * @param username Nombre del usuario a buscar
 * @return Puntero al nodo del usuario encontrado, NULL si no existe
*/
UserPosition find_userTable_node(UserTable table, const char *username){
    unsigned int index = jenkins_hash((char*)username) % USER_TABLE_SIZE;
    return find_UserList_node(table->buckets[index], username);
}

/**
 * @brief Borra un usuario dado su nombre de la tabla de usuarios
 *
 * @param table Puntero a la tabla de usuarios
 * @param username Nombre del usuario a borrar
*/
void delete_userTable_node(UserTable table, const char* username){
    unsigned int index = jenkins_hash((char*)username) % USER_TABLE_SIZE;
    if(delete_UserList_node(find_UserList_node(table->buckets[index], username), table->buckets[index])){
        table->userCount--;
        table->modified = true;
    }
}

/**
 * @brief Imprime la tabla de usuarios en la consola
 *
 * @param table Puntero a la tabla de usuarios
*/
void print_userTable(UserTable table){
    printf("Usuarios de la red (%d):\n", table->userCount);
    for(int i=0; i<USER_TABLE_SIZE; i++){
        printf("Bucket %2d: ", i);
        print_UserList(table->buckets[i]);
    }
}

/**
 * @brief Funcion para guardar una tabla de usuarios en su archivo JSON correspondiente
 *
 * @param userTable Tabla de usuarios a guardar
*/
void save_userTable(UserTable userTable)
{
    FILE* userTableFile = fopen(USERS_PATH"users.json", "w");
    if (userTableFile == NULL)
    {
        print_error(100, USERS_PATH"users.json", NULL);
        return;
    }

    bool first = true;
    fprintf(userTableFile, "[\n");
    for(int i=0; i<USER_TABLE_SIZE; i++)
    {
        if(!userTable->buckets[i]->next){
            continue;
        }
        if(!first){
            fprintf(userTableFile, ",\n");
        }
        else{
            first = false;
        }
        UserPosition aux = userTable->buckets[i]->next;
        while(aux != NULL){
            fprintf(userTableFile, "\t{\n\t\t\"userName\":\"%s\",\n\t\t\"friends\":[", aux->username);
            if(aux->friends->next){
                UserLinkPosition aux2 = aux->friends->next;
                while(aux2 != NULL){
                    fprintf(userTableFile, "\"%s\"", aux2->userName);
                    if(aux2->next != NULL){
                        fprintf(userTableFile, ", ");
                    }
                    aux2 = aux2->next;
                }
            }
            fprintf(userTableFile, "]\n\t}");
            if(aux->next != NULL){
                fprintf(userTableFile, ",\n");
            }
            aux = aux->next;
        }
    }
    fprintf(userTableFile, "\n]");
    fclose(userTableFile);
}


// Funciones de LoopWeb relacionadas a usuarios

/**
 * @brief Funcion que crea un comentario en loopweb partiendo de la interaccion con el usuario
 *
 * @param userName Nombre del usuario
 * @param userTable Tabla de usuarios
 * @param bandTable Tabla de bandas
 * @param genreTable Tabla de generos
*/
void make_comment(char* userName, UserTable userTable, BandTable bandTable, GenreTable genreTable, CommentTable comments)
{
    int option;
    UserPosition author = find_userTable_node(userTable, userName); // Guardamos el autor del comentario
    if(author == NULL){ // No deberia pasar, ya se ha comprobado antes
        print_error(300, userName, NULL);
        return;
    }
    author = complete_user_from_json(author);

    char commentText[MAX_COMMENT_LENGTH+1];
    do{
        // Limpiamos el buffer de entrada
        while (getchar() != '\n');

        printf("Escriba el comentario: ");
        if(fgets(commentText, sizeof(commentText), stdin) == NULL){
            print_error(102, NULL, NULL);
            continue;
        }

        // Elimina el salto de línea si es necesario
        size_t len = strlen(commentText);
        if (len > 0 && commentText[len - 1] == '\n') {
            commentText[len - 1] = '\0';
        }

        printf("El comentario a ingresar es: ");
        print_loopweb(commentText);
        printf("\nEsta seguro de ingresar el comentario? (0:si, 1:no): ");
        if(scanf("%d", &option) != 1){
            print_error(103, NULL, NULL);
            continue;
        }
    }while(option != 0);

    CommentPosition commentNode = create_new_comment(time(NULL), commentText, userName);
    insert_commentTable_comment(commentNode, comments);
    complete_comment_tags(commentNode);
    // Revisamos las bandas del comentario
    BandLinkList bandAux = commentNode->bands->next;
    while(bandAux != NULL){
        printf("Procesando: %s\n", bandAux->band);
        BandPosition bandPosition = find_bandTable_band(bandAux->band, bandTable);
        if(!bandPosition)
        {
            printf("La banda "ANSI_COLOR_GREEN"%s"ANSI_COLOR_RESET" no se encuentra en la base de datos, desea agregarla?: (0:Si, 1:No): ", bandAux->band);
            if(scanf("%d", &option) != 1){
                print_error(103, NULL, NULL);
                bandAux = bandAux->next;
                continue;
            }
            if(option == 0){
                bandPosition = insert_bandTable_band(bandAux->band, bandTable);
            }
        }
        insert_commentLinkList_node_completeInfo(bandPosition->comments, commentNode); // Se agrega el comentario a la banda correspondiente
        bandAux = bandAux->next;
    }

    // Revisamos los generos del comentario
    GenreLinkPosition genreAux = commentNode->genres->next;
    while(genreAux != NULL){
        printf("Procesando: %s\n", genreAux->genre);
        GenrePosition genrePosition = find_genresTable_genre(genreAux->genre, genreTable);
        if(!genrePosition)
        {
            printf("El genero "ANSI_COLOR_RED"%s"ANSI_COLOR_RESET" no se encuentra en la base de datos, desea agregarlo?: (0:Si, 1:No): ", genreAux->genre);
            if(scanf("%d", &option) != 1){
                print_error(103, NULL, NULL);
                genreAux = genreAux->next;
                continue;
            }
            if(option == 0){
                genrePosition = insert_genre(genreAux->genre, genreTable);
            }
        }
        insert_commentLinkList_node_completeInfo(genrePosition->comments, commentNode); // Se agrega el comentario a la banda correspondiente
        genreAux = genreAux->next;
    }

    // Guardamos los comentarios en donde corresponde
    save_commentNode(commentNode); // Se guarda en el archivo correspondiente
    insert_commentLinkList_node_completeInfo(author->comments, commentNode); // Se guarda en la lista de comentarios del autor
    save_userNode(author);
    save_bandTable(bandTable);
    save_genresTable(genreTable);
    save_commentTable(comments);

    sleep(1);
    printf(CLEAR_SCREEN"El siguiente comentario fue agregado a loopweb:\n\n");
    print_commentNode(commentNode);

}

/**
 * @brief Imprime de manera estetica la tabla de usuarios y devuelve la lista de enlaces a todos los usuarios
 *
 * @param table Puntero a la tabla de usuarios
 * @param print TRUE si se desea imprimir la lista de usuarios, FALSE en caso contrario
 * @return Puntero a la lista de enlaces a todos los usuarios de la red ordenados alfabeticamente
*/
UserLinkList get_loopweb_users(UserTable table, bool print)
{
    UserLinkList allUsers = create_empty_userLinkList(NULL);

    for(int i=0; i<USER_TABLE_SIZE; i++){
        UserPosition aux = table->buckets[i]->next;
        while(aux != NULL){
            insert_userLinkList_node_completeInfo(allUsers, aux);
            aux = aux->next;
        }
    }
    sort_userLinkList_byName(&allUsers->next);
    if(print){
        UserLinkPosition current = allUsers->next;
        int counter = 1;
        while (current != NULL) {
            printf("%3d. "ANSI_COLOR_CYAN"%-10s"ANSI_COLOR_RESET, counter, current->userName);
            if(counter % 5 == 0){
                printf("\n");
            }
            counter++;
            current = current->next;
        }
        printf("\n\n");
    }
    return allUsers;
}

/**
 * @brief Funcion que maneja la creacion de nuevas amistades de un usuario basado en una lista de recomendaciones PREVIAMENTE IMPRESA
 *
 * @param user Nodo de usuario a hacer amigos
 * @param possibleFriends Puntero a la lista de amigos recomendados
*/
void request_for_friendship(UserPosition user, UserLinkList possibleFriends, UserTable table)
{
    int noMoreFriends = 0, friendOption=0, counter = 1;
    UserLinkPosition aux;

    while(noMoreFriends == 0){
        counter = 1;
        printf("Desea hacerse amigo/a de alguno de los usuarios recomendados? Ingrese el numero que aparece junto al usuario deseado (0 para salir): ");
        if(scanf("%d", &friendOption) != 1){
            print_error(103, NULL, NULL);
            continue;
        }
        if(friendOption == 0){
            noMoreFriends = 1;
            break;
        }
        aux = possibleFriends->next;
        while(aux != NULL){
            if(counter == friendOption){
                if(find_userLinkList_node(user->friends, aux->userName)){
                    printf("Ya eres amigo/a de "ANSI_COLOR_CYAN"%s"ANSI_COLOR_RESET"\n", aux->userName);
                    counter++;
                    aux = aux->next;
                    continue;
                }
                // Evitamos errores por ausencia de punteros
                aux = complete_userLinkList_node(aux, table);
                aux->userNode = complete_user_from_json(aux->userNode);
                user = complete_user_from_json(user);

                // Generamos amistad
                insert_userLinkList_node_completeInfo(user->friends, aux->userNode);
                #ifdef DEBUG
                    printf("Lista de amigos de "ANSI_COLOR_CYAN"%s"ANSI_COLOR_RESET" actualizada:\n", user->username);
                    print_userLinkList(user->friends);
                    printf("\n");
                #endif
                save_userNode(user);
                insert_userLinkList_node_completeInfo(aux->userNode->friends, user);
                #ifdef DEBUG
                    printf("Lista de amigos de "ANSI_COLOR_CYAN"%s"ANSI_COLOR_RESET" actualizada:\n", aux->userNode->username);
                    print_userLinkList(aux->userNode->friends);
                    printf("\n");
                #endif
                save_userNode(aux->userNode);
                printf("Ahora eres amigo/a de "ANSI_COLOR_CYAN"%s"ANSI_COLOR_RESET"\n", aux->userNode->username);
                table->modified = true;
                break;
            }
            counter++;
            aux = aux->next;
        }
        if(aux == NULL){
            noMoreFriends = 1;
        }
    }
}

/**
 * @brief Interactua con un usuario para crear su perfil
 *
 * @param users Tabla de usuarios
 * @param bands Tabla de bandas
 * @param genres Tabla de generos
 * @param comments Tabla de comentarios
 * @return Puntero al usuario creado
*/
UserPosition create_user_profile(UserTable users, BandTable bands, GenreTable genres)
{
    char userName[21];
    int age;
    char nationality[50];
    char description[MAX_COMMENT_LENGTH+1];
    GenreLinkList genresList = create_empty_genreLinkList(NULL);
    char genreText[20];
    char bandText[20];
    BandLinkList bandsList = create_empty_bandLinkList(NULL);
    UserLinkList friendsList = create_empty_userLinkList(NULL);
    CommentLinkList commentsList = create_empty_commentLinkList(NULL);
    bool notValid = true;
    int option;
    size_t len;

    printf(CLEAR_SCREEN"Bienvenido al creador de perfiles de usuarios de LoopWeb!\n\n");

    // Nombre de usuario
    printf(CLEAR_SCREEN);
    do{
        printf("Ingrese su nombre de usuario: ");
        if(scanf("%s", userName) != 1){
            print_error(103, NULL, NULL);
            continue;
        }
        while (getchar() != '\n'); // Limpiamos el buffer de entrada

        len = strlen(userName);
        if (len > 0 && userName[len - 1] == '\n') {
            userName[len - 1] = '\0';
        }
        if(userName[0] >= 'A' && userName[0] <= 'Z' && len >= 3 && len <= 20){
            notValid = false;
        }

        if(notValid){
            printf("Nombre de usuario no válido, debe tener entre 3 y 20 caracteres y empezar por una letra mayuscula\n");
        }
        else{
            printf("Nombre ingresado: " ANSI_COLOR_CYAN"%s"ANSI_COLOR_RESET" desea continuar? (0:si, 1:no): ", userName);
            if(scanf("%d", &option) != 1){
                print_error(103, NULL, NULL);
                continue;
            }
            if(option != 0){ // Hubo un error al ingresar el nombre y el usuario quiere corregirlo
                notValid = true;
            }
            else if(find_userTable_node(users, userName) != NULL){ // El usuario ya existe
                printf("El usuario ya existe, intente con otro nombre\n");
                notValid = true;
            }
        }
    }while(notValid);

    notValid = true;
    // Edad
    printf(CLEAR_SCREEN);
    do{
        printf("Ingrese su edad: ");
        if(scanf("%d", &age) != 1){
            print_error(103, NULL, NULL);
            continue;
        }
        while (getchar() != '\n'); // Limpiamos el buffer de entrada

        if(age >= 18 && age <= 99){
            notValid = false;
        }

        if(notValid == true){
            printf("Edad no válida, debe ser entre 18 y 98\n");
        }
        else{
            printf("Edad ingresada: "ANSI_COLOR_MAGENTA"%d"ANSI_COLOR_RESET" desea continuar? (0:si, 1:no): ", age);
            if(scanf("%d", &option) != 1){
                print_error(103, NULL, NULL);
                continue;
            }
            if(option != 0){ // Hubo un error al ingresar la edad y el usuario quiere corregirlo
                notValid = true;
            }
        }
    }while(notValid);

    notValid = true;
    // Nacionalidad
    printf(CLEAR_SCREEN);
    do{
        printf("Ingrese su nacionalidad (Ej: Chile, Colombia, Canada, France, Spain, etc): ");
        if(scanf("%s", nationality) != 1){
            print_error(103, NULL, NULL);
            continue;
        }
        while (getchar() != '\n'); // Limpiamos el buffer de entrada

        len = strlen(nationality);
        if (len > 0 && nationality[len - 1] == '\n') {
            nationality[len - 1] = '\0';
        }
        if(nationality[0] >= 'A' && nationality[0] <= 'Z' && len >= 2 && len <= 50){
            notValid = false;
        }

        if(notValid){
            printf("Nacionalidad no válida, debe tener entre 2 y 50 caracteres y empezar por una letra mayuscula\n");
        }
        else{
            printf("Nacionalidad ingresada: "ANSI_COLOR_YELLOW"%s"ANSI_COLOR_RESET" desea continuar? (0:si, 1:no): ", nationality);
            if(scanf("%d", &option) != 1){
                print_error(103, NULL, NULL);
                continue;
            }
            if(option != 0){ // Hubo un error al ingresar la nacionalidad y el usuario quiere corregirlo
                notValid = true;
            }
        }
    }while(notValid);

    notValid = true;
    // Descripcion
    printf(CLEAR_SCREEN);
    do{
        printf("Ingrese una descripcion de su perfil: ");

        while (getchar() != '\n'); // Limpiamos el buffer de entrada
        if(fgets(description, sizeof(description), stdin) == NULL){
            print_error(103, NULL, NULL);
            continue;
        }

        // Elimina el '\n' si está presente
        size_t len = strlen(description);
        if (len > 0 && description[len - 1] == '\n') {
            description[len - 1] = '\0';
        }
        if(len >= 1 && len <= MAX_COMMENT_LENGTH){
            notValid = false;
        }

        if(notValid){
            printf("Descripcion no válida, debe tener entre 1 y %d caracteres\n", MAX_COMMENT_LENGTH);
        }
        else{
            printf("Descripcion ingresada: \"");
            print_loopweb(description);
            printf("\" desea continuar? (0:si, 1:no): ");
            if(scanf("%d", &option) != 1){
                print_error(103, NULL, NULL);
                continue;
            }
            if(option != 0){ // Hubo un error al ingresar la descripcion y el usuario quiere corregirlo
                notValid = true;
            }
        }
    }while(notValid);

    notValid = true;
    // Gustos musicales
    printf(CLEAR_SCREEN);
    printf("A continuacion, ingrese los gustos musicales de su perfil (Puede no estar en la lista): \n");
    GenreLinkList programGenreList = get_loopweb_genres(genres);
    GenrePosition genrePosition;
    do{
        printf("Genro: ");
        if(scanf("%s", genreText) != 1){
            print_error(103, NULL, NULL);
            continue;
        }
        while (getchar() != '\n'); // Limpiamos el buffer de entrada
        genrePosition = find_genresTable_genre(genreText, genres);
        if(genrePosition){
            insert_genreLinkList_node_completeInfo(genresList, genrePosition);
            notValid = false;
        }
        else{
            printf("El genero "ANSI_COLOR_RED"\"%s\""ANSI_COLOR_RESET" no existe, desea ingresarlo en la tabla de generos? (0:si, 1:no): ", genreText);
            if(scanf("%d", &option) != 1){
                print_error(103, NULL, NULL);
                continue;
            }
            if(option == 0){
                genrePosition = insert_genre(genreText, genres);
                insert_genreLinkList_node_completeInfo(genresList, genrePosition);
                notValid = false;
            }
        }

        if(notValid==false){
            printf("Desea ingresar otro genero? (0:si, 1:no): ");
            if(scanf("%d", &option) != 1){
                print_error(103, NULL, NULL);
                continue;
            }
            if(option == 0){ // El usuario desea ingresar otro genero
                notValid = true;
            }
        }
    }while(notValid);

    notValid = true;
    // Bandas
    printf(CLEAR_SCREEN);
    printf("A continuacion, ingrese las bandas de su perfil (Puede no estar en la lista): \n");
    BandLinkList programBandList = get_loopweb_bands(bands);
    BandPosition bandPosition;
    do{
        printf("Banda: ");
        if(scanf("%s", bandText) != 1){
            print_error(103, NULL, NULL);
            continue;
        }
        while (getchar() != '\n'); // Limpiamos el buffer de entrada
        bandPosition = find_bandTable_band(bandText, bands);
        if(bandPosition){
            insert_bandLinkList_node_completeInfo(bandsList, bandPosition);
            notValid = false;
        }
        else{
            printf("La banda "ANSI_COLOR_GREEN"\"%s\""ANSI_COLOR_RESET" no existe, desea ingresarla en la tabla de bandas? (0:si, 1:no): ", bandText);
            if(scanf("%d", &option) != 1){
                print_error(103, NULL, NULL);
                continue;
            }
            if(option == 0){
                bandPosition = insert_bandTable_band(bandText, bands);
                insert_bandLinkList_node_completeInfo(bandsList, bandPosition);
                notValid = false;
            }
        }

        if(notValid == false){
            printf("Desea ingresar otra banda? (0:si, 1:no): ");
            if(scanf("%d", &option) != 1){
                print_error(103, NULL, NULL);
                continue;
            }
            if(option == 0){ // El usuario desea ingresar otra banda
                notValid = true;
            }
        }
    }while(notValid);

    // Creamos el nodo con toda la informacion
    UserPosition user = insert_userTable_node(users, userName, age, nationality, description, genresList, bandsList, friendsList, commentsList);

    printf(CLEAR_SCREEN);
    print_user(user);

    // Damos la posibilidad de tener amigos
    UserLinkList possibleFriends = find_possible_friends(user, users);
    UserLinkPosition aux = possibleFriends->next;
    while(aux != NULL){
        complete_userLinkList_node(aux, users);
        if(aux == NULL){
            continue;
        }
        complete_user_from_json(aux->userNode);
        /* Se calcula el coeficiente para cada usuario como sigue:
            - Un 20% del valor dado por la diferencia de edades
            - Un 40% del valor dado por el indice de Jaccard entre los generos de ambos usuarios
            - Un 60% del valor dado por el indice de Jaccard entre las bandas de ambos usuarios
        Esto da un maximo del indice de 1.0 */
        aux->coefficient = 0;
        #ifdef DEBUG
            printf("%s AND %s\n", aux->userName, user->username);
        #endif
        aux->coefficient += 0.2 * pow(EULER, -0.09*abs(user->age - aux->userNode->age)); // Coeficiente de edad (Lo tomamos como una variable aleatoria de tipo exponencial)
        aux->coefficient += 0.4 * jacardIndex_genreLinkList(user->genres, aux->userNode->genres);
        aux->coefficient += 0.4 * jacardIndex_bandLinkList(user->bands, aux->userNode->bands);

        aux = aux->next;
    }
    sort_userLinkList_byCoefficient(&possibleFriends->next);
    print_user_recommendations(user, possibleFriends);
    request_for_friendship(user, possibleFriends, users);

    // Liberamos toda la memoria utilizada
    delete_userLinkList(possibleFriends);
    delete_genreLinkList(programGenreList);
    delete_bandLinkList(programBandList);
    printf("Usuario "ANSI_COLOR_CYAN"%s"ANSI_COLOR_RESET" creado exitosamente\n\n", userName);
    return user;
}