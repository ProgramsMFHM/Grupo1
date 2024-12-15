# LoopWe♭
## Integrantes
- [Constanza Nayely Araya Farfán](https://github.com/Cnstnnza)
- [Rodolfo Sebastian Cifuentes Kamann](https://github.com/Fitooooooooo)
- [Bruno Benjamin Martinez flores](https://github.com/pin0no)
- [Milton Fabricio Hernández Morales](https://github.com/ProgramsMFHM)
- Guliana Patricia Ruiz Millacari

## Descripción
Este proyecto es una aplicación de terminal que pretende emular una red social de usuarios (se plantea que sea basada principalmente en música) por medio de grafos y otras estructuras de datos.

Dicha red social pretende contar con los siguientes elementos:
- Creación de un perfil de usuario
- Establecer conexiones entre usuarios (amistades).
- Publicar y visualizar publicaciones propias y de amigos.
- Explorar y recomendar usuarios basándose en afinidades o popularidad.
- Realizar búsquedas eficientes de usuarios.

## Ejecusión del programa
Para ejecutar el programa, se debe seguir los siguientes pasos:
1. Asegurarse de tener instalada la librería [Jansson](https://github.com/akheron/jansson) en el PATH del sistema (puede usar el script [jansson.sh](/docs/jansson.sh) para instalarla directamente en sistemas Linux con `apt`)
2. Clonar el repositorio con `git clone https://github.com/ProgramsMFHM/Grupo1`.
3. Ejecutar los comandos `make folders` y `make` para compilar el programa.
4. Ejecutar el programa con el comando `make run` y seguir sus instrucciones.

Luego de esto puede ejecutar:
- `make debug` para compilar el programa con las opciones de depuración.
- `make doc` para generar la documentación del programa con [Doxygen](https://www.doxygen.nl/).
- `make clean` para eliminar los archivos compilados.
- `make save` para guardar los archivos del programa en el directorio `testing/`.