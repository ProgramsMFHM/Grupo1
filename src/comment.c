/**
 * @file comment.c
 * @author Constanza Araya, Rodolfo Cifuentes, Bruno Martinez, Milton Hernández, Guliana Ruiz
 * @brief Funciones para manejo de comentarios dentro de loopweb
*/

#include <comment.h>

/**
 * @brief Funcion para crear una lista vacia
 * 
 * @param list Puntero a la lista a crear ¿
 * @return Lista vacia
*/
CommentList make_empty_comment_list(CommentList list) {
    if(list != NULL) {
        delete_comment_list(list);
    }

    list = (CommentList)malloc(sizeof(Comment));
    if (list == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return NULL;
    }
    list->next = NULL;

    return list;
}

/**
 * @brief Funcion para crear un nodo de la lista
 * 
 * @param text Texto del comentario
 * @return Puntero al nodo creado
*/
CommentPosition create_comment_node(const char* text) {
    CommentList new_node = (Comment*)malloc(sizeof(Comment));
    if (new_node == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return NULL;
    }
    
    strncpy(new_node->Text, text, MAX_COMMENT_LENGTH - 1);
    new_node->Text[MAX_COMMENT_LENGTH - 1] = '\0';

    new_node->GenreCount = 0;
    new_node->BandCount = 0;
    new_node->next = NULL;

    add_tags(new_node);

    return new_node;
}

/**
 * @brief Funcion para agregar un comentario a una lista de comentarios
 * 
 * @param prev Nodo anterior al que se agregara el comentario
 * @param text Texto del comentario
 * @return Puntero al nuevo comentario
*/
CommentPosition append_comment(CommentPosition prev, const char* text) {
    if (prev == NULL) {
        printf("Error: Nodo anterior nulo\n");
        return NULL;
    }

    PtrToComment new_node = create_comment_node(text);
    if (new_node == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return NULL;
    }

    new_node->next = prev->next;
    prev->next = new_node;

    return new_node;
}

/**
 * @brief Funcion para leer todos los comentarios de un archivo
 * 
 * @param list Lista de comentarios
 * @param filename Ruta al archivo
 * @return Lista de comentarios actualizada
*/
CommentList read_comments_from_file(CommentList list, const char* filename) {
    if (list == NULL) {
        list = make_empty_comment_list(list);
    }

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: incapaz de abrir el archivo %s\n", filename);
        return NULL;
    }

    char buffer[MAX_COMMENT_LENGTH];
    char paragraph[MAX_COMMENT_LENGTH] = "";

    while (fgets(buffer, sizeof(buffer), file)) {
        if (buffer[0] == '\n' || buffer[0] == '\r') {
            if (paragraph[0] != '\0') {
                append_comment(list, paragraph);
                paragraph[0] = '\0';
            }
        } else {
            if (strlen(paragraph) + strlen(buffer) < MAX_COMMENT_LENGTH - 1) {
                strcat(paragraph, buffer);
            }
        }
    }

    if (paragraph[0] != '\0') {
        append_comment(list, paragraph);
    }

    fclose(file);
    return list;
}

/**
 * @brief Funcion para imprimir todos los comentarios de una lista
 * 
 * @param list Lista de comentarios
*/
void print_comments(CommentList list) {
    const Comment* current = list->next;
    int i = 1;

    if(current == NULL) {
        printf("Lista vacia\n");
        return;
    }
    
    while (current != NULL) {
        printf("Comentario %d:\n", i++);
        printf("Texto: %s\n", current->Text);
        
        //géneros
        printf("Géneros: ");
        
        printf("%d ", current->GenreCount);
        //printf("%s ", current->GenreLikes[j]);
        
        printf("\n");
        
        //bandas
        printf("Bandas: ");
        printf("%d ", current->BandCount);
        //printf("%s ", current->BandLikes[j]);

        printf("\n");
        
        printf("----------------------------------------\n");
        current = current->next;
    }
}

/**
 * @brief Eliminar todas las listas de comentarios
 * 
 * @param list Lista de comentarios a eliminar
*/
void delete_comment_list(CommentList list) {
    CommentList current, next;
    current = list->next;
    while (current != NULL) {
        next = current->next;
        free(current);
        list->next = next;
        current = next;
    }
    free(list);
}


//funciones para manejar tags

/**
 * @brief Dado un comentario, extrae los tags de su texto y genera las listas de tags del comentario
 * 
 * @param comment Comentario a procesar
 * @return Comentario actualizado
*/
CommentList add_tags(CommentList comment) {
    // The existing implementation remains the same
    char* ptr = comment->Text;
    char* tag_start = NULL;
    char* tag_end = NULL;

    // Reiniciar contadores
    comment->GenreCount = 0;
    comment->BandCount = 0;
    
    while (*ptr) {
        // Procesar hashtags para géneros
        if (*ptr == '#') {
            if (comment->GenreCount < MAX_TAGS) {
                tag_start = ptr + 1;
                tag_end = tag_start;
                
                // Encontrar el final del hashtag
                while (*tag_end && 
                       (isalnum(*tag_end) || *tag_end == '_')) {
                    tag_end++;
                }
                
                // Verificar si se encontró un tag válido
                if (tag_end > tag_start) {
                    size_t tag_length = tag_end - tag_start;
                    strncpy(comment->GenreLikes[comment->GenreCount], 
                            tag_start, 
                            tag_length);
                    comment->GenreLikes[comment->GenreCount][tag_length] = '\0';
                    
                    comment->GenreCount++;
                }
                
                // Actualizar puntero
                ptr = tag_end;
            }
            else {
                // Si se alcanzan los máximos tags, saltar
                while (*ptr && (isalnum(*ptr) || *ptr == '_')) {
                    ptr++;
                }
            }
        }
        // Procesar menciones para bandas
        else if (*ptr == '@') {
            if (comment->BandCount < MAX_TAGS) {
                tag_start = ptr + 1;
                tag_end = tag_start;
                
                // Encontrar el final de la mención
                while (*tag_end && 
                       (isalnum(*tag_end) || *tag_end == '_')) {
                    tag_end++;
                }
                
                // Verificar si se encontró un tag válido
                if (tag_end > tag_start) {
                    size_t tag_length = tag_end - tag_start;
                    strncpy(comment->BandLikes[comment->BandCount], 
                            tag_start,
                            tag_length);
                    comment->BandLikes[comment->BandCount][tag_length] = '\0';
                    
                    comment->BandCount++;
                }
                
                // Actualizar puntero
                ptr = tag_end;
            }
            else {
                // Si se alcanzan los máximos tags, saltar
                while (*ptr && (isalnum(*ptr) || *ptr == '_')) {
                    ptr++;
                }
            }
        }
        else {
            ptr++;
        }
    }
    return comment;
}