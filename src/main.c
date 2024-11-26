#include <stdlib.h>
#include "comment.h"

int main()
{
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

    return 0;
}