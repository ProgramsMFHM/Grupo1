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

void user_mode(char *user_name);

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
                user_mode(optarg);
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

    return 0;
}

void user_mode(char *userName)
{
    printf("\t\tUsted a ingresado como usuaro con el nombre "ANSI_COLOR_CYAN"%s\n" ANSI_COLOR_RESET, userName);

    int terminate = 0;
    UserTable loopwebUsers = get_users_from_file(USERS_PATH"users.json", NULL);
    BandTable loopwebBands = get_bands_from_file("./build/bands.json", NULL);
    GenreTable loopwebGenres = get_genres_from_file("./build/genres.json", NULL);

    // Comprobamos que el usuario exista
    if(!find_userTable_node(loopwebUsers, userName)){
        print_error(300, userName, NULL);
        return;
    }

    while(!terminate)
    {
        // Usuario escoge camino a seguir
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
                break;
            case 3: // Ver me feed de publicaciones
                break;
            case 4: // Realizar una publicacion
                make_comment(userName, loopwebUsers, loopwebBands, loopwebGenres);
                break;
            case 5: // Ver mis recomendaciones de amigos
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

    delete_userTable(loopwebUsers);
}