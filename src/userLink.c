/**
 * @file userLink.c
 * @author Constanza Araya, Rodolfo Cifuentes, Bruno Martinez, Milton Hernández, Guliana Ruiz
 * @brief Funciones de manejo de enlaces a usuarios
*/
#include "userLink.h"

// Funciones para el manejo de una lista de enlaces a usuarios

/**
 * @brief Crea una lista vacia de enlaces a usuarios
 *
 * @param linkList Puntero a una lista de enlaces a usuarios a vaciar, si es necesario
 * @return Puntero al nodo centinela de la lista
*/
UserLinkList create_empty_userLinkList(UserLinkList linkList){
    if(!is_empty_userLinkList(linkList)){
        delete_userLinkList(linkList);
    }
    UserLinkList newList = (UserLinkList) malloc(sizeof(struct _userLinkNode));
    if(newList == NULL){
        print_error(200, NULL, NULL);
    }
    newList->next = NULL;
    newList->userNode = NULL;
    return newList;
}

/**
 * @brief Borra una lista de enlaces a usuarios
 *
 * @param linkList Puntero a la lista de enlaces a usuarios a borrar
*/
void delete_userLinkList(UserLinkList linkList){
    if(is_empty_userLinkList(linkList)){
        return;
    }
    UserLinkPosition aux = userLinkList_first(linkList);
    while(aux != NULL){
        delete_userLinkList_node(aux, linkList);
        aux = userLinkList_first(linkList);
    }
    free(linkList);
}

/**
 * @brief Indica si una lista de usuarios esta vacia
 *
 * @param linkList Lista de enlaces a usuarios
 * @return TRUE si la lista esta vacia, FALSE en caso contrario
*/
bool is_empty_userLinkList(UserLinkList linkList){
    return linkList == NULL;
}

/**
 * @brief Imprime la lista de enlaces a usuarios
 *
 * @param linkList Lista de enlaces a usuarios
*/
void print_userLinkList(UserLinkList linkList){
    if(linkList == NULL){
        printf("NULL");
        return;
    }
    UserLinkPosition current = linkList->next;
    printf("{%s", current->userName);
    current = current->next;
    if (current != NULL){
        while (current != NULL) {
            printf(", %s", current->userName);
            current = current->next;
        }
    }
    printf("}");
}

/**
 * @brief Busca un usuario dentro de una lista de enlaces a usuarios
 *
 * @param linkList Lista en que se desea buscar
 * @param userName Nombre de usuario a buscar
 * @return Puntero al nodo encontrado
*/
UserLinkPosition find_userLinkList_node(UserLinkList linkList, char* userName){
    if(is_empty_userLinkList(linkList)){
        return NULL;
    }
    UserLinkPosition P = userLinkList_first(linkList);
    while (P != NULL && strcmp(P->userName, userName) != 0) {
        P = P->next;
    }
    return P;
}

/**
 * @brief Encuentra el nodo anterior a un nodo dado en una lista de enlaces a usuarios
 *
 * @param P Nodo del cual se busca el anterior
 * @param linkList Puntero a la lista de enlaces a usuarios
 * @return Puntero al nodo anterior a @p P
 */
UserLinkPosition find_userLinkList_prev_node(UserLinkPosition P, UserLinkList linkList){
    UserLinkPosition aux = linkList;
    while (aux != NULL && strcmp(aux->next->userName, P->userName) != 0){
        aux = aux->next;
    }
    return aux;
}

/**
 * @brief Crea el nodo correspondiente a un enlace a un usuario (sin apuntar a un nodo de usuario)
 *
 * @param prevPosition Puntero al nodo anterior al que se desea insertar
 * @param userName Nombre del usuario al que se desea enlazar
 * @return Puntero al nodo creado
*/
UserLinkPosition insert_userLinkList_node_basicInfo(UserLinkPosition prevPosition, char* userName){
    UserLinkPosition newNode = (UserLinkPosition) malloc(sizeof(struct _userLinkNode));
    if (newNode == NULL) {
        print_error(200, NULL, NULL);
    }
    newNode->userName = malloc(strlen(userName) + 1);
    if(newNode->userName == NULL){
        print_error(200, NULL, NULL);
    }
    strcpy(newNode->userName, userName);
    newNode->next = prevPosition->next;
    prevPosition->next = newNode;
    return newNode;
}

/**
 * @brief Crea el nodo correspondiente a un enlace a un usuario (apuntando a un nodo de usuario)
 *
 * @param prevPosition Puntero al nodo anterior al que se desea insertar
 * @param userNode Puntero al nodo de usuario al que se desea enlazar
 * @return Puntero al nodo creado
*/
UserLinkPosition insert_userLinkList_node_completeInfo(UserLinkPosition prevPosition, PtrToUser userNode){
    UserLinkPosition newNode = (UserLinkPosition) malloc(sizeof(struct _userLinkNode));
    if (newNode == NULL) {
        print_error(200, NULL, NULL);
    }
    newNode->userName = malloc(strlen(userNode->username) + 1);
    if(newNode->userName == NULL){
        print_error(200, NULL, NULL);
    }
    strcpy(newNode->userName, userNode->username);
    newNode->userNode = userNode;
    newNode->next = prevPosition->next;
    prevPosition->next = newNode;
    return newNode;
}

/**
 * @brief Borra un nodo de una lista de enlaces a usuarios
 *
 * @param P Puntero al nodo a borrar
 * @param linkList Puntero a la lista de enlaces a usuarios a la que pertenece @p P
*/
void delete_userLinkList_node(UserLinkPosition P, UserLinkList linkList){
    if(P == NULL){
        print_error(202, NULL, NULL);
    }
    UserLinkPosition prevNode = find_userLinkList_prev_node(P, linkList);
    if(prevNode == NULL){
        print_error(300, P->userName, NULL);
        return;
    }
    prevNode->next = P->next;
    free(P->userName);
    free(P);
}

// Funciones de interaccion con el usuario
/**
 * @brief Completa un enlace a un usuario (agregando el puntero al nodo de usuario)
 *
 * @param P Puntero al nodo de enlace a usuario
 * @param userTable Puntero a la tabla de usuarios
 * @return Puntero al nodo de enlace a usuario completado
*/
UserLinkPosition complete_userLinkList_node(UserLinkPosition P, UserTable userTable){
    UserPosition userNode = find_userTable_node(userTable, P->userName);
    if(userNode == NULL){
        print_error(300, P->userName, NULL);
        return NULL;
    }
    P->userNode = userNode;
    return P;
}

/**
 * @brief Obtiene el primer nodo de una lista de enlaces a usuarios
 *
 * @param linkList Puntero a la lista de enlaces a usuarios
 * @return Puntero al primer enlace a usuario de la lista
*/
UserLinkPosition userLinkList_first(UserLinkList linkList){
    return linkList->next;
}

/**
 * @brief Obtiene el ultimo nodo de una lista de enlaces a usuarios
 *
 * @param linkList Puntero a la lista de enlaces a usuarios
 * @return Puntero al ultimo enlace a usuario de la lista
*/
UserLinkPosition userLinkList_last(UserLinkList linkList){
    UserLinkPosition P = linkList->next;
    while (P->next != NULL) {
        P = P->next;
    }
    return P;
}

/**
 * @brief Obtiene el seiguiente nodo a @p P de una lista de enlaces de usuario.
 *
 * @param P Nodo del que se quiere obtener el siguiente.
 * @return El siguiente nodo de la lista de enlaces de usuario.
*/
UserLinkPosition userLinkList_advance(UserLinkPosition P){
    return P->next;
}

//otras funciones

/**
 * @brief encuentra recomendaciones de amigos para un usuario
 *
 * @param user Usuario a recomendar amigos
 * @param table Tabla de usuarios
 * @return Lista de amigos recomendados (amigos en tercer nivel)
 */
UserLinkPosition find_possible_friends(UserPosition user, UserTable table)
{
    //iniciaciones
    UserLinkList amigos = create_empty_userLinkList(NULL);
    UserLinkList visitados = create_empty_userLinkList(NULL);
    UserLinkList vecino = create_empty_userLinkList(NULL);
    UserLinkList cola = create_empty_userLinkList(NULL);

    insert_userLinkList_node_basicInfo(cola, user->username);
    UserLinkPosition rear = insert_userLinkList_node_basicInfo(visitados, user->username);
    rear->coefficient = 1.0; //nivel inicial (nivel 1)

    //mientas que la cola no este vacia coefficient sea menor a 5.0
    while(cola->next != NULL && visitados->next->coefficient < 5.0){
        //procesar nodo actual

        #ifdef DEBUG
            printf(" - %-10s: ---->   ",rear->userName);
        #endif


        // Obtener nodo de usuario correspondiente
        UserPosition userNode = find_userTable_node(table, rear->userName);
        if(userNode == NULL){
            print_error(300, rear->userName, NULL);
            return NULL;
        }
        complete_user_from_json(userNode);
        amigos = userNode->friends;

        // Iterar sobre vecinos
        vecino = amigos->next;

        while(vecino != NULL){
            //si el amigo es nuevo, agregarlo a visitados
            if(!find_userLinkList_node(visitados, vecino->userName)&& rear->coefficient + 1 <= 4.0)
                {
                    //enqueue
                    insert_userLinkList_node_basicInfo(cola, vecino->userName);
                    cola->next->coefficient = rear->coefficient +1;
                    #ifdef DEBUG
                        printf("%-10s",vecino->userName);
                    #endif
                    insert_userLinkList_node_basicInfo(visitados, vecino->userName);
                    visitados->next->coefficient = rear->coefficient +1;
                }
            vecino = vecino->next;
        }
        #ifdef DEBUG
            printf("\n");
        #endif

        //dequeue
        rear = find_userLinkList_prev_node(rear, cola);
        delete_userLinkList_node(rear->next, cola);
    }

    // Eliminamos los nodos que tengan coeficiente 2 (amigos directos) y 1 (El propio usuario)
    UserLinkPosition aux = visitados->next;
    while(aux != NULL){
        if(aux->coefficient == 2.0 || aux->coefficient == 1.0){
            delete_userLinkList_node(aux, visitados);
        }
        aux = aux->next;
    }

    delete_userLinkList(cola);
    return visitados;
}