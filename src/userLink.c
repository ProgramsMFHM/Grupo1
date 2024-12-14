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
    if(linkList->next == NULL){
        printf("Empty");
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

// Funciones de ordenamiento de listas de enlaces a usuarios

/**
 * @brief Divide una lista enlazada en dos mitades.
 *
 * @param source Puntero al nodo inicial de la lista a dividir.
 * @param frontRef Referencia a la primera mitad de la lista.
 * @param backRef Referencia a la segunda mitad de la lista.
 */
void split_userLinkList(UserLinkPosition source, UserLinkPosition* frontRef, UserLinkPosition* backRef)
{
    UserLinkPosition slow, fast;
    slow = source;
    fast = source->next;

    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
}

/**
 * @brief Fusiona dos listas enlazadas ordenadas en una sola lista ordenada (Usando el nombre de usuario)
 *
 * @param a Puntero a la primera lista ordenada
 * @param b Puntero a la segunda lista ordenada
 * @return Puntero al nodo inicial de la lista fusionada ordenada
*/
UserLinkPosition merge_userLinkLists_withName(UserLinkPosition a, UserLinkPosition b)
{
    if (a == NULL) return b;
    if (b == NULL) return a;

    UserLinkPosition result;

    if (strcmp(a->userName, b->userName) < 0) {
        result = a;
        result->next = merge_userLinkLists_withName(a->next, b);
    } else {
        result = b;
        result->next = merge_userLinkLists_withName(a, b->next);
    }
    return result;
}

/**
 * @brief Ordena una lista de usuarios utilizando el algoritmo merge sort.
 *
 * @note Ordena la lista de usuarios en orden alfabetico ascendente.
 * @param headRef Referencia al puntero del nodo inicial de la lista a ordenar.
 * @warning Es necesario pasar a esta funcion la primera posicion de la lista de usuarios NO EL CENTINELA.
*/
void sort_userLinkList_byName(UserLinkPosition* headRef)
{
    UserLinkPosition head = *headRef;
    UserLinkPosition a, b;

    if ((head == NULL) || (head->next == NULL)) {
        return;  /**<si la lista esta vacia o tiene un solo elemento, no hay que ordenar */
    }

    split_userLinkList(head, &a, &b);

    sort_userLinkList_byName(&a);  /**<ordena la primera mitad */
    sort_userLinkList_byName(&b);  /**<ordena la segunda mitad */

    *headRef = merge_userLinkLists_withName(a, b);  /**<fusiona las dos mitades ordenadas */
}

/**
 * @brief Fusiona dos listas enlazadas ordenadas en una sola lista ordenada (Usando el coediciente de usuario)
 *
 * @param a Puntero a la primera lista ordenada
 * @param b Puntero a la segunda lista ordenada
 * @return Puntero al nodo inicial de la lista fusionada ordenada
*/
UserLinkPosition merge_userLinkLists_withCoefficient(UserLinkPosition a, UserLinkPosition b)
{
    if (a == NULL) return b;
    if (b == NULL) return a;

    UserLinkPosition result;

    if (a->coefficient > b->coefficient) {
        result = a;
        result->next = merge_userLinkLists_withCoefficient(a->next, b);
    } else {
        result = b;
        result->next = merge_userLinkLists_withCoefficient(a, b->next);
    }
    return result;
}

/**
 * @brief Ordena una lista de usuarios utilizando el algoritmo merge sort.
 *
 * @note Ordena la lista de usuarios de mayor a menor segun el valor del coeficiente de cada usuario.
 * @param headRef Referencia al puntero del nodo inicial de la lista a ordenar.
 * @warning Es necesario pasar a esta funcion la primera posicion de la lista de usuarios NO EL CENTINELA.
*/
void sort_userLinkList_byCoefficient(UserLinkPosition* headRef)
{
    UserLinkPosition head = *headRef;
    UserLinkPosition a, b;

    if ((head == NULL) || (head->next == NULL)) {
        return;  /**<si la lista esta vacia o tiene un solo elemento, no hay que ordenar */
    }

    split_userLinkList(head, &a, &b);

    sort_userLinkList_byCoefficient(&a);  /**<ordena la primera mitad */
    sort_userLinkList_byCoefficient(&b);  /**<ordena la segunda mitad */

    *headRef = merge_userLinkLists_withCoefficient(a, b);  /**<fusiona las dos mitades ordenadas */
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
 * @name Los usuarios son completados por esta funcion
*/
UserLinkPosition find_possible_friends(UserPosition user, UserTable table)
{
    //iniciaciones
    UserLinkList friends;
    UserLinkList visited = create_empty_userLinkList(NULL);
    UserLinkList vecino;
    UserLinkList queue = create_empty_userLinkList(NULL);

    insert_userLinkList_node_basicInfo(queue, user->username);
    UserLinkPosition rear = insert_userLinkList_node_basicInfo(visited, user->username);
    rear->coefficient = 1.0; //nivel inicial (nivel 1)

    //mientas que la cola no este vacia coefficient sea menor a 5.0
    while(queue->next != NULL && visited->next->coefficient < 5.0){
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
        friends = userNode->friends;

        // Iterar sobre vecinos
        vecino = friends->next;

        while(vecino != NULL){
            //si el amigo es nuevo, agregarlo a visitados
            if(!find_userLinkList_node(visited, vecino->userName)&& rear->coefficient + 1 <= 4.0)
                {
                    //enqueue
                    insert_userLinkList_node_basicInfo(queue, vecino->userName);
                    queue->next->coefficient = rear->coefficient +1;
                    #ifdef DEBUG
                        printf("%-10s",vecino->userName);
                    #endif
                    insert_userLinkList_node_basicInfo(visited, vecino->userName);
                    visited->next->coefficient = rear->coefficient +1;
                }
            vecino = vecino->next;
        }
        #ifdef DEBUG
            printf("\n");
        #endif

        //dequeue
        rear = find_userLinkList_prev_node(rear, queue);
        if(rear == queue){
            break;
        }
        delete_userLinkList_node(rear->next, queue);
    }

    // Eliminamos el nodo correspondiente al usuario
    delete_userLinkList_node(find_userLinkList_node(visited, user->username), visited);

    // Eliminamos los nodos que tengan coeficiente 2 (amigos directos)
    UserLinkPosition aux = visited->next;
    while(aux != NULL){
        UserLinkPosition aux2 = aux->next;
        if(aux->coefficient == 2.0){
            delete_userLinkList_node(aux, visited);
        }
        aux = aux2;
    }

    if(visited->next == NULL){ // Si no hay recomendaciones las recomendaciones son todos los usuarios de la web
        UserLinkList allUsers = get_loopweb_users(table, false); // Obtenemos todos los usuarios
        UserLinkPosition aux = allUsers->next;
        while(aux != NULL){
            // Si el usuario no es el propio y no esta en la lista de amigos, lo agregamos
            if(aux->userName != user->username && !find_userLinkList_node(user->friends, aux->userName)){
                insert_userLinkList_node_completeInfo(visited, aux->userNode);
            }
            aux = aux->next;
        }

        // Eliminamos el nodo correspondiente al usuario
        delete_userLinkList_node(find_userLinkList_node(visited, user->username), visited);
        // Eliminamos las referencias a todos los usuarios de la tabla
        delete_userLinkList(allUsers);
    }

    delete_userLinkList(queue);
    return visited;
}

void print_user_recommendations(UserPosition user, UserLinkList recommendations)
{
    UserLinkPosition aux = recommendations->next;
    int counter = 1;

    printf("\t\t Posibles amigos para: "ANSI_COLOR_CYAN"%s"ANSI_COLOR_RESET" ("ANSI_COLOR_MAGENTA"%d"ANSI_COLOR_RESET"):\n", user->username, user->age);
    printf("___________________________________________________________________________\n");
    printf("| ID |        Nombre       |    Edad   |      Nacionalidad      |  Coef.  |\n");
    while(aux != NULL){
        printf("| %-3d|        "ANSI_COLOR_CYAN"%-13s"ANSI_COLOR_RESET"|"ANSI_COLOR_MAGENTA"    %-7d"ANSI_COLOR_RESET"|"ANSI_COLOR_YELLOW"      %-18s"ANSI_COLOR_RESET"|  %-5.3f  |\n", counter, aux->userName, aux->userNode->age, aux->userNode->nationality, aux->coefficient);
        counter++;
        aux = aux->next;
    }
    printf("___________________________________________________________________________\n");
    printf("\n");
}