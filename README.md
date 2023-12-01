# The Guardians Battle 
### Martin Bascuñan Gonzalez
## Descripción.
Corresponde a un juego donde los guardianes son héroes con habilidades y destrezas únicas que protegen a las ciudades a lo largo de toda la tierra siendo estas los últimos asentamientos de la humanidad.
## Estructura Utilizada.
Se hablara de las estructuras declaradas en el código del programa. (aunque muchas de dichas funciones tambien presentan una breve descripcion en los comentarios del code).
- Struct Guardian: Estructura para almacenar la información de los Guardianes.
- Struct Node: Estructura para almacenar la información de los Nodos.
- Struct GuardianNodoArbol: Estructura para almacenar la información del arbol de guardianes.
## Grafos Implementados.
using Grafo = unordered_map<string, unordered_set<string>>;
Los viajes entre ciudades no son tarea fácil, por lo que se implementó el uso de Grafos para generar lazos entre ciudades y que, a su vez, los Guardianes tuvieran un nexo entre las Ciudades donde pueden moverse.
-lecturaCiudad: Funcion encargada de cargar los datos del archivo "Ciudades.txt" que permitirá indicar mediante este archivo texto, las ciudades disponibles para cada Guardian.
-imprimirGrafo: Como dice su nombre. Funcion para la impresion de grafo general gracias a la funcion "vecinos" y "par." que permitirá establecer una conexion entre los nodos del grafo, para generar una estructura enlazada más grande.
-MatrizComparacion: Funcion que crea una matriz de comparación que nos permite ver de otra perspectiva el grafo anteriormente creado, generando enlaces entre los Nodos del grafo, viendo de manera más gráfica los nodos que se intersectan entre cada uno. En simnples palabras, es la impresión del grafo pero en forma de matríz.
-leerGuardianesDesdeArchivo: Funcion, al igual que lecturaCiudad, es la encargada de cargar los datos del archivo "Guardianes.txt" para ser mostrado posteriormente.
## Funciones Principales.
- InsertNode: Inserta un nuevo nodo en el arbol binario bajo el parametro del nivel de poder.
- DescendentPower: Recorre de manera inversa el arbol, es decir, de derecha a izquierda. Aqui se hace la distincion entre los Guardianes del Reino y los Candidatos a Reino.
- PoderPostBatalla: Actualiza el nivel de poder del guardian según el resultado de la batalla, también establece los párámetros para verificar si sumar los puntos llevará al poder por encima de 100.
- MaestroGuardian: Verifica si un guardian tiene al menos un aprendiz en el arbol, con parámetros que indican si el arbol se encuentra vacio, el guardian no es ni aprendiz ni maestro o si el guardián tiene el mismo nombre que el guardián actual dentro de ese nodo. También se verifica si el nodo actual tiene al menos un hijo.
- Se declara una una función que le indica al usuario si este presenta los archivos "Guardianes.txt" y "Ciudades.txt" en su computadora. Los cuales son fileCiudad y fileGuardian respectivamente.
- Main: Se encuentra el menú del programa que será el punto de interaccion entre el código y el usuario. Se establece las opciones del menú donde el usuario podrá interactuar, y tambien, se validan los datos entregados por el mismo. Dentro del menú, habrán diferentes opciones que el usuario podrá interactuar, donde cada una le llevará a otro apartado, si el usuario lee claramente las indicaciones por pantalla. Cada enunciado lo llevará a una acción concreta dentro del código.
## Link Video
(insertar link)

