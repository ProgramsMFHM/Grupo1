#include <stdlib.h>
#include "getopt.h"
#include "comments.h"
#include "commentLink.h"
#include "user.h"
#include "userLink.h"
#include "musicGenres.h"
#include "genreLink.h"
#include "bands.h"
#include "bandLink.h"
#include "json.h"
#include "utilities.h"

int main(int argc, char* argv[])
{
    int opt;
    // int opt_index = 0

    // Definir las opciones largas
    struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"administrador", no_argument, 0, 'a'},
        {"user", required_argument, 0, 'u'},
        {0, 0, 0, 0} // Terminador
    };

    // Analizar opciones
    if ((opt = getopt_long(argc, argv, "hau:", long_options, NULL)) != -1) {
        switch (opt) {
            case 'a': // Modo Admin
                printf("Usted a ingresado como administrador de LoopWeb\n");
                break;
            case 'u': // Modo usuario
                printf("Usted a ingresado como usuaro con el nombre %s\n", optarg);
                break;
            case '?': // Error
                return 0;
                break;
            case 'h': // Modo ayuda
            default:
                printf("Ayuda del programa\n");
                break;
        }
    }
    else{
        printf("Ayuda del programa\n");
    }

    // PRUEBA DE TABLA DE BANDAS Y GENRES
    BandTable bandsTable = get_bands_from_file("./build/bands.json", NULL);
    print_bandTable(bandsTable);
    delete_bandTable(bandsTable);

    printf("--------------------------------------------------------------------------------\n");

    MusicGenresTable genresTable = get_genres_from_file("./build/music_genres.json", NULL);
    print_musicGenresTable(genresTable);
    delete_musicGenresTable(genresTable);

    // FIN PRUEBA DE TABLA DE BANDAS Y GENRES

    return 0;
}


/* PRUEBA DE COMENTARIOS
    CommentList comentarios = NULL;
    comentarios = read_comments_from_file(comentarios, "./build/com.txt");
    if(comentarios == NULL){
        printf("Error al crear la lista de comentarios\n");
        exit(1);
    }
    printf("\nComentarios leidos\n");

    print_comments(comentarios);

    delete_comment_list(comentarios);
FIN PRUEBA DE COMENTARIOS */

 /* PRUEBA DE GÉNEROS MUSICALES
   MusicGenresTable genresTable = read_musicGenre_file("./build/music_genres.txt", NULL);
   print_musicGenresTable(genresTable);
   delete_musicGenresTable(genresTable);
FIN PRUEBA DE GÉNEROS MUSICALES */

/* PRUEBA DE LECTURA DE DATOS JSON
    User usuarios[MAX_USERS];
    int total_users = 0;

    if (read_archive_json("./build/users.json", usuarios, &total_users) == 0) {
        printf("Se leyeron %d usuarios:\n", total_users);

        // imprimir los datos obtenidos de cada usuario
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
FIN PRUEBA DE LECTURA DE DATOS JSON */

/* PRUEBA DE TABLA DE USUARIOS
   // Crear la tabla hash
    UserTable table = create_userTable(NULL);

    // Imprimir la tabla inicial
    print_userTable(table);

    // Agregar usuarios
    insert_userTable_node(table, "Alice", 30, "USA", "Rock");
    insert_userTable_node(table, "Bob", 25, "Canada", "Jazz");
    insert_userTable_node(table, "Charlie", 35, "UK", "Pop");
    insert_userTable_node(table, "David", 35, "UK", "Pop");
    insert_userTable_node(table, "Emily", 35, "UK", "Pop");
    insert_userTable_node(table, "Frank", 35, "UK", "Pop");
    insert_userTable_node(table, "George", 35, "UK", "Pop");
    insert_userTable_node(table, "Hannah", 35, "UK", "Pop");
    insert_userTable_node(table, "Isabella", 35, "UK", "Pop");
    insert_userTable_node(table, "Jack", 35, "UK", "Pop");
    insert_userTable_node(table, "Jasmine", 35, "UK", "Pop");
    insert_userTable_node(table, "Kate", 35, "UK", "Pop");
    insert_userTable_node(table, "Lily", 35, "UK", "Pop");
    insert_userTable_node(table, "Max", 35, "UK", "Pop");
    insert_userTable_node(table, "Natalie", 35, "UK", "Pop");
    insert_userTable_node(table, "Oliver", 35, "UK", "Pop");
    insert_userTable_node(table, "Penelope", 35, "UK", "Pop");
    insert_userTable_node(table, "Quentin", 35, "UK", "Pop");
    insert_userTable_node(table, "Sophia", 35, "UK", "Pop");

    // Imprimir la tabla después de agregar usuarios
    print_userTable(table);

    // Crear un nuevo usuario
    UserNode usuario;
    printf("Ingrese el nombre de usuario: ");
    if(scanf("%s", usuario.username) < 1){
        printf("Error al leer el nombre de usuario\n");
        exit(1);
    }
    printf("Ingrese la edad: ");
    if(scanf("%d", &usuario.age) < 1){
        printf("Error al leer la edad\n");
        exit(1);
    }
    printf("Ingrese la nacionalidad: ");
    if(scanf("%s", usuario.nationality) < 1){
        printf("Error al leer la nacionalidad\n");
        exit(1);
    }
    printf("Ingrese el gusto musical: ");
    if(scanf("%s", usuario.musicTaste) < 1){
        printf("Error al leer el gusto musical\n");
        exit(1);
    }
    insert_userTable_node(table, usuario.username, usuario.age, usuario.nationality, usuario.musicTaste);

    // Imprimir la tabla después de agregar el nuevo usuario
    print_userTable(table);

    // Eliminar a Bob
    printf("Eliminando a Bob\n");
    delete_userTable_node(table, "Bob");
    print_userTable(table);

FIN PRUEBA DE TABLA DE USUARIOS */

/* PRUEBA DE TABLA DE USUARIOS
    UserTable table = get_users_from_file(USERS_PATH"users.json", NULL);
    // print_userTable(table);

    printf("--- Completando usuarios ---\n");
    for(int i = 0; i < USER_TABLE_SIZE; i++){
        UserPosition user = table->buckets[i]->next;
        while(user != NULL){
            complete_user_from_json(user);
            user = user->next;
        }
    }
    print_userTable(table);

    printf("Gustos musicales de Allice:\n");
    bubbleSort_genreLinkList(find_userTable_node(table, "Alice")->genres);
    print_genreLinkList(find_userTable_node(table, "Alice")->genres);
    printf("\n");

    printf("Gustos musicales de Bob:\n");
    bubbleSort_genreLinkList(find_userTable_node(table, "Bob")->genres);
    print_genreLinkList(find_userTable_node(table, "Bob")->genres);
    printf("\n");

    delete_userTable(table);
FIN PRUEBA DE TABLA DE USUARIOS */


/* PRUEBA DE TABLA DE BANDAS
    BandTable bandsTable = read_band_file("./build/bands.txt", NULL);
    print_bandTable(bandsTable);
    delete_bandTable(bandsTable);

    MusicGenresTable genresTable = read_musicGenre_file("./build/music_genres.txt", NULL);
    print_musicGenresTable(genresTable);
    delete_musicGenresTable(genresTable);

FIN PRUEBA DE TABLA DE BANDAS */

/* PRUEBA FUNCION DE IMPRESION
    printf_loopweb("Hello World\n");
    printf_loopweb("Este es un texto de descripcion de un comentario sobre #rock y @rock\nSomos entusiastas de #rock\n");
    printf_loopweb("@rock#rock@pop#pop@rock#rock\n");
FIN PRUEBA FUNCION DE IMPRESION */

/* PRUEBA DE TABLA DE USUARIOS
    UserTable table = get_users_from_file(USERS_PATH"users.json", NULL);
    // print_userTable(table);

    printf("--- Completando usuarios ---\n");
    for(int i = 0; i < USER_TABLE_SIZE; i++){
        UserPosition user = table->buckets[i]->next;
        while(user != NULL){
            complete_user_from_json(user);
            user = user->next;
        }
    }
    print_userTable(table);

    for(int i = 0; i < USER_TABLE_SIZE; i++){
        UserPosition user = table->buckets[i]->next;
        while(user != NULL){
            printf(ANSI_COLOR_GREEN "%s: " ANSI_COLOR_RESET, user->username);
            print_loopweb(user->description);
            printf("\n");
            user = user->next;
        }
    }

    delete_userTable(table);
FIN PRUEBA DE TABLA DE USUARIOS */


/* PRUEBA LISTA DE COMENTARIOS
    // Cargamos usuarios
    UserTable userTable = get_users_from_file(USERS_PATH "users.json", NULL);

    // Crear árbol vacío
    CommentList comments = create_empty_CommentList(NULL);

    // Crear comentarios e insertarlos
    char *comentarios[] = {
        "Este es el primer comentario #rock #pop #indie",
        "Este es el segundo comentario @rock @pop @indie",
        "Otro comentario interesante #rock #pop #indie",
        "Comentario sobre música",
        "Comentario sobre películas",
        "Comentario aleatorio"
    };

    for (int i = 0; i < 6; i++) {
        // Insertar comentario
        insert_CommentList_node(comments, create_new_comment(i, comentarios[i], "Alice"));
        complete_commentList_node(comments->next, userTable);
    }

    // Mostrar el árbol (opcional, para verificar)
    printf("Comentarios en la lista:\n\n");
    print_CommentList(comments);

    // Liberar recursos
    printf("\nEliminando lista de comentarios...\n");
    delete_CommentList(comments);

    printf("Eliminando tabla de usuarios...\n");
    delete_userTable(userTable);

FIN PRUEBA ARBOL DE COMENTARIOS */