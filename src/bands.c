/**
 * @file bands.c
 * @author Constanza Araya, Rodolfo Cifuentes, Bruno Martinez, Milton Hernández, Guliana Ruiz
 * @brief Funciones para manejo de bandas (artistas) musicales dentro de loopweb
*/

#include "bands.h"

 // Funciones de la lista de bandas

 /**
  * @brief Crea una lista vacia de bandas
  * @param bandList Puntero a una lista de bandas a vaciar, si es necesario
  * @return Puntero al nodo centinela de la lista
*/
BandList create_empty_bandList(BandList bandList)
{
    if (!is_empty_bandList(bandList)) {
        delete_bandList(bandList);
    }
    BandList newList = (BandList)malloc(sizeof(struct _band));
    if (newList == NULL) {
        print_error(200, NULL, NULL);
    }
    newList->next = NULL;
    return newList;
}

/**
 * @brief Verifica si una lista de bandas esta vacia
 * @param bandList Puntero a la lista de bandas
 * @return TRUE si la lista esta vacia, FALSE en caso contrario
*/
bool is_empty_bandList(BandList bandList)
{
    return bandList == NULL;
}

/**
 * @brief Borra una lista de bandas
 * @param bandList Puntero a la lista de bandas
*/
void delete_bandList(BandList bandList)
{
    if (is_empty_bandList(bandList)) {
        return;
    }
    BandPosition aux = bandList->next;
    while (aux != NULL) {
        delete_bandList_band(aux, bandList);
        aux = bandList->next;
    }
    free(bandList);
}

/**
 * @brief Imprime una lista de bandas en la consola
 * @param bandList Puntero a la lista de bandas
*/
void print_bandList(BandList bandList)
{
    BandPosition current = bandList->next;
    if (current == NULL) {
        printf("Empty\n");
    } else {
        while (current != NULL) {
            printf("[%s, ", current->band);
            print_commentLinkList(current->comments);
            printf("]\n\t-> ");
            current = current->next;
        }
        printf("NULL\n");
    }
}

/**
 * @brief Busca una banda en la lista de bandas
 * @param bandList Puntero a la lista de bandas
 * @param band Banda a buscar
 * @return Puntero al nodo encontrado, NULL si no se encuentra
*/
BandPosition find_bandList_band(BandList bandList, char* band)
{
    if (is_empty_bandList(bandList)) {
        return NULL;
    }
    BandPosition position = bandList_first(bandList);
    while (position != NULL && strcmp(position->band, band) != 0) {
        position = position->next;
    }
    return position;
}

/**
 * @brief Encuentra el nodo anterior a un nodo dado en la lista de bandas
 * @param position Nodo del cual se busca el anterior
 * @param bandList Puntero a la lista de bandas
 * @return Puntero al nodo anterior a @p position
*/
BandPosition find_bandList_prev_band(BandPosition position, BandList bandList)
{
    BandPosition aux = bandList;
    while (aux != NULL && aux->next != position) {
        aux = aux->next;
    }
    return aux;
}

/**
 * @brief Inserta un nodo en la lista de bandas
 * @param prevPosition Puntero al nodo anterior al que se desea insertar
 * @param band Banda a insertar
 * @param comments Lista de comentarios relacionados con la banda
 * @return Puntero al nodo insertado
*/
BandPosition insert_bandList_band(BandPosition prevPosition, char* band)
{
    BandPosition newNode = (BandPosition)malloc(sizeof(struct _band));
    if (newNode == NULL) {
        print_error(200, NULL, NULL);
    }

    newNode->band = (char*)malloc(sizeof(char) * strlen(band) + 1);
    if (newNode->band == NULL) {
        print_error(200, NULL, NULL);
    }
    snprintf(newNode->band, strlen(band) + 1, "%s", band);

    newNode->comments = create_empty_commentLinkList(NULL);
    newNode->next = prevPosition->next;
    prevPosition->next = newNode;
    return newNode;
}

/**
 * @brief Borra un nodo de la lista de bandas
 * @param position Puntero al nodo a borrar
 * @param bandList Puntero a la lista de bandas a la que pertenece @p position
*/
void delete_bandList_band(BandPosition position, BandList bandList)
{
    if (position == NULL) {
        print_error(203, NULL, NULL);
    }
    BandPosition prevNode = find_bandList_prev_band(position, bandList);
    if (prevNode == NULL) {
        print_error(301, NULL, NULL);
        return;
    }
    prevNode->next = position->next;
    delete_commentLinkList(position->comments);
    free(position->band);
    free(position);
}

// Funciones de interaccion con el usuario

/**
 * @brief Obtiene el primer nodo de una lista de bandas
 * @param bandList Puntero a la lista de bandas
 * @return Puntero a la primera banda de la lista
*/
BandPosition bandList_first(BandList bandList)
{
    return bandList->next;
}

/**
 * @brief Obtiene el ultimo nodo de una lista de bandas
 * @param bandList Puntero a la lista de bandas
 * @return Puntero a la ultima banda de la lista
*/
BandPosition bandList_last(BandList bandList)
{
    BandPosition position = bandList->next;
    while (position->next != NULL) {
        position = position->next;
    }
    return position;
}

/**
 * @brief Avanza al siguiente nodo en la lista de bandas
 * @param position Puntero a la banda actual
 * @return Puntero a la siguiente banda de la lista
*/
BandPosition bandList_advance(BandPosition position)
{
    return position->next;
}

/**
 * @brief Obtiene la banda almacenado en un nodo
 * @param position Puntero al nodo
 * @return Banda almacenada en el nodo
*/
char* get_band(BandPosition position)
{
    return position->band;
}

// Funciones de la tabla de bandas

/**
 * @brief Crea una tabla de bandas
 * @param bandTable Puntero a una tabla de bandas a vaciar, si es necesario
 * @return Puntero a la tabla creada
*/
BandTable create_bandTable(BandTable bandTable)
{
    if (bandTable != NULL) {
        delete_bandTable(bandTable);
    }

    bandTable = (BandTable)malloc(sizeof(struct _bandHashTable));
    if (!bandTable) {
        print_error(200, NULL, NULL);
    }

    for (int i = 0; i < BANDS_TABLE_SIZE; i++) {
        bandTable->buckets[i] = create_empty_bandList(NULL);
        bandTable->bandCount = 0;
    }

    bandTable->modified = false;

    return bandTable;
}

/**
 * @brief Imprime una tabla de bandas en la consola
 * @param bandTable Tabla de bandas a imprimir
*/
void print_bandTable(BandTable bandTable)
{
    printf("Bandas de la red (%d):\n", bandTable->bandCount);
    for(int i=0; i<BANDS_TABLE_SIZE; i++){
        printf("Bucket %2d: ", i);
        print_bandList(bandTable->buckets[i]);
    }
}

/**
 * @brief Inserta una banda en una tabla de bandas
 * @param band Banda a insertar
 * @param bandTable Tabla de bandas donde insertar la banda
 * @return Puntero al nodo insertado
*/
BandPosition insert_bandTable_band(char* band, BandTable bandTable)
{
    #ifdef DEBUG
        printf("Insertando banda %s en la tabla de bandas...\n", band);
    #endif
    unsigned int index = jenkins_hash(band) % BANDS_TABLE_SIZE;
    BandPosition position = insert_bandList_band(bandTable->buckets[index], band);
    if (position != NULL) {
        bandTable->bandCount++;
    }
    bandTable->modified = true;
    return position;
}

/**
 * @brief Borra una banda de una tabla de bandas
 * @param band Banda a borrar
 * @param bandTable Tabla de bandas donde buscar la banda
*/
void delete_bandTable_band(char* band, BandTable bandTable)
{
    int index = jenkins_hash(band) % BANDS_TABLE_SIZE;
    BandPosition position = find_bandList_band(bandTable->buckets[index], band);
    if (position == NULL) {
        print_error(301, NULL, NULL);
        return;
    }
    delete_bandList_band(position, bandTable->buckets[index]);
    bandTable->modified = true;
    bandTable->bandCount--;
}

/**
 * @brief Borra una tabla de bandas
 * @param bandTable Tabla de bandas a borrar
*/
void delete_bandTable(BandTable bandTable)
{
    for (int i = 0; i < BANDS_TABLE_SIZE; i++) {
        delete_bandList(bandTable->buckets[i]);
    }
    free(bandTable);
}

/**
 * @brief Verifica si una banda esta en la tabla de bandas
 * @param band Banda a verificar
 * @param bandTable Tabla de bandas donde buscar
 * @return TRUE si la banda esta en la tabla, FALSE en caso contrario
*/
BandPosition find_bandTable_band(char* band, BandTable bandTable)
{
    int index = jenkins_hash(band) % BANDS_TABLE_SIZE;
    return find_bandList_band(bandTable->buckets[index], band);
}


/**
 * @brief Funcion para guardar una tabla de bandas en su archivo JSON correspondiente
 *
 * @param bandTable Tabla de bandas a guardar
*/
void save_bandTable(BandTable bandTable)
{
    FILE* bandTableFile = fopen("./build/bands.json", "w");
    if (bandTableFile == NULL)
    {
        print_error(100, "./build/bands.json", NULL);
        return;
    }

    bool first = true;
    fprintf(bandTableFile, "[\n");
    for(int i=0; i<BANDS_TABLE_SIZE; i++)
    {
        if(!bandTable->buckets[i]->next){
            continue;
        }
        if(!first){
            fprintf(bandTableFile, ",\n");
        }
        else{
            first = false;
        }
        BandPosition aux = bandTable->buckets[i]->next;
        while(aux != NULL){
            fprintf(bandTableFile, "\t{\n\t\t\"band\":\"%s\",\n\t\t\"comments\":[", aux->band);
            if(aux->comments->next){
                CommentLinkPosition aux2 = aux->comments->next;
                while(aux2 != NULL){
                    fprintf(bandTableFile, "%ld", aux2->commentID);
                    if(aux2->next != NULL){
                        fprintf(bandTableFile, ", ");
                    }
                    aux2 = aux2->next;
                }
            }
            fprintf(bandTableFile, "]\n\t}");
            if(aux->next != NULL){
                fprintf(bandTableFile, ",\n");
            }
            aux = aux->next;
        }
    }
    fprintf(bandTableFile, "\n]");
    fclose(bandTableFile);
}

// Funciones de LoopWeb relacionadas a bandas

/**
 * @brief Imprime de manera estetica la tabla de bandas y devuelve la lista de enlaces a a todas las bandas
 *
 * @param table Puntero a la tabla de bandas
 * @return Puntero a la lista de enlaces a todas las bandas de la red ordenadas alfabeticamente
*/
BandLinkList get_loopweb_bands(BandTable table)
{
    BandLinkList allBands = create_empty_bandLinkList(NULL);

    for(int i=0; i<BANDS_TABLE_SIZE; i++){
        BandPosition aux = table->buckets[i]->next;
        while(aux != NULL){
            insert_bandLinkList_node_completeInfo(allBands, aux);
            aux = aux->next;
        }
    }
    sort_bandLinkList_byName(&allBands->next);
    BandLinkPosition current = allBands->next;
    int counter = 1;
    while (current != NULL) {
        printf("%3d. "ANSI_COLOR_GREEN"%-17s"ANSI_COLOR_RESET, counter, current->band);
        if(counter % 5 == 0){
            printf("\n");
        }
        counter++;
        current = current->next;
    }
    printf("\n\n");
    return allBands;
}