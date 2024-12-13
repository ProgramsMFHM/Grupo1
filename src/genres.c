/**
 * @file genres.c
 * @author Constanza Araya, Rodolfo Cifuentes, Bruno Martinez, Milton Hernández, Guliana Ruiz
 * @brief Funciones para manejo de generos musicales dentro de loopweb
*/

#include "genres.h"

 // Funciones de la lista de generos musicales

 /**
  * @brief Crea una lista vacia de generos musicales
  * @param genreList Puntero a una lista de generos a vaciar, si es necesario
  * @return Puntero al nodo centinela de la lista
*/
GenreList create_empty_genreList(GenreList genreList)
{
    if (!is_empty_genreList(genreList)) {
        delete_genreList(genreList);
    }
    GenreList newList = (GenreList)malloc(sizeof(struct _genre));
    if (newList == NULL) {
        print_error(200, NULL, NULL);
    }
    newList->next = NULL;
    return newList;
}

/**
 * @brief Verifica si una lista de generos musicales esta vacia
 * @param genreList Puntero a la lista de generos
 * @return TRUE si la lista esta vacia, FALSE en caso contrario
*/
bool is_empty_genreList(GenreList genreList)
{
    return genreList == NULL;
}

/**
 * @brief Borra una lista de generos musicales
 * @param genreList Puntero a la lista de generos
*/
void delete_genreList(GenreList genreList)
{
    if (is_empty_genreList(genreList)) {
        return;
    }
    GenrePosition aux = genreList->next;
    while (aux != NULL) {
        delete_genreList_genre(aux, genreList);
        aux = genreList->next;
    }
    free(genreList);
}

/**
 * @brief Imprime una lista de generos musicales en la consola
 * @param genreList Puntero a la lista de generos
*/
void print_genreList(GenreList genreList)
{
    GenrePosition current = genreList->next;
    if (current == NULL) {
        printf("Empty\n");
    } else {
        while (current != NULL) {
            printf("[%s, ", current->genre);
            print_commentLinkList(current->comments);
            printf("]\n\t-> ");
            current = current->next;
        }
        printf("NULL\n");
    }
}

/**
 * @brief Busca un genero en la lista de generos musicales
 * @param genreList Puntero a la lista de generos
 * @param genre Genero a buscar
 * @return Puntero al nodo encontrado, NULL si no se encuentra
*/
GenrePosition find_genreList_genre(GenreList genreList, char* genre)
{
    if (is_empty_genreList(genreList)) {
        return NULL;
    }
    GenrePosition position = genreList_first(genreList);
    while (position != NULL && strcmp(position->genre, genre) != 0) {
        position = position->next;
    }
    return position;
}

/**
 * @brief Encuentra el nodo anterior a un nodo dado en la lista de generos musicales
 * @param position Nodo del cual se busca el anterior
 * @param genreList Puntero a la lista de generos
 * @return Puntero al nodo anterior a @p position
*/
GenrePosition find_genreList_prev_genre(GenrePosition position, GenreList genreList)
{
    GenrePosition aux = genreList;
    while (aux != NULL && aux->next != position) {
        aux = aux->next;
    }
    return aux;
}

/**
 * @brief Inserta un nodo en la lista de generos musicales
 * @param prevPosition Puntero al nodo anterior al que se desea insertar
 * @param genre Genero a insertar
 * @return Puntero al nodo insertado
*/
GenrePosition insert_genreList_genre(GenrePosition prevPosition, char* genre)
{
    GenrePosition newNode = (GenrePosition)malloc(sizeof(struct _genre));
    if (newNode == NULL) {
        print_error(200, NULL, NULL);
    }

    newNode->genre = malloc(strlen(genre) + 1);
    if (newNode->genre == NULL) {
        print_error(200, NULL, NULL);
    }
    snprintf(newNode->genre, strlen(genre) + 1, "%s", genre);

    newNode->comments = create_empty_commentLinkList(NULL);
    newNode->next = prevPosition->next;
    prevPosition->next = newNode;
    return newNode;
}

/**
 * @brief Borra un nodo de la lista de generos musicales
 * @param position Puntero al nodo a borrar
 * @param genreList Puntero a la lista de generos a la que pertenece @p position
*/
void delete_genreList_genre(GenrePosition position, GenreList genreList)
{
    if (position == NULL) {
        print_error(203, NULL, NULL);
    }
    GenrePosition prevNode = find_genreList_prev_genre(position, genreList);
    if (prevNode == NULL) {
        print_error(301, NULL, NULL);
        return;
    }
    prevNode->next = position->next;
    delete_commentLinkList(position->comments);
    free(position->genre);
    free(position);
}

// Funciones de interaccion con el usuario

/**
 * @brief Obtiene el primer nodo de una lista de generos musicales
 * @param genreList Puntero a la lista de generos
 * @return Puntero al primer genero de la lista
*/
GenrePosition genreList_first(GenreList genreList)
{
    return genreList->next;
}

/**
 * @brief Obtiene el ultimo nodo de una lista de generos musicales
 * @param genreList Puntero a la lista de generos
 * @return Puntero al ultimo genero de la lista
*/
GenrePosition genreList_last(GenreList genreList)
{
    GenrePosition position = genreList->next;
    while (position->next != NULL) {
        position = position->next;
    }
    return position;
}

/**
 * @brief Avanza al siguiente nodo en la lista de generos musicales
 * @param position Puntero al genero actual
 * @return Puntero al siguiente genero de la lista
*/
GenrePosition genreList_advance(GenrePosition position)
{
    return position->next;
}

/**
 * @brief Obtiene el genero almacenado en un nodo
 * @param position Puntero al nodo
 * @return Genero almacenado en el nodo
*/
char* get_genre(GenrePosition position)
{
    return position->genre;
}

// Funciones de la tabla de generos musicales

/**
 * @brief Crea una tabla de generos musicales
 * @param genresTable Puntero a una tabla de generos a vaciar, si es necesario
 * @return Puntero a la tabla creada
*/
GenreTable create_genresTable(GenreTable genresTable)
{
    if (genresTable != NULL) {
        delete_genresTable(genresTable);
    }

    genresTable = (GenreTable)malloc(sizeof(struct _genreTable));
    if (!genresTable) {
        print_error(200, NULL, NULL);
    }

    for (int i = 0; i < GENRE_TABLE_SIZE; i++) {
        genresTable->buckets[i] = create_empty_genreList(NULL);
        genresTable->genreCount = 0;
    }
    genresTable->modified = false;
    return genresTable;
}

/**
 * @brief Imprime una tabla de generos musicales en la consola
 * @param genresTable Tabla de generos musicales a imprimir
*/
void print_genresTable(GenreTable genresTable)
{
    printf("Generos de la red (%d):\n", genresTable->genreCount);
    for(int i=0; i<GENRE_TABLE_SIZE; i++){
        printf("Bucket %2d: ", i);
        print_genreList(genresTable->buckets[i]);
    }
}

/**
 * @brief Inserta un genero en una tabla de generos musicales
 * @param genre Genero a insertar
 * @param genresTable Tabla de generos musicales donde insertar el genero
 * @return Puntero al nodo insertado
*/
GenrePosition insert_genre(char* genre, GenreTable genresTable)
{
    unsigned int index = jenkins_hash(genre) % GENRE_TABLE_SIZE;
    GenrePosition position = insert_genreList_genre(genresTable->buckets[index], genre);
    if (position != NULL) {
        genresTable->genreCount++;
    }
    genresTable->modified = true;
    return position;
}

/**
 * @brief Borra un genero de una tabla de generos musicales
 * @param genre Genero a borrar
 * @param genresTable Tabla de generos musicales donde buscar el genero
*/
void delete_genresTable_genre(char* genre, GenreTable genresTable)
{
    int index = jenkins_hash(genre) % GENRE_TABLE_SIZE;
    GenrePosition position = find_genreList_genre(genresTable->buckets[index], genre);
    if (position == NULL) {
        print_error(301, NULL, NULL);
        return;
    }
    delete_genreList_genre(position, genresTable->buckets[index]);
    genresTable->genreCount--;
    genresTable->modified = true;
}

/**
 * @brief Borra una tabla de generos musicales
 * @param genresTable Tabla de generos musicales a borrar
*/
void delete_genresTable(GenreTable genresTable)
{
    for (int i = 0; i < GENRE_TABLE_SIZE; i++) {
        delete_genreList(genresTable->buckets[i]);
    }
    free(genresTable);
}

/**
 * @brief Verifica si un genero esta en la tabla de generos musicales
 * @param genre Genero a verificar
 * @param genresTable Tabla de generos musicales donde buscar
 * @return TRUE si el genero esta en la tabla, FALSE en caso contrario
*/
GenrePosition find_genresTable_genre(char* genre, GenreTable genresTable)
{
    int index = jenkins_hash(genre) % GENRE_TABLE_SIZE;
    return find_genreList_genre(genresTable->buckets[index], genre);
}

/**
 * @brief Funcion para guardar una tabla de generos musicales en su archivo JSON correspondiente
 *
 * @param bandTable Tabla de generos a guardar
*/
void save_genresTable(GenreTable bandTable)
{
    FILE* genresTableFile = fopen("./build/genres.json", "w");
    if (genresTableFile == NULL)
    {
        print_error(100, "./build/genres.json", NULL);
        return;
    }

    fprintf(genresTableFile, "[\n");
    for(int i=0; i<BANDS_TABLE_SIZE; i++)
    {
        if(!bandTable->buckets[i]->next){
            continue;
        }
        if(i != 0){
            fprintf(genresTableFile, ",\n");
        }
        GenrePosition aux = bandTable->buckets[i]->next;
        while(aux != NULL){
            fprintf(genresTableFile, "\t{\n\t\t\"genre\":\"%s\",\n\t\t\"comments\":[", aux->genre);
            if(aux->comments->next){
                CommentLinkPosition aux2 = aux->comments->next;
                while(aux2 != NULL){
                    fprintf(genresTableFile, "%ld", aux2->commentID);
                    if(aux2->next != NULL){
                        fprintf(genresTableFile, ", ");
                    }
                    aux2 = aux2->next;
                }
            }
            fprintf(genresTableFile, "]\n\t}");
            if(aux->next != NULL){
                fprintf(genresTableFile, ",\n");
            }
            aux = aux->next;
        }
    }
    fprintf(genresTableFile, "\n]");
    fclose(genresTableFile);
}

// Funciones de LoopWeb relacionadas a geberos

/**
 * @brief Imprime de manera estetica la tabla de generos y devuelve la lista de enlaces a a todos los generos
 *
 * @param table Puntero a la tabla de generos
 * @return Puntero a la lista de enlaces a todos los generos de la red ordenados alfabeticamente
*/
GenreLinkList get_loopweb_genres(GenreTable table)
{
    GenreLinkList allGenres = create_empty_genreLinkList(NULL);

    for(int i=0; i<GENRE_TABLE_SIZE; i++){
        GenrePosition aux = table->buckets[i]->next;
        while(aux != NULL){
            insert_genreLinkList_node_completeInfo(allGenres, aux);
            aux = aux->next;
        }
    }
    sort_genreLinkList_byName(&allGenres->next);
    GenreLinkPosition current = allGenres->next;
    int counter = 1;
    while (current != NULL) {
        printf("%3d. "ANSI_COLOR_RED"%-17s"ANSI_COLOR_RESET, counter, current->genre);
        if(counter % 5 == 0){
            printf("\n");
        }
        counter++;
        current = current->next;
    }
    printf("\n\n");
    return allGenres;
}