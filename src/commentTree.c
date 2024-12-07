/**
 * @file commentTree.c
 * @author Constanza Araya, Rodolfo Cifuentes, Bruno Martinez, Milton Hernández, Guliana Ruiz
 * @brief Funciones para manejo de un árbol de comentarios en loopweb
*/
#include "commentTree.h"

// Utilidades para el AVL

/**
 * @brief Devuelve la altura de un arbol de comentarios
 *
 * @param tree Puntero al nodo del árbol
 * @return Altura del árbol
*/
int height(CommentTree tree)
{
	if (!tree)
		return 0;
	else
		return tree->height;
}

/**
 * @brief Crea un arbol de comentarios vacio
 *
 * @param tree Puntero al nodo del arbol
 * @return CommentTree Puntero a la raíz del arbol
*/
CommentTree make_empty_commentTree(CommentTree tree)
{
    delete_commentTree(tree);
    return NULL;
}

/**
 * @brief Dado un comentario, extrae los tags de su texto y genera las listas de tags del comentario
 *
 * @param comment Comentario a procesar
 * @return Comentario actualizado
*/
CommentTreePosition add_comment_tags(CommentTreePosition comment) {
    printf("Agregando tags del nodo %u\n", comment->commentID);
    comment->bands = create_empty_bandLinkList(comment->bands);
    comment->genres = create_empty_genreLinkList(comment->genres);

    // The existing implementation remains the same
    char* ptr = comment->commentText;
    char* tag_start = NULL;
    char* tag_end = NULL;

    while (*ptr) {
        printf("%c\n", *ptr);
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
    return comment;
}

// Funciones de diccionario
/**
 * @brief Inserta un nodo en un arbol de comentarios
 *
 * @param tree Puntero al nodo del arbol
 * @param commentID Identificador del comentario
 * @param commentText Texto del comentario
 * @param user Puntero al nodo del autor del comentario
 * @param genres Puntero a la lista de gustos musicales del comentario
 * @param bands Puntero a la lista de bandas del comentario
 * @return CommentTreePosition Puntero al nodo insertado
*/
CommentTreePosition insert_commentTree_node(CommentTree tree, unsigned int commentID, time_t timestamp, char* commentText, UserPosition user, GenreLinkPosition genres, BandLinkPosition bands)
{
	// Elemento encontrado
    if (tree == NULL) {
        tree = malloc(sizeof(struct _commentTreeNode));
        if (tree == NULL)
            print_error(200, NULL, NULL);
        else{
            tree->commentID = commentID;
            tree->timestamp = timestamp;
            tree->user = user;
            tree->commentText = malloc(strlen(commentText) + 1);
            strcpy(tree->commentText, commentText);
            tree->genres = genres;
            tree->bands = bands;
            tree->left = tree->right = NULL;
            tree->height = 0;
        }
    }
    // Buscar a la izquierda
    else if (commentID < tree->commentID){
        tree->left = insert_commentTree_node(tree->left, commentID, timestamp, commentText, user, genres, bands);
        // Comprobamos desbalances a la izquierda
        if (height(tree->left) - height(tree->right) == 2) {
            if (commentID < tree->left->commentID)
                tree = single_rotate_with_left(tree);
            else
                tree = double_rotate_with_left(tree);
        }
    }
    // Buscar a la derecha
    else if (commentID > tree->commentID) {
        tree->right = insert_commentTree_node(tree->right, commentID, timestamp, commentText, user, genres, bands);
        // Comprobamos desbalances a la derecha
        if (height(tree->right) - height(tree->left) == 2) {
            if (commentID > tree->right->commentID)
                tree = single_rotate_with_right(tree);
            else
                tree = double_rotate_with_right(tree);
        }
    }
    // Calculamos la altura del nodo actual
    tree->height = max(height(tree->left), height(tree->right)) + 1;
    return tree;
}

/**
 * @brief Busca un nodo en un arbol de comentarios
 *
 * @param tree Arbol en que se busca el nodo
 * @param commentID Identificador del comentario
 * @return CommentTreePosition Puntero al nodo encontrado
*/
CommentTreePosition find_commentTree_node(CommentTree tree, unsigned int commentID)
{
    if(tree == NULL)
        return NULL;
    if(commentID < tree->commentID)
        return find_commentTree_node(tree->left, commentID);
    else if (commentID > tree->commentID)
        return find_commentTree_node(tree->right, commentID);
    else
        return tree;
}

/**
 * @brief Elimina un nodo de un arbol de comentarios
 *
 * @param tree Puntero al nodo del arbol
 * @param commentID Identificador del comentario
 * @return Puntero a la raíz del arbol
*/
CommentTree delete_commentTree_node(CommentTree tree, unsigned int commentID) {
    if (tree == NULL) {
        return NULL;
    }

    // Paso 1: Eliminar como en un ABB
    if (commentID < tree->commentID) {
        tree->left = delete_commentTree_node(tree->left, commentID);
    } else if (commentID > tree->commentID) {
        tree->right = delete_commentTree_node(tree->right, commentID);
    } else {
        // Nodo encontrado
        if (tree->left == NULL || tree->right == NULL) {
            // Caso 1: Nodo con uno o sin hijos
            CommentTree tmp = tree->left ? tree->left : tree->right;

            // Liberar memoria del nodo actual
            delete_genreLinkList(tree->genres);
            delete_bandLinkList(tree->bands);
            free(tree->commentText);
            free(tree);

            return tmp; // Retornar el hijo existente o NULL
        } else {
            // Caso 2: Nodo con dos hijos
            CommentTreePosition aux = find_commentTree_min(tree->right);
            // Copiar datos del sucesor
            tree->commentID = aux->commentID;
            tree->commentText = aux->commentText;
            tree->timestamp = aux->timestamp;
            tree->user = aux->user;
            tree->genres = aux->genres;
            tree->bands = aux->bands;

            // Eliminar el sucesor
            tree->right = delete_commentTree_node(tree->right, aux->commentID);
        }
    }

    // Paso 2: Actualizar altura del nodo actual
    tree->height = max(height(tree->left), height(tree->right)) + 1;

    // Paso 3: Balanceo
    int balance = height(tree->left) - height(tree->right);

    // Rotaciones necesarias
    if (balance > 1) {
        if (height(tree->left->left) >= height(tree->left->right)) {
            tree = single_rotate_with_left(tree); // Rotación simple izquierda
        } else {
            tree = double_rotate_with_left(tree); // Rotación doble izquierda
        }
    } else if (balance < -1) {
        if (height(tree->right->right) >= height(tree->right->left)) {
            tree = single_rotate_with_right(tree); // Rotación simple derecha
        } else {
            tree = double_rotate_with_right(tree); // Rotación doble derecha
        }
    }

    return tree;
}

/**
 * @brief Elimina un arbol de comentarios
 *
 * @param tree Puntero al arbol
*/
void delete_commentTree(CommentTree tree){
    if (tree == NULL) {
        return;
    }

    // Eliminar subárbol izquierdo y derecho
    delete_commentTree(tree->left);
    delete_commentTree(tree->right);

    // Liberar recursos del nodo actual
    delete_genreLinkList(tree->genres);
    delete_bandLinkList(tree->bands);
    free(tree->commentText);
    free(tree);
}

/**
 * @brief Busca el nodo mínimo de un arbol de comentarios
 *
 * @param tree Puntero al nodo del arbol
 * @return Puntero al nodo mínimo
*/
CommentTreePosition find_commentTree_min(CommentTree tree)
{
    if(tree == NULL)
        return NULL;
    else
    if(tree->left == NULL)
        return tree;
    else
        return find_commentTree_min(tree->left);
}

/**
 * @brief Busca el nodo máximo de un arbol de comentarios
 *
 * @param tree Puntero al nodo del arbol
 * @return Puntero al nodo maximo
*/
CommentTreePosition find_commentTree_max(CommentTree tree)
{
    if(tree == NULL)
        return NULL;
    else
    if(tree->right == NULL)
        return tree;
    else
        return find_commentTree_max(tree->right);
}

// Rotaciones
CommentTreePosition single_rotate_with_right(CommentTreePosition A)
{
	CommentTreePosition B; // Nodo auxiliar

	B = A->right; // Guardamos la referencia al nodo B
	A->right = B->left; // Hacemos que Y sea el árbol derecho de A
	B->left = A; // Decimos que A es el hijo izquierdo de B

	// Cambiamos las alturas de los nodos A y B
	A->height = max(height(A->left), height(A->right)) + 1;
	B->height = max(height(B->right), A->height)+ 1;

	return B;
}

CommentTreePosition single_rotate_with_left(CommentTreePosition A)
{
	CommentTreePosition B; // Nodo auxiliar

	B = A->left; // Guardamos la referencia al nodo B
	A->left = B->right; // Hacemos que Y sea el árbol izquierdo de A
	B->right = A; // Decimos que A es el hijo derecho de B

	// Cambiamos las alturas de los nodos A y B
	A->height = max(height(A->left), height(A->right)) + 1;
	B->height = max(height(B->left), A->height) + 1;

	return B;
}

CommentTreePosition double_rotate_with_right(CommentTreePosition A)
{
	A->right = single_rotate_with_left(A->right); // Rotamos el hijo derecho a la derecha
	return single_rotate_with_right(A); // Rotamos A a la Izquierda
}

CommentTreePosition double_rotate_with_left(CommentTreePosition A)
{
	A->left = single_rotate_with_right(A->left); // Rotamos el hijo izquierdo a la izquierda
	return single_rotate_with_left(A); // Rotamos A a la derecha
}


// Impresion y recorrido en AVL

/**
 * @brief Imprime un nodo de un arbol de comentarios en la consola
 *
 * @param node Puntero al nodo a imprimir
*/
void print_commentTree_node(CommentTreePosition node){
    if(node == NULL){
        return;
    }
    printf("ID: %u\n", node->commentID);
    printf("Fecha: %s", ctime(&node->timestamp));
    printf("Texto: ");
    print_loopweb(node->commentText);
    printf("\n");
    printf("Usuario: %s\n", node->user->username);
    printf("Gustos: ");
    print_genreLinkList(node->genres);
    printf("\nBandas: ");
    print_bandLinkList(node->bands);
    printf("\n");
}

/**
 * @brief Imprime un arbol de comentarios en la consola (Pre-orden)
 *
 * @param tree Puntero al nodo del arbol
*/
void print_commentTree(CommentTree tree)
{
	if (tree == NULL){
		return;
    }
	print_commentTree_node(tree);
	printf("Altura: %d\n", height(tree));
	print_commentTree(tree->left);
	print_commentTree(tree->right);
}

/**
 * @brief Completa los tags de un arbol de comentarios
 *
 * @param tree Puntero al arbol
*/
void complete_tree_tags(CommentTree tree){
    if(tree == NULL){
        return;
    }
    add_comment_tags(tree);
    complete_tree_tags(tree->left);
    complete_tree_tags(tree->right);
}