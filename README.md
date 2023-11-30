# The Guardians Battle 
### Martin Bascuñan Gonzalez
## Descripción.
Corresponde a un juego donde los guardianes son héroes con habilidades y destrezas únicas que protegen a las ciudades a lo largo de toda la tierra siendo estas los últimos asentamientos de la humanidad.
## Estructura Utilizada.
Se hablara de las estructuras declaradas en el código del programa. (aunque muchas de dichas funciones tambien presentan una breve descripcion en los comentarios del code).
- Struct Guardian: Estructura para almacenar la información de los Guardianes.
- Struct Node: Estructura para almacenar la información de los Nodos.
- Struct GuardianNodoArbol: Estructura para almacenar la información del arbol de guardianes.
- Class GrafoUnidireccional: Estructura que permite hacer un grafo general para las clases Guardianes y Maestros que conectarán las ciudades entre si.
## Funciones Principales.
- InsertNode: Inserta un nuevo nodo en el arbol binario bajo el parametro del nivel de poder.
- DescendentPower: Recorre de manera inversa el arbol, es decir, de derecha a izquierda. Aqui se hace la distincion entre los Guardianes del Reino y los Candidatos a Reino.
- PoderPostBatalla: Actualiza el nivel de poder del guardian según el resultado de la batalla, también establece los párámetros para verificar si sumar los puntos llevará al poder por encima de 100.
- MaestroGuardian: Verifica si un guardian tiene al menos un aprendiz en el arbol, con parámetros que indican si el arbol se encuentra vacio, el guardian no es ni aprendiz ni maestro o si el guardián tiene el mismo nombre que el guardián actual dentro de ese nodo. También se verifica si el nodo actual tiene al menos un hijo.
- Se declara una una función que le indica al usuario si este presenta los archivos "Guardianes.txt" y "Ciudades.txt" en su computadora. Los cuales son fileCiudad y fileGuardian respectivamente.
- Main: Se encuentra el menú del programa que será el punto de interaccion entre el código y el usuario. Se establece las opciones del menú donde el usuario podrá interactuar, y tambien, se validan los datos entregados por el mismo.

