/**
 * @file hash.c
 * @author Constanza Araya, Rodolfo Cifuentes, Bruno Martinez, Milton Hernández, Guliana Ruiz
 * @brief Funciones de hashing
*/
#include "hash.h"

/**
 * @brief Función que calcula el hash de un string usando el algoritmo de Jenkins
 * @param key Palabra a calcular el hash
 * @return Devuelve el hash
 */
unsigned int jenkins_hash(char* key)
{
   unsigned int hash = 0;

   while (*key){
      hash += (unsigned char)(*key);
      hash += (hash << 10);
      hash ^= (hash >> 6);

      key++;
   }

   hash += (hash << 3);
   hash ^= (hash >> 11);
   hash += (hash << 15);

   return hash;
}

/**
 *  @brief Función para leer el contenido de un archivo y calcular el hash
 *  @param filename Nombre del archivo a hashear
 *  @return hash del archivo
*/
unsigned int hashFile(char *filename) {
    FILE *file = fopen(filename, "rb"); // Abrir el archivo en modo binario
    char aux[30];
    if (!file) {
        print_error(100, filename, NULL);
        exit(EXIT_FAILURE);
    }

    // Determinar el tamaño del archivo
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Leer el contenido del archivo
    char *buffer = (char*)malloc(fileSize * sizeof(char));
    if (!buffer) {
        sprintf(aux, "%lu", (fileSize * sizeof(char)));
        print_error(200, aux, NULL);
        fclose(file);
        exit(EXIT_FAILURE);
    }

    if(fread(buffer, sizeof(char), fileSize, file) < (long unsigned int)fileSize)
    {
        print_error(100, filename, NULL);
        return 0;
    }
    fclose(file);

    // Calcular el hash del contenido
    unsigned int hash = jenkins_hash(buffer);

    // Liberar la memoria del buffer
    free(buffer);

    return hash;
}
