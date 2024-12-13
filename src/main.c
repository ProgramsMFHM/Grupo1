#include <stdlib.h>
#include "getopt.h"
#include "comments.h"
#include "commentLink.h"
#include "user.h"
#include "userLink.h"
#include "genres.h"
#include "genreLink.h"
#include "bands.h"
#include "bandLink.h"
#include "json.h"
#include "utilities.h"

void admin_mode();
void user_mode(char *user_name);

int main(int argc, char* argv[])
{
    #ifdef DEBUG
        printf(ANSI_COLOR_RED"\t\tDebug mode enabled\n" ANSI_COLOR_RESET);
    #endif
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
                admin_mode();
                break;
            case 'u': // Modo usuario
                user_mode(optarg);
                break;
            case '?': // Error
                return 0;
                break;
            case 'h': // Modo ayuda
            default:
                printf("Ayuda del programa :D\n");
                break;
        }
    }
    else{
        printf("Ayuda del programa :D\n");
    }

    return 0;
}

void admin_mode()
{
    int terminate = 0;
    UserTable looopWebUsers = get_users_from_file(USERS_PATH"users.json", NULL);
    UserLinkList allUsers;
    BandTable loopwebBands = get_bands_from_file("./build/bands.json", NULL);
    BandLinkList allBands;
    GenreTable loopwebGenres = get_genres_from_file("./build/genres.json", NULL);
    GenreLinkList allGenres;

    while(!terminate)
    {
        printf(CLEAR_SCREEN"\t\tUsted a ingresado como administrador\n");
        printf("Que desea hacer?\n");
        printf("\t1. Listar todos los usuarios y ver un perfil\n");
        printf("\t2. Listar todas las bandas y artistas de la base de datos\n");
        printf("\t3. Listar todos los generos y artistas de la base de datos\n");
        printf("\t4. Crear un nuevo usuario\n");
        printf("\t5. Salir\n");
        int option;
        do{
            printf("Opcion: ");
            if(scanf("%d", &option) != 1){
                print_error(103, NULL, NULL);
                continue;
            }
        }while(option < 1 || option > 5);

        switch(option){
            case 1: // Listar todos los usuarios
                allUsers = get_loopweb_users(looopWebUsers);
                printf("Desea ver el perfil de un usuario? Ingrese el numero que aparece junto al usuario deseado (0 para salir): ");
                if(scanf("%d", &option) != 1){
                    print_error(103, NULL, NULL);
                    continue;
                }
                if(option > 1 && option <= looopWebUsers->userCount){
                    UserLinkPosition aux = allUsers->next;
                    for(int i=1; i<option; i++){
                        aux = aux->next;
                    }
                    if(aux){
                        print_user(aux->userNode);
                    }
                }
                delete_userLinkList(allUsers);
                break;
            case 2: // Listar todas las bandas y artistas de la base de datos
                allBands = get_loopweb_bands(loopwebBands);
                delete_bandLinkList(allBands);
                break;
            case 3: // Listar todos los generos y artistas de la base de datos
                allGenres = get_loopweb_genres(loopwebGenres);
                delete_genreLinkList(allGenres);
                break;
            case 4: // Crear un nuevo usuario
                break;
            case 5: // Salir
                printf("Nos vemos pronto\n");
                break;
            default:
                break;
        }

        printf("\n¿Desea realizar otra accion? (0:si, 1:no): ");
        if(scanf("%d", &terminate) != 1){
            print_error(103, NULL, NULL);
            continue;
        }
    }

    delete_bandTable(loopwebBands);
    delete_genresTable(loopwebGenres);
    delete_userTable(looopWebUsers);
}


/**
 * @brief Funcion para manejar el comportamiento del programa en modo usuario
 *
 * @param userName Nombre del usuario que desea realizar acciones
*/
void user_mode(char *userName)
{
    int terminate = 0;
    UserTable loopwebUsers = get_users_from_file(USERS_PATH"users.json", NULL);
    UserPosition user = find_userTable_node(loopwebUsers, userName); // Comprobamos que el usuario exista
    if(!user){
        print_error(300, userName, NULL);
        delete_userTable(loopwebUsers);
        return;
    }
    BandTable loopwebBands = get_bands_from_file("./build/bands.json", NULL);
    GenreTable loopwebGenres = get_genres_from_file("./build/genres.json", NULL);
    CommentTable loopwebComments = get_comments_from_file(COMMENTS_PATH"comments.json", NULL);

    UserLinkList possibleFriends;

    while(!terminate)
    {
        // Usuario escoge camino a seguir
        printf(CLEAR_SCREEN"\t\tUsted a ingresado como usuaro con el nombre "ANSI_COLOR_CYAN"%s\n" ANSI_COLOR_RESET, userName);
        printf("Que desea hacer?\n");
        printf("\t1. Ver perfiles de mis amigos\n");
        printf("\t2. Ver mi propio perfil\n");
        printf("\t3. Ver me feed de publicaciones\n");
        printf("\t4. Realizar una publicacion\n");
        printf("\t5. Ver mis recomendaciones de amigos\n");
        printf("\t6. Salir\n");
        int option;
        do{
            printf("Opcion: ");
            if(scanf("%d", &option) != 1){
                print_error(103, NULL, NULL);
                continue;
            }
        }while(option < 1 || option > 6);

        switch(option){
            case 1: // Ver perfiles de mis amigos
                break;
            case 2: // Ver mi propio perfil
                printf(CLEAR_SCREEN);
                print_user(user);
                break;
            case 3: // Ver me feed de publicaciones
                print_user_feed(user, loopwebBands, loopwebGenres, loopwebComments);
                break;
            case 4: // Realizar una publicacion
                make_comment(userName, loopwebUsers, loopwebBands, loopwebGenres, loopwebComments);
                break;
            case 5: // Ver mis recomendaciones de amigos
                possibleFriends = find_possible_friends(user, loopwebUsers);
                print_userLinkList(possibleFriends);
                delete_userLinkList(possibleFriends);
                break;
            case 6: // Salir
                printf("Nos vemos pronto\n");
            default:
                break;
        }

        printf("\n¿Desea realizar otra accion? (0:si, 1:no): ");
        if(scanf("%d", &terminate) != 1){
            print_error(103, NULL, NULL);
            continue;
        }
    }

    delete_bandTable(loopwebBands);
    delete_genresTable(loopwebGenres);
    delete_commentTable(loopwebComments);
    delete_userTable(loopwebUsers);
}