#include <stdlib.h>
#include "comment.h"
#include "musicGenres.h"
#include "user.h"
#include "userLink.h"
// #include "json.h"

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

    /*
    // PRUEBA DE LECTURA DE DATOS JSON
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
     // FIN PRUEBA DE LECTURA DE DATOS JSON
    */

   /*
   // PRUEBA DE TABLA DE USUARIOS
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

    // FIN PRUEBA DE TABLA DE USUARIOS
    */

    // PRUEBA DE USUARIOS CON ENLACES
    UserTable users = create_userTable(NULL);

    // Crearemos a 5 amigos, Alice, Bob, Carol, Dave y Eve con los siguientes enlaces:
        // Alice es amiga de Bob, Carol y Dave
        // Bob es amigo de Alice
        // Carol es amiga de Alice, Dave y Eve
        // Dave es amigo de Alice y Carol
        // Eve es amiga de Carol
    UserLinkList aliceFriends = create_empty_userLinkList(NULL);
        insert_userLinkList_node_basicInfo(aliceFriends, "Bob");
        insert_userLinkList_node_basicInfo(aliceFriends, "Carol");
        insert_userLinkList_node_basicInfo(aliceFriends, "Dave");
    UserLinkList bobFriends = create_empty_userLinkList(NULL);
        insert_userLinkList_node_basicInfo(bobFriends, "Alice");
    UserLinkList carolFriends = create_empty_userLinkList(NULL);
        insert_userLinkList_node_basicInfo(carolFriends, "Alice");
        insert_userLinkList_node_basicInfo(carolFriends, "Dave");
        insert_userLinkList_node_basicInfo(carolFriends, "Eve");
    UserLinkList daveFriends = create_empty_userLinkList(NULL);
        insert_userLinkList_node_basicInfo(daveFriends, "Alice");
    UserLinkList eveFriends = create_empty_userLinkList(NULL);
        insert_userLinkList_node_basicInfo(eveFriends, "Carol");

    // Creamos 5 usuarios
    insert_userTable_node(users, "Alice", 18, "España", "Rock", aliceFriends);
    insert_userTable_node(users, "Bob", 19, "Italia", "Rock", bobFriends);
    insert_userTable_node(users, "Carol", 20, "Francia", "Rock", carolFriends);
    insert_userTable_node(users, "Dave", 21, "Italia", "Rock", daveFriends);
    insert_userTable_node(users, "Eve", 22, "España", "Rock", eveFriends);

    print_userTable(users);
    delete_userTable(users);

   // FIN PRUEBA DE USUARIOS CON ENLACES
    return 0;
}