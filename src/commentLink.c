/**
 * @file commentLink.c
 * @author Constanza Araya, Rodolfo Cifuentes, Bruno Martinez, Milton Hernández, Guliana Ruiz
 * @brief Funciones de manejo de enlaces a comentarios
*/
#include "commentLink.h"

// Funciones para el manejo de una lista de enlaces a comentarios

/**
 * @brief Crea una lista vacia de enlaces a comentarios
 *
 * @param linkList Puntero a una lista de enlaces a comentarios a vaciar, si es necesario
 * @return Puntero al nodo centinela de la lista
*/
CommentLinkList create_empty_commentLinkList(CommentLinkList linkList){
    if(!is_empty_commentLinkList(linkList)){
        delete_commentLinkList(linkList);
    }
    CommentLinkList newList = (CommentLinkList) malloc(sizeof(struct _commentLinkNode));
    if(newList == NULL){
        print_error(200, NULL, NULL);
    }
    newList->next = NULL;
    newList->commentNode = NULL;
    return newList;
}

/**
 * @brief Borra una lista de enlaces a comentarios
 *
 * @param linkList Puntero a la lista de enlaces a comentarios a borrar
*/
void delete_commentLinkList(CommentLinkList linkList){
    if(is_empty_commentLinkList(linkList)){
        return;
    }
    CommentLinkPosition aux = commentLinkList_first(linkList);
    while(aux != NULL){
        delete_commentLinkList_node(aux, linkList);
        aux = commentLinkList_first(linkList);
    }
    free(linkList);
}

/**
 * @brief Indica si una lista de comentarios esta vacia
 *
 * @param linkList Lista de enlaces a comentarios
 * @return TRUE si la lista esta vacia, FALSE en caso contrario
*/
bool is_empty_commentLinkList(CommentLinkList linkList){
    return linkList == NULL;
}

/**
 * @brief Imprime la lista de enlaces a comentarios
 *
 * @param linkList Lista de enlaces a comentarios
*/
void print_commentLinkList(CommentLinkList linkList){
    if(linkList == NULL){
        printf("NULL");
        return;
    }
    if(linkList->next == NULL){
        printf("Empy");
        return;
    }
    CommentLinkPosition current = linkList->next;
    printf("{%ld", current->commentID);
    current = current->next;
    if (current != NULL){
        while (current != NULL) {
            printf(", %ld", current->commentID);
            current = current->next;
        }
    }
    printf("}");
}

/**
 * @brief Busca un comentario dentro de una lista de enlaces a comentarios
 *
 * @param linkList Lista en que se desea buscar
 * @param commentID ID del comentario a buscar
 * @return Puntero al nodo encontrado
*/
CommentLinkPosition find_commentLinkList_node(CommentLinkList linkList, time_t commentID){
    if(is_empty_commentLinkList(linkList)){
        return NULL;
    }
    CommentLinkPosition P = commentLinkList_first(linkList);
    while (P != NULL && P->commentID != commentID) {
        P = P->next;
    }
    return P;
}

/**
 * @brief Encuentra el nodo anterior a un nodo dado en una lista de enlaces a comentarios
 *
 * @param P Nodo del cual se busca el anterior
 * @param linkList Puntero a la lista de enlaces a comentarios
 * @return Puntero al nodo anterior a @p P
 */
CommentLinkPosition find_commentLinkList_prev_node(CommentLinkPosition P, CommentLinkList linkList){
    CommentLinkPosition aux = linkList;
    while (aux != NULL && aux->next->commentID != P->commentID){
        aux = aux->next;
    }
    return aux;
}

/**
 * @brief Crea el nodo correspondiente a un enlace a un comentario (sin apuntar a un nodo de comentario)
 *
 * @param prevPosition Puntero al nodo anterior al que se desea insertar
 * @param comment Nombre del comentario al que se desea enlazar
 * @return Puntero al nodo creado
*/
CommentLinkPosition insert_commentLinkList_node_basicInfo(CommentLinkPosition prevPosition, time_t commentID){
    CommentLinkPosition newNode = (CommentLinkPosition) malloc(sizeof(struct _commentLinkNode));
    if (newNode == NULL) {
        print_error(200, NULL, NULL);
    }
    newNode->commentID = commentID;
    newNode->next = prevPosition->next;
    prevPosition->next = newNode;
    return newNode;
}

/**
 * @brief Crea el nodo correspondiente a un enlace a un comentario (apuntando a un nodo de comentario)
 *
 * @param prevPosition Puntero al nodo anterior al que se desea insertar
 * @param commentNode Puntero al nodo de comentario al que se desea enlazar
 * @return Puntero al nodo creado
*/
CommentLinkPosition insert_commentLinkList_node_completeInfo(CommentLinkPosition prevPosition, PtrToComment commentNode){
    CommentLinkPosition newNode = (CommentLinkPosition) malloc(sizeof(struct _commentLinkNode));
    if (newNode == NULL) {
        print_error(200, NULL, NULL);
    }
    newNode->commentID = commentNode->ID;
    newNode->commentNode = commentNode;
    newNode->next = prevPosition->next;
    prevPosition->next = newNode;
    return newNode;
}

/**
 * @brief Borra un nodo de una lista de enlaces a comentarios
 *
 * @param P Puntero al nodo a borrar
 * @param linkList Puntero a la lista de enlaces a comentarios a la que pertenece @p P
*/
void delete_commentLinkList_node(CommentLinkPosition P, CommentLinkList linkList){
    if(P == NULL){
        print_error(202, NULL, NULL);
    }
    CommentLinkPosition prevNode = find_commentLinkList_prev_node(P, linkList);
    if(prevNode == NULL){
        char commentID[20];
        strcpy(commentID, ctime(&P->commentID));
        print_error(302, commentID, NULL);
        return;
    }
    prevNode->next = P->next;
    free(P);
}

// Funciones de interaccion con el usuario

/**
 * @brief Completa un enlace a un comentario (agregando el puntero al nodo de comentario)
 *
 * @param P Puntero al nodo de enlace a comentario
 * @param commentTable Puntero a la tabla de comentarios
 * @return Puntero al nodo de enlace a comentario completado
*/
CommentLinkPosition complete_commentLinkList_node(CommentLinkPosition P, CommentTable commentTable){
    CommentPosition commentNode = find_commentTable_comment(P->commentID, commentTable);
    if(commentNode == NULL){
        char commentID[20];
        sprintf(commentID, "%ld", P->commentID);
        print_error(302, commentID, NULL);
        return NULL;
    }
    P->commentNode = commentNode;
    return P;
}

/**
 * @brief Obtiene el primer nodo de una lista de enlaces a comentarios
 *
 * @param linkList Puntero a la lista de enlaces a comentarios
 * @return Puntero al primer enlace a comentario de la lista
*/
CommentLinkPosition commentLinkList_first(CommentLinkList linkList){
    return linkList->next;
}

/**
 * @brief Obtiene el ultimo nodo de una lista de enlaces a comentarios
 *
 * @param linkList Puntero a la lista de enlaces a comentarios
 * @return Puntero al ultimo enlace a comentario de la lista
*/
CommentLinkPosition commentLinkList_last(CommentLinkList linkList){
    CommentLinkPosition P = linkList->next;
    while (P->next != NULL) {
        P = P->next;
    }
    return P;
}

/**
 * @brief Obtiene el seiguiente nodo a @p P de una lista de enlaces de comentario.
 *
 * @param P Nodo del que se quiere obtener el siguiente.
 * @return El siguiente nodo de la lista de enlaces de comentario.
*/
CommentLinkPosition commentLinkList_advance(CommentLinkPosition P){
    return P->next;
}


// Funciones de ordenamiento de listas de enlaces a comentarios

/**
 * @brief Divide una lista enlazada en dos mitades.
 *
 * @param source Puntero al nodo inicial de la lista a dividir.
 * @param frontRef Referencia a la primera mitad de la lista.
 * @param backRef Referencia a la segunda mitad de la lista.
 */
void split_commentLinkList(CommentLinkPosition source, CommentLinkPosition* frontRef, CommentLinkPosition* backRef)
{
    CommentLinkPosition slow, fast;
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
 * @brief Fusiona dos listas enlazadas ordenadas en una sola lista ordenada
 *
 * @param a Puntero a la primera lista ordenada
 * @param b Puntero a la segunda lista ordenada
 * @return Puntero al nodo inicial de la lista fusionada ordenada
 */
CommentLinkPosition merge_commentLinkLists(CommentLinkPosition a, CommentLinkPosition b)
{
    if (a == NULL) return b;
    if (b == NULL) return a;

    CommentLinkPosition result;

    if (a->commentID > b->commentID) {
        result = a;
        result->next = merge_commentLinkLists(a->next, b);
    } else {
        result = b;
        result->next = merge_commentLinkLists(a, b->next);
    }
    return result;
}

/**
 * @brief Ordena una lista de comentarios utilizando el algoritmo merge sort.
 *
 * @note Ordena la lista de comentarios de mas reciente a mas antiguo.
 * @param headRef Referencia al puntero del nodo inicial de la lista a ordenar.
 * @warning Es necesario pasar a esta funcion la primera posicion de la lista de comentarios NO EL CENTINELA.
*/
void sort_commentLinkList_byID(CommentLinkPosition* headRef)
{
    CommentLinkPosition head = *headRef;
    CommentLinkPosition a, b;

    if ((head == NULL) || (head->next == NULL)) {
        return;  /**<si la lista esta vacia o tiene un solo elemento, no hay que ordenar */
    }

    split_commentLinkList(head, &a, &b);

    sort_commentLinkList_byID(&a);  /**<ordena la primera mitad */
    sort_commentLinkList_byID(&b);  /**<ordena la segunda mitad */

    *headRef = merge_commentLinkLists(a, b);  /**<fusiona las dos mitades ordenadas */
}