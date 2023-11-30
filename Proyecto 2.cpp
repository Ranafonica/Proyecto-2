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

// Estructuras:
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
	DescendentPower(root->right, count, countReino);								// Se imprime.
	
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
int main (){
	
	ifstream fileCiudad("Ciudades.txt");
    if (!fileCiudad.is_open()) {
    	cout << "Archivo Ciudades.txt no encontrado." << endl;
        cout << "No se ha podido abrir correctamente." << endl;
        return 1;
    } else {
    	cout << "Archivo Ciudades.txt encontrado.";
        cout << "...Archivo abierto satisfactoriamente" << endl;
    }
    // Funcion que carga los datos del archivo "Guardianes.txt"
    ifstream fileGuardian("Guardianes.txt");
    if (!fileGuardian.is_open()) {
    	cout << endl;
        cout << "Archivo Guardianes.txt no encontrado." << endl;
        cout << "No se ha podido abrir correctamente." << endl;
        return 1;
    } else {
    	cout << endl;
        cout << "Archivo Guardianes.txt encontrado.";
        cout << "...Archivo abierto satisfactoriamente" << endl;
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
			case 2:{
				
				break;
			}
			case 3:{
				
				break;
			}
			case 4:{
				
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
