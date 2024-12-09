/**
 * @file comment.c
 * @author Constanza Araya, Rodolfo Cifuentes, Bruno Martinez, Milton Hernández, Guliana Ruiz
 * @brief Funciones para manejo de commentarios dentro de loopweb
*/
#include "comments.h"

// Funciones para un nodo de usuario

/**
 * @brief Imprime un comentario en su archivo en formato JSON
 *
 * @param comment Puntero al nodo de comentario
*/
void save_commentNode(PtrToComment comment){
    if(comment == NULL
        || comment->bands == NULL
        || comment->genres == NULL
        || comment->text == NULL
        || comment->user.userName == NULL
        )
    {
        print_error(202, NULL, NULL);
    }

    char commentID[20];
    sprintf(commentID, "%ld", comment->ID);

    char filename[strlen(commentID) + strlen(COMMENTS_PATH) + 6];
    sprintf(filename, COMMENTS_PATH"%s.json", commentID);

    #ifdef DEBUG
        printf("Guardando comentario %s en el archivo %s\n", commentID, filename);
    #endif

    FILE *file = fopen(filename, "w");
    if(file == NULL){
        print_error(100, filename, NULL);
        return;
    }

    fprintf(file, "{\n");
    fprintf(file,"\t\"author\": \"%s\",\n", comment->user.userName);
    fprintf(file,"\t\"ID\": %ld,\n", comment->ID);
    fprintf(file,"\t\"text\": \"%s\",\n", comment->text);
    fprintf(file, "}\n");
    fclose(file);
}

// Funciones de la lista de comentarios
/**
 * @brief Crea una lista vacia de comentarios
 *
 * @param commentList Puntero a una lista de comentarios a vaciar, si es necesario
 * @return Puntero al nodo centinela de la lista
*/
CommentList create_empty_CommentList(CommentList commentList){
    if(!is_empty_CommentList(commentList)){
        delete_CommentList(commentList);
    }
    CommentList newList = (CommentList) malloc(sizeof(struct _commentNode));
    if(newList == NULL){
        print_error(200, NULL, NULL);
    }
    newList->next = NULL;
    return newList;
}

/**
 * @brief Borra una lista de comentarios
 *
 * @param commentList Puntero a la lista de comentarios a borrar
*/
void delete_CommentList(CommentList commentList){
    if(is_empty_CommentList(commentList)){
        return;
    }
    CommentPosition aux = commentList_first(commentList);
    while(aux != NULL){
        delete_CommentList_node(aux, commentList);
        aux = commentList_first(commentList);
    }
    free(commentList);
}

/**
 * @brief Verifica si una lista de comentarios esta vacia
 *
 * @param commentList Puntero a la lista de comentarios
 * @return true si la lista esta vacia, false en caso contrario
*/
bool is_empty_CommentList(CommentList commentList){
    return commentList == NULL;
}

/**
 * @brief Imprime una lista de comentarios en la consola
 *
 * @param commentList Puntero a la lista de comentarios
*/
void print_CommentList(CommentList commentList){
    CommentPosition current = commentList->next;
    if (current == NULL) {
        printf("Empty\n");
    } else {
        while (current != NULL) {
            if(!current->complete){
                complete_comment_tags(current);
            }
            printf("%ld, %s, #:", current->ID, current->text);
            print_genreLinkList(current->genres);
            printf(", @:");
            print_bandLinkList(current->bands);
            printf("\n");
            current = current->next;
        }
    }
}

/**
 * @brief Busca un usuario en la lista de comentarios por su commentname
 *
 * @param commentList Lista de comentarios
 * @param commentname Nombre del usuario a buscar
 * @return Puntero al nodo encontrado, NULL si no se encuentra
*/
CommentPosition find_CommentList_node(CommentList commentList, time_t ID){
    if(is_empty_CommentList(commentList)){
        return NULL;
    }
    CommentPosition P = commentList_first(commentList);
    while (P != NULL &&  P->ID != ID) {
        P = P->next;
    }
    return P;
}

/**
 * @brief Encuentra el nodo anterior a un nodo dado en la lista de comentarios
 *
 * @param P Nodo del cual se busca el anterior
 * @param commentList Puntero a la lista de comentarios
 * @return Puntero al nodo anterior a @p P
*/
CommentPosition find_CommentList_prev_node(CommentPosition P, CommentList commentList){
    CommentPosition aux = commentList;
    while (aux != NULL && aux->next->ID != P->ID){
        aux = aux->next;
    }
    return aux;
}

/**
 * @brief Crea el nodo correspondiente a un usuario
 *
 * @param commentname Nombre del usuario
 * @param age Edad del usuario
 * @param nationality Nacionalidad del usuario
 * @param genres0 Gustos musicales del usuario
 * @return Puntero al nodo creado
*/
CommentPosition create_new_comment(time_t ID, const char *text, char* author){
    PtrToComment newComment = (PtrToComment) malloc(sizeof(CommentNode));
    if (newComment == NULL) {
        print_error(200, NULL, NULL);
    }

    newComment->ID = ID;
    newComment->text = malloc(strlen(text) + 1);
    if(newComment->text == NULL){
        print_error(200, NULL, NULL);
    }
    strcpy(newComment->text, text);

    newComment->user.userName = malloc(strlen(author) + 1);
    if(newComment->user.userName == NULL){
        print_error(200, NULL, NULL);
    }
    strcpy(newComment->user.userName, author);

    newComment->bands = create_empty_bandLinkList(NULL);
    newComment->genres = create_empty_genreLinkList(NULL);
    newComment->complete = false;
    newComment->next = NULL;
    return newComment;
}

/**
 * @brief Inserta un nodo de usuario en una lista de comentarios
 *
 * @param prevPosition Puntero al nodo anterior al que se desea insertar
 * @param newNode Puntero al nodo a insertar
 * @return Puntero al nodo insertado
*/
CommentPosition insert_CommentList_node(CommentPosition prevPosition, CommentPosition newNode){
    newNode->next = prevPosition->next;
    prevPosition->next = newNode;
    return newNode;
}

/**
 * @brief Completa un nodo de una lista de comentarios
 *
 * @param P Puntero al nodo a completar
 * @return Puntero al nodo completado
*/
CommentPosition complete_commentList_node(CommentPosition P, UserTable userTable){
    if(P->text == NULL){
        print_error(202, NULL, NULL);
    }
    if(!P->complete){
        complete_comment_tags(P);
    }
    if(!P->user.userNode){
        P->user.userNode = find_userTable_node(userTable, P->user.userName);
        if(!P->user.userNode){
            print_error(300, P->user.userName, NULL);
        }
    }
    return P;
}

/**
 * @brief Borra un nodo de una lista de comentarios
 *
 * @param P Puntero al nodo a borrar
 * @param commentList Puntero a la lista de comentarios a la que pertenece @p P
 * @return true si el nodo fue borrado, false en caso contrario (si no existe)
*/
bool delete_CommentList_node(CommentPosition P, CommentList commentList){
    if(P == NULL){
        print_error(202, NULL, NULL);
    }
    CommentPosition prevNode = find_CommentList_prev_node(P, commentList);
    if(prevNode == NULL){
        char commentID[20];
        sprintf(commentID, "%ld", P->ID);
        print_error(303, commentID, NULL);
        return false;
    }
    prevNode->next = P->next;
    delete_genreLinkList(P->genres);
    delete_bandLinkList(P->bands);
    free(P->user.userName);
    free(P->text);
    free(P);
    return true;
}

// Funciones de interaccion con el usuario
/**
 * @brief Obtiene el primer nodo de una lista de comentarios
 *
 * @param commentList Puntero a la lista de comentarios
 * @return Puntero al primer usuario de la lista
*/
CommentPosition commentList_first(CommentList commentList){
    return commentList->next;
}

/**
 * @brief Obtiene el ultimo nodo de una lista de comentarios
 *
 * @param commentList Puntero a la lista de comentarios
 * @return Puntero al ultimo usuario de la lista
*/
CommentPosition commentList_last(CommentList commentList){
    CommentPosition P = commentList->next;
    while (P->next != NULL) {
        P = P->next;
    }
    return P;
}

/**
 * @brief Avanza al siguiente nodo en la lista de comentarios
 *
 * @param P Puntero al usuario actual
 * @return Puntero al siguiente usuario de la lista
*/
CommentPosition commentList_advance(CommentPosition P){
    return P->next;
}

// Ordenamiento y completacion
CommentPosition complete_comment_tags(CommentPosition comment){
    #ifdef DEBUG
        printf("Agregando tags del nodo %ld\n", comment->ID);
    #endif
    comment->bands = create_empty_bandLinkList(comment->bands);
    comment->genres = create_empty_genreLinkList(comment->genres);

    // The existing implementation remains the same
    char* ptr = comment->text;
    char* tag_start = NULL;
    char* tag_end = NULL;

    while (*ptr) {
        // Procesar hashtags para géneros
        if (*ptr == '#') {
            tag_start = ptr + 1;
            tag_end = tag_start;

            // Encontrar el final del hashtag
            while (*tag_end && (isalnum(*tag_end) || *tag_end == '_')) {
                tag_end++;
            }
            // Verificar si se encontró un tag válido
            if (tag_end > tag_start) {
                size_t tag_length = tag_end - tag_start;
                char* genre = malloc(tag_length + 1);
                strncpy(genre, tag_start, tag_length);
                genre[tag_length] = '\0';
                insert_genreLinkList_node_basicInfo(comment->genres, genre);
                free(genre);
            }
            // Actualizar puntero
            ptr = tag_end;
        }
        // Procesar menciones para bandas
        else if (*ptr == '@') {
                tag_start = ptr + 1;
                tag_end = tag_start;
                // Encontrar el final de la mención
                while (*tag_end && (isalnum(*tag_end) || *tag_end == '_')) {
                    tag_end++;
                }
                // Verificar si se encontró un tag válido
                if (tag_end > tag_start) {
                    size_t tag_length = tag_end - tag_start;
                    char* band = malloc(tag_length + 1);
                    strncpy(band, tag_start, tag_length);
                    band[tag_length] = '\0';
                    insert_bandLinkList_node_basicInfo(comment->bands, band);
                    free(band);
                }
                // Actualizar puntero
                ptr = tag_end;
        }
        else {
            ptr++;
        }
    }
    comment->complete = true;
    return comment;
}