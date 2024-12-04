/**
 * @file user.c
 * @author Constanza Araya, Rodolfo Cifuentes, Bruno Martinez, Milton Hernández, Guliana Ruiz
 * @brief Funciones para manejo de usuarios dentro de loopweb
*/
#include "user.h"

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
UserPosition create_new_user(const char *username, int age, const char *nationality, const char *description, GenreLinkList genres, BandLinkList bands, UserLinkList friends){
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
UserPosition complete_userList_node(UserPosition P, int age, const char *nationality, const char *description, GenreLinkList genres, BandLinkList bands){
    if(P == NULL){
        print_error(202, NULL, NULL);
    }
    P->age = age;

    P->nationality = (char*)realloc(P->nationality, strlen(nationality) + 1);
    strcpy(P->nationality, nationality);

    P->description = (char*)realloc(P->description, strlen(description) + 1);
    strcpy(P->description, description);

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
UserPosition insert_userTable_node(UserTable table, const char *username, int age, const char *nationality, const char *description, GenreLinkList genres, BandLinkList bands, UserLinkList friends){
    if(find_userTable_node(table, username) != NULL){
        print_error(301, NULL, NULL);
        return NULL;
    }

    unsigned int index = jenkins_hash((char*)username) % USER_TABLE_SIZE;

    PtrToUser newUser = create_new_user(username, age, nationality, description, genres, bands, friends);
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