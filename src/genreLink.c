/**
 * @file genreLink.c
 * @author Constanza Araya, Rodolfo Cifuentes, Bruno Martinez, Milton Hernández, Guliana Ruiz
 * @brief Funciones de manejo de enlaces a generos
*/
#include "genreLink.h"

// Funciones para el manejo de una lista de enlaces a generos

/**
 * @brief Crea una lista vacia de enlaces a generos
 *
 * @param linkList Puntero a una lista de enlaces a generos a vaciar, si es necesario
 * @return Puntero al nodo centinela de la lista
*/
GenreLinkList create_empty_genreLinkList(GenreLinkList linkList){
    if(!is_empty_genreLinkList(linkList)){
        delete_genreLinkList(linkList);
    }
    GenreLinkList newList = (GenreLinkList) malloc(sizeof(struct _genreLinkNode));
    if(newList == NULL){
        print_error(200, NULL, NULL);
    }
    newList->next = NULL;
    newList->genreNode = NULL;
    return newList;
}

/**
 * @brief Borra una lista de enlaces a generos
 *
 * @param linkList Puntero a la lista de enlaces a generos a borrar
*/
void delete_genreLinkList(GenreLinkList linkList){
    if(is_empty_genreLinkList(linkList)){
        return;
    }
    GenreLinkPosition aux = genreLinkList_first(linkList);
    while(aux != NULL){
        delete_genreLinkList_node(aux, linkList);
        aux = genreLinkList_first(linkList);
    }
    free(linkList);
}

/**
 * @brief Indica si una lista de generos esta vacia
 *
 * @param linkList Lista de enlaces a generos
 * @return TRUE si la lista esta vacia, FALSE en caso contrario
*/
bool is_empty_genreLinkList(GenreLinkList linkList){
    return linkList == NULL;
}

/**
 * @brief Imprime la lista de enlaces a generos
 *
 * @param linkList Lista de enlaces a generos
*/
void print_genreLinkList(GenreLinkList linkList){
    GenreLinkPosition current = linkList->next;
    printf("{%s", current->genre);
    current = current->next;
    if (current != NULL){
        while (current != NULL) {
            printf(", %s", current->genre);
            current = current->next;
        }
    }
    printf("}");
}

/**
 * @brief Busca un genero dentro de una lista de enlaces a generos
 *
 * @param linkList Lista en que se desea buscar
 * @param genre Nombre de genero a buscar
 * @return Puntero al nodo encontrado
*/
GenreLinkPosition find_genreLinkList_node(GenreLinkList linkList, char* genre){
    if(is_empty_genreLinkList(linkList)){
        return NULL;
    }
    GenreLinkPosition P = genreLinkList_first(linkList);
    while (P != NULL && strcmp(P->genre, genre) != 0) {
        P = P->next;
    }
    return P;
}

/**
 * @brief Encuentra el nodo anterior a un nodo dado en una lista de enlaces a generos
 *
 * @param P Nodo del cual se busca el anterior
 * @param linkList Puntero a la lista de enlaces a generos
 * @return Puntero al nodo anterior a @p P
 */
GenreLinkPosition find_genreLinkList_prev_node(GenreLinkPosition P, GenreLinkList linkList){
    GenreLinkPosition aux = linkList;
    while (aux != NULL && strcmp(aux->next->genre, P->genre) != 0){
        aux = aux->next;
    }
    return aux;
}

/**
 * @brief Crea el nodo correspondiente a un enlace a un genero (sin apuntar a un nodo de genero)
 *
 * @param prevPosition Puntero al nodo anterior al que se desea insertar
 * @param genre Nombre del genero al que se desea enlazar
 * @return Puntero al nodo creado
*/
GenreLinkPosition insert_genreLinkList_node_basicInfo(GenreLinkPosition prevPosition, char* genre){
    GenreLinkPosition newNode = (GenreLinkPosition) malloc(sizeof(struct _genreLinkNode));
    if (newNode == NULL) {
        print_error(200, NULL, NULL);
    }
    newNode->genre = malloc(strlen(genre) + 1);
    if(newNode->genre == NULL){
        print_error(200, NULL, NULL);
    }
    strcpy(newNode->genre, genre);
    newNode->next = prevPosition->next;
    prevPosition->next = newNode;
    return newNode;
}

/**
 * @brief Crea el nodo correspondiente a un enlace a un genero (apuntando a un nodo de genero)
 *
 * @param prevPosition Puntero al nodo anterior al que se desea insertar
 * @param userNode Puntero al nodo de genero al que se desea enlazar
 * @return Puntero al nodo creado
*/
GenreLinkPosition insert_genreLinkList_node_completeInfo(GenreLinkPosition prevPosition, PtrToMusicGenre userNode){
    GenreLinkPosition newNode = (GenreLinkPosition) malloc(sizeof(struct _genreLinkNode));
    if (newNode == NULL) {
        print_error(200, NULL, NULL);
    }
    newNode->genre = malloc(strlen(userNode->genre) + 1);
    if(newNode->genre == NULL){
        print_error(200, NULL, NULL);
    }
    strcpy(newNode->genre, userNode->genre);
    newNode->genreNode = userNode;
    newNode->next = prevPosition->next;
    prevPosition->next = newNode;
    return newNode;
}

/**
 * @brief Borra un nodo de una lista de enlaces a generos
 *
 * @param P Puntero al nodo a borrar
 * @param linkList Puntero a la lista de enlaces a generos a la que pertenece @p P
*/
void delete_genreLinkList_node(GenreLinkPosition P, GenreLinkList linkList){
    if(P == NULL){
        print_error(202, NULL, NULL);
    }
    GenreLinkPosition prevNode = find_genreLinkList_prev_node(P, linkList);
    if(prevNode == NULL){
        print_error(300, P->genre, NULL);
        return;
    }
    prevNode->next = P->next;
    free(P->genre);
    free(P);
}

// Funciones de interaccion con el usuario
/**
 * @brief Completa un enlace a un genero (agregando el puntero al nodo de genero)
 *
 * @param P Puntero al nodo de enlace a genero
 * @param genreTable Puntero a la tabla de generos
 * @return Puntero al nodo de enlace a genero completado
*/
GenreLinkPosition complete_genreLinkList_node(GenreLinkPosition P, MusicGenresTable genreTable){
    MusicGenrePosition userNode = find_musicGenresTable_genre(P->genre, genreTable);
    if(userNode == NULL){
        print_error(300, P->genre, NULL);
        return NULL;
    }
    P->genreNode = userNode;
    return P;
}

/**
 * @brief Obtiene el primer nodo de una lista de enlaces a generos
 *
 * @param linkList Puntero a la lista de enlaces a generos
 * @return Puntero al primer enlace a genero de la lista
*/
GenreLinkPosition genreLinkList_first(GenreLinkList linkList){
    return linkList->next;
}

/**
 * @brief Obtiene el ultimo nodo de una lista de enlaces a generos
 *
 * @param linkList Puntero a la lista de enlaces a generos
 * @return Puntero al ultimo enlace a genero de la lista
*/
GenreLinkPosition genreLinkList_last(GenreLinkList linkList){
    GenreLinkPosition P = linkList->next;
    while (P->next != NULL) {
        P = P->next;
    }
    return P;
}

/**
 * @brief Obtiene el seiguiente nodo a @p P de una lista de enlaces de genero.
 *
 * @param P Nodo del que se quiere obtener el siguiente.
 * @return El siguiente nodo de la lista de enlaces de genero.
*/
GenreLinkPosition genreLinkList_advance(GenreLinkPosition P){
    return P->next;
}


// Funciones de ordenamiento de listas de enlaces a generos

/**
 * @brief Ordena una lista de enlaces a generos usando el algoritmo de intercambio (BubleSort)
 *
 * @param linkList Puntero a la lista de enlaces a generos a ordenar
 * @return Puntero a la lista ordenada
*/
GenreLinkList bubbleSort_genreLinkList(GenreLinkList linkList){
    if(is_empty_genreLinkList(linkList)){
		return linkList;
	}
	unsigned int listSize = 0;
    GenreLinkPosition P = linkList->next;
	while(P != NULL){ // Calculo ineficiente de la cantidad de elementos de la lista
		listSize++;
		P = P->next;
	}
	unsigned int toOrder = listSize-1;

	P=linkList->next;
	while(toOrder > 0){
		for(unsigned int i = 0; i < toOrder; i++){
			if(strcmp(P->genre, P->next->genre) > 0){
				swap_genreLinkList_nodes(P, P->next);
			}
			P = P->next;
		}
		P=linkList->next;
		toOrder--;

	}
	return linkList;
}

/**
 * @brief Intercambia los punteros de dos nodos de una lista de enlaces a generos
 *
 * @param a Puntero al primer nodo a intercambiar
 * @param b Puntero al segundo nodo a intercambiar
*/
void swap_genreLinkList_nodes(GenreLinkPosition a, GenreLinkPosition b){
    GenreLinkNode aux;
    aux = *a;

	a->genre = b->genre;
    a->completed = b->completed;
    a->genreNode = b->genreNode;

	b->genre = aux.genre;
    b->completed = aux.completed;
    b->genreNode = aux.genreNode;
}