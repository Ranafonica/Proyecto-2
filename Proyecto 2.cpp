// Librerias a utilizar en el código.
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <limits>
#include <random>

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
	printDescendingPower(root->right, count, countReino);								// Se imprime 
	
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
