/**
 * @file musicGenres.c
 * @author Constanza Araya, Rodolfo Cifuentes, Bruno Martinez, Milton Hernández, Guliana Ruiz
 * @brief Funciones para manejo de generos musicales dentro de loopweb
*/

#include "musicGenres.h"

 // Funciones de la lista de generos musicales

 /**
  * @brief Crea una lista vacia de generos musicales
  * @param genreList Puntero a una lista de generos a vaciar, si es necesario
  * @return Puntero al nodo centinela de la lista
*/
MusicGenreList create_empty_musicGenreList(MusicGenreList genreList)
{
    if (!is_empty_musicGenreList(genreList)) {
        delete_musicGenreList(genreList);
    }
    MusicGenreList newList = (MusicGenreList)malloc(sizeof(struct _musicGenre));
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
bool is_empty_musicGenreList(MusicGenreList genreList)
{
    return genreList == NULL;
}

/**
 * @brief Borra una lista de generos musicales
 * @param genreList Puntero a la lista de generos
*/
void delete_musicGenreList(MusicGenreList genreList)
{
    if (is_empty_musicGenreList(genreList)) {
        return;
    }
    MusicGenrePosition aux = genreList->next;
    while (aux != NULL) {
        delete_musicGenreList_genre(aux, genreList);
        aux = genreList->next;
    }
    free(genreList);
}

/**
 * @brief Imprime una lista de generos musicales en la consola
 * @param genreList Puntero a la lista de generos
*/
void print_musicGenreList(MusicGenreList genreList)
{
    MusicGenrePosition position = musicGenreList_first(genreList);

    while (position != NULL) {
        printf("%s\n", position->genre);
        position = position->next;
    }
}

/**
 * @brief Busca un genero en la lista de generos musicales
 * @param genreList Puntero a la lista de generos
 * @param genre Genero a buscar
 * @return Puntero al nodo encontrado, NULL si no se encuentra
*/
MusicGenrePosition find_musicGenreList_genre(MusicGenreList genreList, char* genre)
{
    if (is_empty_musicGenreList(genreList)) {
        return NULL;
    }
    MusicGenrePosition position = musicGenreList_first(genreList);
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
MusicGenrePosition find_musicGenreList_prev_genre(MusicGenrePosition position, MusicGenreList genreList)
{
    MusicGenrePosition aux = genreList;
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
MusicGenrePosition insert_musicGenreList_genre(MusicGenrePosition prevPosition, char* genre)
{
    MusicGenrePosition newNode = (MusicGenrePosition)malloc(sizeof(struct _musicGenre));
    if (newNode == NULL) {
        print_error(200, NULL, NULL);
    }
    newNode->next = prevPosition->next;
    prevPosition->next = newNode;
    snprintf(newNode->genre, sizeof(newNode->genre), "%s", genre);
    return newNode;
}

/**
 * @brief Borra un nodo de la lista de generos musicales
 * @param position Puntero al nodo a borrar
 * @param genreList Puntero a la lista de generos a la que pertenece @p position
*/
void delete_musicGenreList_genre(MusicGenrePosition position, MusicGenreList genreList)
{
    if (position == NULL) {
        print_error(203, NULL, NULL);
    }
    MusicGenrePosition prevNode = find_musicGenreList_prev_genre(position, genreList);
    if (prevNode == NULL) {
        print_error(301, NULL, NULL);
        return;
    }
    prevNode->next = position->next;
    free(position);
}

// Funciones de interaccion con el usuario

/**
 * @brief Obtiene el primer nodo de una lista de generos musicales
 * @param genreList Puntero a la lista de generos
 * @return Puntero al primer genero de la lista
*/
MusicGenrePosition musicGenreList_first(MusicGenreList genreList)
{
    return genreList->next;
}

/**
 * @brief Obtiene el ultimo nodo de una lista de generos musicales
 * @param genreList Puntero a la lista de generos
 * @return Puntero al ultimo genero de la lista
*/
MusicGenrePosition musicGenreList_last(MusicGenreList genreList)
{
    MusicGenrePosition position = genreList->next;
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
MusicGenrePosition musicGenreList_advance(MusicGenrePosition position)
{
    return position->next;
}

/**
 * @brief Obtiene el genero almacenado en un nodo
 * @param position Puntero al nodo
 * @return Genero almacenado en el nodo
*/
char* get_genre(MusicGenrePosition position)
{
    return position->genre;
}

// Funciones de la tabla de generos musicales

/**
 * @brief Crea una tabla de generos musicales
 * @param genresTable Puntero a una tabla de generos a vaciar, si es necesario
 * @return Puntero a la tabla creada
*/
MusicGenresTable create_musicGenresTable(MusicGenresTable genresTable)
{
    if (genresTable != NULL) {
        delete_musicGenresTable(genresTable);
    }

    genresTable = (MusicGenresTable)malloc(sizeof(struct _musicHashTable) * MUSIC_GENRES_HASH_SIZE);
    if (!genresTable) {
        print_error(200, NULL, NULL);
    }

    for (int i = 0; i < MUSIC_GENRES_HASH_SIZE; i++) {
        genresTable[i].genreList = create_empty_musicGenreList(NULL);
        genresTable[i].nodeCount = 0;
    }

    return genresTable;
}

/**
 * @brief Lee generos de un archivo e inserta en una tabla de generos musicales
 * @param fileName Nombre del archivo a leer
 * @param genresTable Tabla de generos musicales donde insertar los generos
 * @return Tabla de generos musicales con los generos leidos
*/
MusicGenresTable read_musicGenre_file(char* fileName, MusicGenresTable genresTable)
{
    FILE* file = fopen(fileName, "r");
    char readGenre[25];

    if (file == NULL) {
        print_error(100, fileName, NULL);
    }

    if (genresTable == NULL) {
        genresTable = create_musicGenresTable(NULL);
    }

    while (fscanf(file, "%s", readGenre) != EOF) {
        insert_musicGenre(readGenre, genresTable);
    }

    fclose(file);
    return genresTable;
}

/**
 * @brief Imprime una tabla de generos musicales en la consola
 * @param genresTable Tabla de generos musicales a imprimir
*/
void print_musicGenresTable(MusicGenresTable genresTable)
{
    for (int i = 0; i < MUSIC_GENRES_HASH_SIZE; i++) {
        printf("-----------------------------\n");
        printf("Hash key: %d\n", i);
        print_musicGenreList(genresTable[i].genreList);
        printf("\n\n");
    }
}

/**
 * @brief Inserta un genero en una tabla de generos musicales
 * @param genre Genero a insertar
 * @param genresTable Tabla de generos musicales donde insertar el genero
 * @return Puntero al nodo insertado
*/
MusicGenrePosition insert_musicGenre(char* genre, MusicGenresTable genresTable)
{
    unsigned int index = jenkins_hash(genre) % MUSIC_GENRES_HASH_SIZE;
    MusicGenrePosition position = insert_musicGenreList_genre(genresTable[index].genreList, genre);
    if (position != NULL) {
        genresTable[index].nodeCount++;
    }
    return position;
}

/**
 * @brief Borra un genero de una tabla de generos musicales
 * @param genre Genero a borrar
 * @param genresTable Tabla de generos musicales donde buscar el genero
*/
void delete_musicGenresTable_genre(char* genre, MusicGenresTable genresTable)
{
    int index = jenkins_hash(genre) % MUSIC_GENRES_HASH_SIZE;
    MusicGenrePosition position = find_musicGenreList_genre(genresTable[index].genreList, genre);
    if (position == NULL) {
        print_error(301, NULL, NULL);
        return;
    }
    delete_musicGenreList_genre(position, genresTable[index].genreList);
    genresTable[index].nodeCount--;
}

/**
 * @brief Borra una tabla de generos musicales
 * @param genresTable Tabla de generos musicales a borrar
*/
void delete_musicGenresTable(MusicGenresTable genresTable)
{
    for (int i = 0; i < MUSIC_GENRES_HASH_SIZE; i++) {
        delete_musicGenreList(genresTable[i].genreList);
    }
    free(genresTable);
}

/**
 * @brief Verifica si un genero esta en la tabla de generos musicales
 * @param genre Genero a verificar
 * @param genresTable Tabla de generos musicales donde buscar
 * @return TRUE si el genero esta en la tabla, FALSE en caso contrario
*/
MusicGenrePosition find_musicGenresTable_genre(char* genre, MusicGenresTable genresTable)
{
    int index = jenkins_hash(genre) % MUSIC_GENRES_HASH_SIZE;
    return find_musicGenreList_genre(genresTable[index].genreList, genre);
}
