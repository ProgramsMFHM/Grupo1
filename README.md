# LoopWe♭
## Integrantes
- Constanza Nayely Araya Farfán
- Rodolfo Sebastian Cifuentes Kamann
- Bruno Benjamin Martinez flores
- Milton Fabricio Hernández Morales
- Guliana Patricia Ruiz Millacari

## Descripción
Este proyecto es una aplicación de terminal que pretende emular una red social de usuarios (se plantea que sea basada principalmente en música) por medio de grafos y otras estructuras de datos.

Dicha red social pretende contar con los siguientes elementos:
- Creación de un perfil de usuario
- Establecer conexiones entre usuarios (amistades).
- Publicar y visualizar publicaciones propias y de amigos.
- Explorar y recomendar usuarios basándose en afinidades o popularidad.
- Realizar búsquedas eficientes de usuarios.

## Ideas iniciales
A continuación se listan ideas motoras para el inicio del desarrollo del proyecto.
1. El perfil de una persona es un grafo, donde cada uno de sus nodos contiene:
    - ID de usuario
	- Nombre de usuario
	- Edad
	- Nacionalidad (o ubicación)
	- Gustos
		- Géneros musicales
		- Bandas/Cantantes
		- Cada gusto puede tener un peso basado en la cantidad de publicaciones al respecto que un usuario ha hecho. **Problema**: ¿Qué pasa si no le gusta lo que está comentando no es de su gusto?
	- Publicaciones
		- Se almacenarán en texto plano
		- Tendrán #Etiquetas que son las categorías que van en los gustos
		- Una descripción personal que pueda ver cualquier usuario
		- Una publicación tendría un límite de $500$ caracteres, y se escribe en un sólo párrafo (para simplificar el almacenamiento).
- Un usuario **podría** dar me gusta a publicaciones lo que aumentaría su relación con los gustos involucrados.
- Toda la información de los usuarios estará almacenada en archivos de texto plano fuera de la RAM del equipo que serían cargados cuando fueran necesarios.
- Podría existir una opción para bloquear o rechazar recomendaciones de usuarios.
- Un usuario puede pedir recomendaciones a la aplicación las cuales son:
	- Basados en los amigos de amigos ( Se planea que se tengan en cuenta los amigos de tercer grado (amigos de amigos de amigos) y se viene a la mente la teoría de los 6 grados: https://upcommons.upc.edu/bitstream/handle/2099/9844/Article008.pdf)
	- Basados en la edad del usuario
	- Basados en la similitud de sus gustos
	- Estas recomendaciones se unirían para formar una lista en orden de mejores recomendaciones.

A continuación se muestra un ejemplo de lo que podría ser la visualización de un perfil en `LoopWeb`.
```bash
> @Unnamed
Unnamed (No son amigos)
Me gusta el pop y salir a caminar por la ciudad
	- #Pop
	- #Country
	- @Madona
	- @Ariana Grande
¿Qué desea hacer con el perfil de @Unnamed?
- Ver las publicaciones de @Unnamed
- Proponer una amistad con @Unnamed
```

Por otro lado aquí se muestra un posible ejemplo de una lista de recomendaciones.

```bash
Recomendaciones @Unnamed
1. @Unnamed2 - Breve por qué
2. @Unnamed3 - Breve por qué
20. @Unnamed4 - Breve por qué

¿Qué hacer?
```
## Gestión inicial de tareas
Por la naturaleza de este proyecto la asignación de tareas es bastante relevante aunque puede mutar durante el desarrollo del mismo dado que es el primer proyecto de este equipo de trabajo.

Como idea preliminar se proponen los siguientes roles (principales):
- **Constanza Araya**: Documentación e investigación de información
- **Rodolfo Cifuentes**: Desarrollador encargado de la construcción de funciones y estructuras de datos
- **Bruno Martinez**: Desarrollador encargado de la construcción de funciones y estructuras de datos
- **Milton Hernández**: Ensamblador y coordinador del equipo
- **Guliana Ruiz**: Encargada de la depuración, corrección de errores y testeo del proyecto