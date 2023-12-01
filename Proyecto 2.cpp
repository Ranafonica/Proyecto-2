// Librerias a utilizar en el código.
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <random>
#include <unordered_map>
#include <unordered_set>
#include <limits>
#include <string>
#include <algorithm>

using namespace std;

//---------------------------------------------ESTRUCTURAS---------------------------------------------
// Estructura para almacenar la información de los Guardianes.
struct Guardian {
    string name;
    int powerLevel;
    string master;
    string city;
    vector<string> apprentices;
};

// Estructura para almacenar la información de los Nodos.
struct Node {
    Guardian guardian;
    Node* left;
    Node* right;
    Node(const Guardian& guard) : guardian(guard), left(nullptr), right(nullptr) {}
};

// Estructura para almacenar la información del arbol de guardianes.
struct GuardianNodoArbol {
    Guardian guardian;																	// Almacena la información del guardian.
    vector<GuardianNodoArbol*> apprentices;												// Almacena los aprendices del guardian.
    GuardianNodoArbol* master;															// Almacena el maestro del guardian.
    GuardianNodoArbol(const Guardian& guard) : guardian(guard), master(nullptr) {}
};

//---------------------------------------------GRAFOS---------------------------------------------
using Grafo = unordered_map<string, unordered_set<string>>;

//Funcion que carga los datos del archivo "Ciudades.txt".
void lecturaCiudad(const string &nombreArchivo, Grafo &grafo, unordered_set<string> &uniqueCity) {
    ifstream fileCiudad("Ciudades.txt");
    if (!fileCiudad.is_open()) {
    	cout << endl;
    	cout << "Archivo Ciudades.txt no encontrado." << endl;
        cout << "No se ha podido abrir correctamente." << endl;
        return;
    } else {
    	cout << "Archivo Ciudades.txt encontrado.";
        cout << "...Archivo abierto satisfactoriamente" << endl;
        cout << endl;
    }
    
    // Formato de lectura de ciudades.
    string line;
    while (getline(fileCiudad, line)) {
        istringstream ss(line);
        string cityA, cityB;
        getline(ss, cityA, ',');
        getline(ss, cityB);

        
        grafo[cityA].insert(cityB);
        grafo[cityB].insert(cityA);

        
        uniqueCity.insert(cityA);
        uniqueCity.insert(cityB);
    }
    fileCiudad.close();
}

// Funcion para la impresion de grafo general.
void imprimirGrafo(const Grafo &grafo) {
    cout << "[GRAFO PRINCIPAL]: \n";
    cout << endl;
    for (const auto &par : grafo) {
        cout << par.first << ": ";
        for (const auto &vecino : par.second) {
            cout << vecino << " -> ";
        }
        cout << "\n";
    }
}

// Funcion que crea la Matriz de comparación.
void MatrizComparacion(const unordered_set<string> &uniqueCity, const Grafo &grafo, const unordered_map<string, int> &numCiudad) {
	cout << "\n[MATRIZ CON NUMEROS]: \n";
	cout << endl;
	// Impresion de Numeros de forma Horizontal
    cout << "   ";
    for (const auto &ciudad : uniqueCity) {
        cout << numCiudad.at(ciudad) << " ";
    }
    cout << "\n";
    
    // Imprimir de Numeros de forma Vertical
    for (const auto &ciudad : uniqueCity) {
        cout << numCiudad.at(ciudad) << ": ";
        
        for (const auto &otraCiudad : uniqueCity) {
            cout << (grafo.at(ciudad).count(otraCiudad) > 0 ? "X " : "O ");
            
        }
        cout << "\n";
    }
}

// Función para cargar la lista de guardianes desde el archivo "Guardianes.txt"
vector<pair<int, Guardian>> leerGuardianesDesdeArchivo(const string& nombreArchivo) {
    ifstream fileGuardian(nombreArchivo);
    vector<pair<int, Guardian>> guardianes;

    if (!fileGuardian.is_open()) {
        cout << "Archivo Guardianes.txt no encontrado." << endl;
        cout << "No se ha podido abrir correctamente." << endl;
    } else {
        cout << "Archivo Guardianes.txt encontrado.";
        cout << "...Archivo abierto satisfactoriamente" << endl;

        string line;
        getline(fileGuardian, line); // Saltar la primera línea que contiene encabezados

        int numero = 1;
        while (getline(fileGuardian, line)) {
            istringstream ss(line);
            Guardian guardian;
            getline(ss, guardian.name, ',');
            ss >> guardian.powerLevel;
            ss.ignore(); // Ignorar la coma después del nivel de poder
            getline(ss, guardian.master, ',');
            getline(ss, guardian.city);

            guardianes.push_back({numero, guardian});
            numero++;
        }

        fileGuardian.close();
    }

    return guardianes;
}

// ---------------------------------------------FUNCIONES PRINCIPALES---------------------------------------------
// Insertar un nuevo nodo en el arbol binario bajo el parametro del nivel de poder.
void InsertNode(Node*& root, const Guardian& guardian){
	if (root == nullptr){																// Se crea un nuevo nodo con la informacion del guardian y se establece como raiz.
        root = new Node(guardian);
        return;
    }
    if (guardian.powerLevel < root->guardian.powerLevel){
        InsertNode(root->left, guardian);
    } else if (guardian.powerLevel > root->guardian.powerLevel){
        InsertNode(root->right, guardian);
    }
}

// Recorre de manera inversa el arbol, es decir, de derecha a izquierda.
// Aqui se hace la distincion entre los Guardianes del Reino y los Candidatos a Reino.
void DescendentPower(Node* root, int& count, int& countReino){
	if (root == nullptr || count == 0){
		return;
	}
	DescendentPower(root->right, count, countReino);									// Se imprime.
	
	if (root->guardian.powerLevel >= 90 && root->guardian.powerLevel <= 100) {			// Se establece la distincion entre puntos de poder para ser Guardian de Reino o Candidato.
        if (countReino < 3) {
            cout << "[Guardian del Reino]/Nombre: " << root->guardian.name << ", Puntos de Poder: " << root->guardian.powerLevel << endl;
            countReino++;
        } else {
            if (count > 0) {
                cout << "[Candidato a Reino]/Nombre: " << root->guardian.name << ", Puntos de Poder: " << root->guardian.powerLevel << endl;
                count--;
            }
        }
    }
    DescendentPower(root->left, count, countReino);
}
// Actualiza el nivel de poder del guardian según el resultado de la batalla.
void PoderPostBatalla(Guardian& guardian, int puntajeBatalla){
	if (puntajeBatalla > 0){															
		if (guardian.powerLevel + puntajeBatalla <= 100){								// Verificar si sumar los puntos llevará al poder por encima de 100.
			guardian.powerLevel += puntajeBatalla;										// Encargado de sumar puntaje.
		} else {
			guardian.powerLevel = 100;													// Si supera el parametro establecido, se limita el puntaje a 100.
		}
	} else {
		guardian.powerLevel -= puntajeBatalla;										// Encargado de restar puntaje.
	}
}
// Verifica si un guardian tiene al menos un aprendiz en el arbol.
bool MaestroGuardian (const Guardian& guardian, Node* guardianTree){
	if (guardianTree == nullptr) {
		return false; 																	// Si el arbol se encuentra vacio, el guardian no es ni aprendiz ni maestro.
	}
	if (guardian.name == guardianTree->guardian.name) {
		return guardianTree->left != nullptr || guardianTree->right != nullptr;			// Si el guardián tiene el mismo nombre que el guardián actual dentro de ese nodo. Se verifica si el nodo actual tiene al menos un hijo. 
	}
	return MaestroGuardian (guardian, guardianTree->left) || MaestroGuardian (guardian, guardianTree->right);
}

//---------------------------------------------COMIENZO DE LA FUNCION MAIN----------------------------------------------
int main (){

	Grafo grafo;
    unordered_set<string> uniqueCity;
    lecturaCiudad("Ciudades.txt", grafo, uniqueCity);
    
    // Función que carga los datos del archivo "Guardianes.txt".
    vector<pair<int, Guardian>> guardianes = leerGuardianesDesdeArchivo("Guardianes.txt");
    
    // Asignar numeros a las ciudades.
    unordered_map<string, int> numCiudad;
    int numero = 1;
    for (const auto &ciudad : uniqueCity) {
        numCiudad[ciudad] = numero;
        ++numero;
    }
    
    // Imprimir asignación de numeros a ciudades.
    cout << "\n[ASIGNACION NUMEROS A CIUDADES]: \n";
    cout << endl;
    for (const auto &par : numCiudad) {
        cout << par.second << ":" << par.first << "\n";
    }
	
	// Mapeado de Guardianes con numero asignado.
    unordered_map<int, Guardian> numeroGuardianMap;
    for (const auto& par : guardianes) {
        numeroGuardianMap[par.first] = par.second;
    }
    
	// Menu principal del juego
	bool cerrar = false;
	while (!cerrar){
		cout << endl;
		cout << "---------------------BIENVENIDO FORASTERO---------------------" << endl;
		cout << "----------------AL JUEGO: THE GUARDIAN BATTLE----------------" << endl;
		cout << "---[MENU PRINCIPAL]" << endl;
		cout << "1- Lista de Guardianes Candidatos" << endl;
        cout << "2- Ver Guardian Específico" << endl;
        cout << "3- Conoce el Reino" << endl;
        cout << "4- Presenciar Disputa" << endl;
        cout << "5- Salir del Juego" << endl;
        
        int opcion;
        cout << "Ingrese una opcion [1-5]: ";
        cin >> opcion;
        
        switch (opcion){
        	case 1:{
				break;
			}
			case 2: {
			    int numeroGuardian;
			    
			    cout << endl;
			    // Mostrar la lista de guardianes con sus números asignados
			    cout << "[LISTA DE GUARDIANES]" << endl;
			    for (const auto& par : guardianes) {
			        cout << par.first << "-" << par.second.name << endl;
			    }
			    
			    cout << "Ingrese numero de Guardian a conocer: ";
			    cin >> numeroGuardian;
			
			    auto it = numeroGuardianMap.find(numeroGuardian);
			    if (it != numeroGuardianMap.end()) {
			        cout << endl;
			        cout << "Nombre: " << it->second.name << endl;
			        cout << "Nivel de Poder: " << it->second.powerLevel << endl;
			        cout << "Maestro: " << it->second.master << endl;
			        cout << "Ciudad: " << it->second.city << endl;
			    } else {
			        cout << "!Oops¡ Numero ingresado no valido." << endl;
			    }
			
			    break;
			}
			case 3:{
				
				int grafo1;
				cout << "---------------------BIENVENIDOS AL REINO---------------------" << endl;
				imprimirGrafo(grafo);
				
				cout << endl;
				cout << "Te gustaria ver nuestro reino en forma de Matriz? ";
				cout << "[1=Si / 2=No]" << endl;
				cin >> grafo1;
				
				if (grafo1 = 1){
					// Impresion de Matriz de Adyacencia con numeros.
					MatrizComparacion(uniqueCity, grafo, numCiudad);
				} else if (grafo1 = 2){
					cout << "Lo lamento don BUEN PROGRAMADOOR, pero de momento son las unicas formas de visitar el reino" << endl;
				} else {
					break;
				}
			}
			case 4:{
				cout << endl;
				cout << "Los Guardianes se encuentran en la Super Guardia Super Secreta haciendo cosas de Guardianes super Valerosos (Dormir arropados placidamente)" << endl;
				cout << "Por lo que ahora los Guardianes no tienen fuerzas para luchar" << endl;
				cout << "PERO SIGUE ASI FORASTERO, ME GUSTA TU INSISTENCIA" << endl;
				break;
			}
			case 5:{
				cerrar = true;
				break;
			}
			default:{
				cout << endl;
				cout << "¡Oops! Opcion ingresada no es valida. Favor intente nuevamente" << endl;
				break;
			}
		}
	}
	return 0;
}
