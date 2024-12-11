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
    MusicGenrePosition current = genreList->next;
    if (current == NULL) {
        printf("Empty\n");
    } else {
        while (current != NULL) {
            printf("[%s, ", current->genre);
            print_CommentList(current->comments);
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
MusicGenrePosition insert_musicGenreList_genre(MusicGenrePosition prevPosition, char* genre, CommentList comments)
{
    MusicGenrePosition newNode = (MusicGenrePosition)malloc(sizeof(struct _musicGenre));
    if (newNode == NULL) {
        print_error(200, NULL, NULL);
    }

    newNode->genre = malloc(strlen(genre) + 1);
    if (newNode->genre == NULL) {
        print_error(200, NULL, NULL);
    }
    snprintf(newNode->genre, strlen(genre) + 1, "%s", genre);

    newNode->comments = comments;
    newNode->next = prevPosition->next;
    prevPosition->next = newNode;
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
    delete_CommentList(position->comments);
    free(position->genre);
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

    genresTable = (MusicGenresTable)malloc(sizeof(struct _musicHashTable));
    if (!genresTable) {
        print_error(200, NULL, NULL);
    }

    for (int i = 0; i < MUSIC_GENRES_TABLE_SIZE; i++) {
        genresTable->buckets[i] = create_empty_musicGenreList(NULL);
        genresTable->genreCount = 0;
    }
    genresTable->modified = false;
    return genresTable;
}

/**
 * @brief Imprime una tabla de generos musicales en la consola
 * @param genresTable Tabla de generos musicales a imprimir
*/
void print_musicGenresTable(MusicGenresTable genresTable)
{
    printf("Generos de la red (%d):\n", genresTable->genreCount);
    for(int i=0; i<MUSIC_GENRES_TABLE_SIZE; i++){
        printf("Bucket %2d: ", i);
        print_musicGenreList(genresTable->buckets[i]);
    }
}

/**
 * @brief Inserta un genero en una tabla de generos musicales
 * @param genre Genero a insertar
 * @param genresTable Tabla de generos musicales donde insertar el genero
 * @return Puntero al nodo insertado
*/
MusicGenrePosition insert_musicGenre(char* genre, CommentList comments, MusicGenresTable genresTable)
{
    unsigned int index = jenkins_hash(genre) % MUSIC_GENRES_TABLE_SIZE;
    MusicGenrePosition position = insert_musicGenreList_genre(genresTable->buckets[index], genre, comments);
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
void delete_musicGenresTable_genre(char* genre, MusicGenresTable genresTable)
{
    int index = jenkins_hash(genre) % MUSIC_GENRES_TABLE_SIZE;
    MusicGenrePosition position = find_musicGenreList_genre(genresTable->buckets[index], genre);
    if (position == NULL) {
        print_error(301, NULL, NULL);
        return;
    }
    delete_musicGenreList_genre(position, genresTable->buckets[index]);
    genresTable->genreCount--;
    genresTable->modified = true;
}

/**
 * @brief Borra una tabla de generos musicales
 * @param genresTable Tabla de generos musicales a borrar
*/
void delete_musicGenresTable(MusicGenresTable genresTable)
{
    for (int i = 0; i < MUSIC_GENRES_TABLE_SIZE; i++) {
        delete_musicGenreList(genresTable->buckets[i]);
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
    int index = jenkins_hash(genre) % MUSIC_GENRES_TABLE_SIZE;
    return find_musicGenreList_genre(genresTable->buckets[index], genre);
}

/**
 * @brief Funcion para guardar una tabla de generos musicales en su archivo JSON correspondiente
 *
 * @param bandTable Tabla de generos a guardar
*/
void save_musicGenresTable(MusicGenresTable bandTable)
{
    FILE* musicGenresTableFile = fopen("./build/music_genres.json", "w");
    if (musicGenresTableFile == NULL)
    {
        print_error(100, "./build/music_genres.json", NULL);
        return;
    }

    fprintf(musicGenresTableFile, "[\n");
    for(int i=0; i<BANDS_TABLE_SIZE; i++)
    {
        if(!bandTable->buckets[i]->next){
            continue;
        }
        if(i != 0){
            fprintf(musicGenresTableFile, ",\n");
        }
        MusicGenrePosition aux = bandTable->buckets[i]->next;
        while(aux != NULL){
            fprintf(musicGenresTableFile, "\t{\n\t\t\"genre\":\"%s\",\n\t\t\"comments\":[", aux->genre);
            if(aux->comments->next){
                CommentPosition aux2 = aux->comments->next;
                while(aux2 != NULL){
                    fprintf(musicGenresTableFile, "%ld", aux2->ID);
                    if(aux2->next != NULL){
                        fprintf(musicGenresTableFile, ", ");
                    }
                    aux2 = aux2->next;
                }
            }
            fprintf(musicGenresTableFile, "]\n\t}");
            if(aux->next != NULL){
                fprintf(musicGenresTableFile, ",\n");
            }
            aux = aux->next;
        }
    }
    fprintf(musicGenresTableFile, "\n]");
}