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
    if(user == NULL
        || user->username == NULL
        || user->nationality == NULL
        || user->description == NULL
        || user->genres == NULL
        || user->bands == NULL
        || user->friends == NULL){
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
    fprintf(file,"\t\"comments\": [");
    CommentPosition aux3 = user->comments->next;
    while (aux3 != NULL) {
        fprintf(file,"\"%ld\"", aux3->ID);
        if (aux3->next != NULL) {
            fprintf(file,", ");
        }
        aux3 = aux3->next;
    }
    fprintf(file,"],\n");

    // Amigos de la lista de amigos
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
            print_CommentList(current->comments);
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
UserPosition create_new_user(const char *username, int age, const char *nationality, const char *description, GenreLinkList genres, BandLinkList bands, UserLinkList friends, CommentList comments){
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
UserPosition complete_userList_node(UserPosition P, int age, const char *nationality, const char *description, GenreLinkList genres, BandLinkList bands, CommentList comments){
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
    delete_CommentList(P->comments);
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
UserPosition insert_userTable_node(UserTable table, const char *username, int age, const char *nationality, const char *description, GenreLinkList genres, BandLinkList bands, UserLinkList friends, CommentList comments){
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

// Funciones de LoopWeb relacionadas a usuarios

/**
 * @brief Funcion que crea un comentario en loopweb partiendo de la interaccion con el usuario
 *
 * @param userName Nombre del usuario
 * @param userTable Tabla de usuarios
 * @param bandTable Tabla de bandas
 * @param genreTable Tabla de generos
*/
void make_comment(char* userName, UserTable userTable, BandTable bandTable, GenreTable genreTable)
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

        // Limpiamos el buffer de entrada
        while (getchar() != '\n');

    }while(option != 0);

    CommentList commentList = create_empty_CommentList(NULL); // Para agregar a donde corresponde
    CommentPosition commentNode = create_new_comment(time(NULL), commentText, userName);
    complete_comment_tags(commentNode);
    insert_CommentList_node(commentList, commentNode);

    // Revisamos las bandas del comentario
    BandLinkList bandAux = commentNode->bands->next;
    while(bandAux != NULL){
        printf("Procesando: %s\n", bandAux->band);
        if(!find_bandTable_band(bandAux->band, bandTable))
        {
            printf("La banda %s no se encuentra en la base de datos, desea agregarla?: (0:Si, 1:No): ", bandAux->band);
            if(scanf("%d", &option) != 1){
                print_error(103, NULL, NULL);
                bandAux = bandAux->next;
                continue;
            }
            if(option == 0){
                insert_bandTable_band(bandAux->band, commentList, bandTable);
            }
        }
        insert_CommentList_node(find_bandTable_band(bandAux->band, bandTable)->comments, commentNode); // Se agrega el comentario a bandas
        bandAux = bandAux->next;
    }

    // Revisamos los generos del comentario
    GenreLinkPosition genreAux = commentNode->genres->next;
    while(genreAux != NULL){
        printf("Procesando: %s\n", genreAux->genre);
        if(!find_genresTable_genre(genreAux->genre, genreTable))
        {
            printf("El genero %s no se encuentra en la base de datos, desea agregarlo?: (0:Si, 1:No): ", genreAux->genre);
            if(scanf("%d", &option) != 1){
                print_error(103, NULL, NULL);
                genreAux = genreAux->next;
                continue;
            }
            if(option == 0){
                insert_genre(genreAux->genre, commentList, genreTable);
            }
        }
        insert_CommentList_node(find_genresTable_genre(genreAux->genre, genreTable)->comments, commentNode); // Se agrega el comentario a bandas
        genreAux = genreAux->next;
    }

    // Guardamos los comentarios en donde corresponde
    save_commentNode(commentNode); // Se guarda en el archivo correspondiente
    insert_CommentList_node(author->comments, commentNode); // Se guarda en la lista de comentarios del autor
    save_userNode(author);
    save_bandTable(bandTable);
    save_genresTable(genreTable);

    sleep(1);
    printf(CLEAR_SCREEN"El siguiente comentario fue agregado a loopweb:\n\n");
    print_commentNode(commentNode);

}