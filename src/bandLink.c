/**
 * @file bandLink.c
 * @author Constanza Araya, Rodolfo Cifuentes, Bruno Martinez, Milton Hernández, Guliana Ruiz
 * @brief Funciones de manejo de enlaces a bandas
*/
#include "bandLink.h"

// Funciones para el manejo de una lista de enlaces a bandas

/**
 * @brief Crea una lista vacia de enlaces a bandas
 *
 * @param linkList Puntero a una lista de enlaces a bandas a vaciar, si es necesario
 * @return Puntero al nodo centinela de la lista
*/
BandLinkList create_empty_bandLinkList(BandLinkList linkList){
    if(!is_empty_bandLinkList(linkList)){
        delete_bandLinkList(linkList);
    }
    BandLinkList newList = (BandLinkList) malloc(sizeof(struct _bandLinkNode));
    if(newList == NULL){
        print_error(200, NULL, NULL);
    }
    newList->next = NULL;
    newList->bandNode = NULL;
    return newList;
}

/**
 * @brief Borra una lista de enlaces a bandas
 *
 * @param linkList Puntero a la lista de enlaces a bandas a borrar
*/
void delete_bandLinkList(BandLinkList linkList){
    if(is_empty_bandLinkList(linkList)){
        return;
    }
    BandLinkPosition aux = bandLinkList_first(linkList);
    while(aux != NULL){
        delete_bandLinkList_node(aux, linkList);
        aux = bandLinkList_first(linkList);
    }
    free(linkList);
}

/**
 * @brief Indica si una lista de bandas esta vacia
 *
 * @param linkList Lista de enlaces a bandas
 * @return TRUE si la lista esta vacia, FALSE en caso contrario
*/
bool is_empty_bandLinkList(BandLinkList linkList){
    return linkList == NULL;
}

/**
 * @brief Imprime la lista de enlaces a bandas
 *
 * @param linkList Lista de enlaces a bandas
*/
void print_bandLinkList(BandLinkList linkList){
    if(linkList == NULL){
        printf("NULL");
        return;
    }
    if(linkList->next == NULL){
        printf("Empy");
        return;
    }
    BandLinkPosition current = linkList->next;
    printf("{%s", current->band);
    current = current->next;
    if (current != NULL){
        while (current != NULL) {
            printf(", %s", current->band);
            current = current->next;
        }
    }
    printf("}");
}

/**
 * @brief Busca una banda dentro de una lista de enlaces a bandas
 *
 * @param linkList Lista en que se desea buscar
 * @param band Nombre de la banda a buscar
 * @return Puntero al nodo encontrado
*/
BandLinkPosition find_bandLinkList_node(BandLinkList linkList, char* band){
    if(is_empty_bandLinkList(linkList)){
        return NULL;
    }
    BandLinkPosition P = bandLinkList_first(linkList);
    while (P != NULL && strcmp(P->band, band) != 0) {
        P = P->next;
    }
    return P;
}

/**
 * @brief Encuentra el nodo anterior a un nodo dado en una lista de enlaces a bandas
 *
 * @param P Nodo del cual se busca el anterior
 * @param linkList Puntero a la lista de enlaces a bandas
 * @return Puntero al nodo anterior a @p P
 */
BandLinkPosition find_bandLinkList_prev_node(BandLinkPosition P, BandLinkList linkList){
    BandLinkPosition aux = linkList;
    while (aux != NULL && strcmp(aux->next->band, P->band) != 0){
        aux = aux->next;
    }
    return aux;
}

/**
 * @brief Crea el nodo correspondiente a un enlace a una banda (sin apuntar a un nodo de banda)
 *
 * @param prevPosition Puntero al nodo anterior al que se desea insertar
 * @param band Nombre de la banda al que se desea enlazar
 * @return Puntero al nodo creado
*/
BandLinkPosition insert_bandLinkList_node_basicInfo(BandLinkPosition prevPosition, char* band){
    BandLinkPosition newNode = (BandLinkPosition) malloc(sizeof(struct _bandLinkNode));
    if (newNode == NULL) {
        print_error(200, NULL, NULL);
    }
    newNode->band = malloc(strlen(band) + 1);
    if(newNode->band == NULL){
        print_error(200, NULL, NULL);
    }
    strcpy(newNode->band, band);
    newNode->next = prevPosition->next;
    prevPosition->next = newNode;
    return newNode;
}

/**
 * @brief Crea el nodo correspondiente a un enlace a una banda (apuntando a un nodo de banda)
 *
 * @param prevPosition Puntero al nodo anterior al que se desea insertar
 * @param userNode Puntero al nodo de banda al que se desea enlazar
 * @return Puntero al nodo creado
*/
BandLinkPosition insert_bandLinkList_node_completeInfo(BandLinkPosition prevPosition, PtrToBand userNode){
    BandLinkPosition newNode = (BandLinkPosition) malloc(sizeof(struct _bandLinkNode));
    if (newNode == NULL) {
        print_error(200, NULL, NULL);
    }
    newNode->band = malloc(strlen(userNode->band) + 1);
    if(newNode->band == NULL){
        print_error(200, NULL, NULL);
    }
    strcpy(newNode->band, userNode->band);
    newNode->bandNode = userNode;
    newNode->next = prevPosition->next;
    prevPosition->next = newNode;
    return newNode;
}

/**
 * @brief Borra un nodo de una lista de enlaces a bandas
 *
 * @param P Puntero al nodo a borrar
 * @param linkList Puntero a la lista de enlaces a bandas a la que pertenece @p P
*/
void delete_bandLinkList_node(BandLinkPosition P, BandLinkList linkList){
    if(P == NULL){
        print_error(202, NULL, NULL);
    }
    BandLinkPosition prevNode = find_bandLinkList_prev_node(P, linkList);
    if(prevNode == NULL){
        print_error(300, P->band, NULL);
        return;
    }
    prevNode->next = P->next;
    free(P->band);
    free(P);
}

// Funciones de ordenamiento de listas de enlaces a bandas

/**
 * @brief Divide una lista enlazada en dos mitades.
 *
 * @param source Puntero al nodo inicial de la lista a dividir.
 * @param frontRef Referencia a la primera mitad de la lista.
 * @param backRef Referencia a la segunda mitad de la lista.
 */
void split_bandLinkList(BandLinkPosition source, BandLinkPosition* frontRef, BandLinkPosition* backRef)
{
    BandLinkPosition slow, fast;
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
BandLinkPosition merge_bandLinkLists(BandLinkPosition a, BandLinkPosition b)
{
    if (a == NULL) return b;
    if (b == NULL) return a;

    BandLinkPosition result;

    if (strcmp(a->band, b->band) < 0) {
        result = a;
        result->next = merge_bandLinkLists(a->next, b);
    } else {
        result = b;
        result->next = merge_bandLinkLists(a, b->next);
    }
    return result;
}

/**
 * @brief Ordena una lista de bandas utilizando el algoritmo merge sort.
 *
 * @note Ordena la lista de bandas en orden alfabetico ascendente.
 * @param headRef Referencia al puntero del nodo inicial de la lista a ordenar.
 * @warning Es necesario pasar a esta funcion la primera posicion de la lista de bandas NO EL CENTINELA.
*/
void sort_bandLinkList_byName(BandLinkPosition* headRef)
{
    BandLinkPosition head = *headRef;
    BandLinkPosition a, b;

    if ((head == NULL) || (head->next == NULL)) {
        return;  /**<si la lista esta vacia o tiene un solo elemento, no hay que ordenar */
    }

    split_bandLinkList(head, &a, &b);

    sort_bandLinkList_byName(&a);  /**<ordena la primera mitad */
    sort_bandLinkList_byName(&b);  /**<ordena la segunda mitad */

    *headRef = merge_bandLinkLists(a, b);  /**<fusiona las dos mitades ordenadas */
}

// Funciones de interaccion con el usuario

/**
 * @brief Completa un enlace a una banda (agregando el puntero al nodo de banda)
 *
 * @param P Puntero al nodo de enlace a banda
 * @param bandTable Puntero a la tabla de bandas
 * @return Puntero al nodo de enlace a banda completado
*/
BandLinkPosition complete_bandLinkList_node(BandLinkPosition P, BandTable bandTable){
    BandPosition userNode = find_bandTable_band(P->band, bandTable);
    if(userNode == NULL){
        print_error(300, P->band, NULL);
        return NULL;
    }
    P->bandNode = userNode;
    return P;
}

/**
 * @brief Obtiene el primer nodo de una lista de enlaces a bandas
 *
 * @param linkList Puntero a la lista de enlaces a bandas
 * @return Puntero al primer enlace a banda de la lista
*/
BandLinkPosition bandLinkList_first(BandLinkList linkList){
    return linkList->next;
}

/**
 * @brief Obtiene el ultimo nodo de una lista de enlaces a bandas
 *
 * @param linkList Puntero a la lista de enlaces a bandas
 * @return Puntero al ultimo enlace a banda de la lista
*/
BandLinkPosition bandLinkList_last(BandLinkList linkList){
    BandLinkPosition P = linkList->next;
    while (P->next != NULL) {
        P = P->next;
    }
    return P;
}

/**
 * @brief Obtiene el seiguiente nodo a @p P de una lista de enlaces de banda.
 *
 * @param P Nodo del que se quiere obtener el siguiente.
 * @return El siguiente nodo de la lista de enlaces de banda.
*/
BandLinkPosition bandLinkList_advance(BandLinkPosition P){
    return P->next;
}


// Funciones de ordenamiento de listas de enlaces a bandas

/**
 * @brief Ordena una lista de enlaces a bandas usando el algoritmo de intercambio (BubleSort)
 *
 * @param linkList Puntero a la lista de enlaces a bandas a ordenar
 * @return Puntero a la lista ordenada
*/
BandLinkList bubbleSort_bandLinkList(BandLinkList linkList){
    if(is_empty_bandLinkList(linkList)){
		return linkList;
	}
	unsigned int listSize = 0;
    BandLinkPosition P = linkList->next;
	while(P != NULL){ // Calculo ineficiente de la cantidad de elementos de la lista
		listSize++;
		P = P->next;
	}
	unsigned int toOrder = listSize-1;

	P=linkList->next;
	while(toOrder > 0){
		for(unsigned int i = 0; i < toOrder; i++){
			if(strcmp(P->band, P->next->band) > 0){
				swap_bandLinkList_nodes(P, P->next);
			}
			P = P->next;
		}
		P=linkList->next;
		toOrder--;

	}
	return linkList;
}

/**
 * @brief Intercambia los punteros de dos nodos de una lista de enlaces a bandas
 *
 * @param a Puntero al primer nodo a intercambiar
 * @param b Puntero al segundo nodo a intercambiar
*/
void swap_bandLinkList_nodes(BandLinkPosition a, BandLinkPosition b){
    BandLinkNode aux;
    aux = *a;

	a->band = b->band;
    a->bandNode = b->bandNode;

	b->band = aux.band;
    b->bandNode = aux.bandNode;
}