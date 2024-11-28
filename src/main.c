#include <stdlib.h>
#include "comment.h"
#include "musicGenres.h"
#include "json.h"

int main()
{
    /*
    // PRUEBA DE COMENTARIOS
    CommentList comentarios = NULL;
    comentarios = read_comments_from_file(comentarios, "./build/com.txt");
    if(comentarios == NULL){
        printf("Error al crear la lista de comentarios\n");
        exit(1);
    }
    printf("\nComentarios leidos\n");

    print_comments(comentarios);

    delete_comment_list(comentarios);
    // FIN PRUEBA DE COMENTARIOS
    */

   /*
   // PRUEBA DE GÉNEROS MUSICALES
   MusicGenresTable genresTable = read_musicGenre_file("./build/music_genres.txt", NULL);
   print_musicGenresTable(genresTable);
    if(find_musicGenresTable_genre("alternativeRock", genresTable)){
        printf("EL "ANSI_COLOR_MAGENTA"#alternativeRock"ANSI_COLOR_RESET" Esta en la tabla\n");
    }
   delete_musicGenresTable(genresTable);
   // FIN PRUEBA DE GÉNEROS MUSICALES
   */

    // PRUEBA DE LECTURA DE DATOS JSON
    User usuarios[MAX_USERS];
    int total_users = 0;

    if (read_archive_json("./build/users.json", usuarios, &total_users) == 0) {
        printf("Se leyeron %d usuarios:\n", total_users);

        /**<  imprimir los datos obtenidos de cada usuario*/
        for (int i = 0; i < total_users; i++) {
            printf("ID %d:\n", i + 1);
            printf("Nombre: %s\n", usuarios[i].name);
            printf("Edad: %d\n", usuarios[i].age);
            printf("Nacionalidad: %s\n", usuarios[i].nationality);
            printf("Gustos:\n");
            for (int j = 0; j < MAX_ELEMENTS && usuarios[i].gustos[j][0]; j++) {
                printf("  - %s\n", usuarios[i].gustos[j]);
            }
            printf("Bandas:\n");
            for (int j = 0; j < MAX_ELEMENTS && usuarios[i].bands[j][0]; j++) {
                printf("  - %s\n", usuarios[i].bands[j]);
            }
            printf("Amigos:\n");
            for (int j = 0; j < MAX_ELEMENTS && usuarios[i].friends[j][0]; j++) {
                printf(" ID - %s\n", usuarios[i].friends[j]);
            }
            printf("\n");
        }
    }
  // FIN PRUEBA DE LECTURA DE DATOS JSON

    return 0;
}