#include <iostream>
#include <unordered_map>
#include <vector>
#include <limits>
#include <fstream>
#include <sstream>
#include <time.h>
#include <stdlib.h>

using namespace std;

struct Guardian {
    string name;
    int powerLevel;
    string master;
    string city;
    vector<string> apprentices;
};

class GrafoUnidireccional {
	private:
	    unordered_map<string, int> cityIndexMap;
	    vector<vector<int>> adjacencyMatrix;
	    vector<string> cities;
	public:
	    GrafoUnidireccional() = default;
	    void addEdge(const string& src, const string& dest, int weight) {
	        int srcIndex = getIndex(src);
	        int destIndex = getIndex(dest);
	        adjacencyMatrix[srcIndex][destIndex] = weight;
	        adjacencyMatrix[destIndex][srcIndex] = weight;
	        cout << "Conexion add +: " << src << " <-> " << dest << " weight: " << weight << endl;
    }

    size_t getNumberOfCities() const {
        return cities.size();
    }

    string getCityName(size_t index) const {									// Obtiene el nombre de la ciudad por la inicial.
        if (index < cities.size()) {
            return cities[index];
        }
        return "";
    }

    int getIndex(const string& city) {
        if (cityIndexMap.find(city) == cityIndexMap.end()) {
            int newIndex = cities.size();
            cities.push_back(city);
            cityIndexMap[city] = newIndex;
            for (auto& row : adjacencyMatrix) {									// Adjunta matriz a un tamaño general para todos.
                row.resize(cities.size(), 0);
            }
            adjacencyMatrix.resize(cities.size(), vector<int>(cities.size(), 0));
            return newIndex;
        }
        return cityIndexMap[city];
    }

      void printDetailedGraph() {
        cout << "Ciudades y sus conexiones:" << endl;
        for (size_t i = 0; i < cities.size(); ++i) {
            cout << cities[i] << " conected: ";
            bool hasConnection = false;
            for (size_t j = 0; j < cities.size(); ++j) {
                if (adjacencyMatrix[i][j] != 0) {
                    cout << cities[j] << " (weight: " << adjacencyMatrix[i][j] << ") ";
                    hasConnection = true;
                }
            }
            if (!hasConnection) {
                cout << "No hay conexion";
            }
            cout << endl;
        }
    }
    void printCityConnections(const string& city) {
        int cityIndex = getIndex(city);

        cout << city << " conectada a: ";
        bool hasConnection = false;
        for (size_t i = 0; i < cities.size(); ++i) {
            if (adjacencyMatrix[cityIndex][i] != 0) {
                cout << cities[i] << " (peso: " << adjacencyMatrix[cityIndex][i] << ") ";
                hasConnection = true;
            }
        }
        if (!hasConnection) {
            cout << "Ninguna conexion";
        }
        cout << endl;
    }

    vector<string> getConnectedCities(const string& city) {
        vector<string> connectedCities;
        int cityIndex = getIndex(city);
        cout << "Ciudades conectadas a " << city << ":" << endl;
        for (size_t i = 0; i < cities.size(); ++i) {
            if (adjacencyMatrix[cityIndex][i] != 0) {
                connectedCities.push_back(cities[i]);
                cout << cities[i] << endl;
            }
        }
        return connectedCities;
    }
};

int main() {

    ifstream cityFile("Ciudades.txt");
    if (!cityFile.is_open()) {
        cout << "Archivo de guardianes no se pudo abrir." << endl;
        return 1;
    } else {
        cout << "Archivo abierto de manera satisfactoria." << endl;
    }
	
	// Grafo Unidireccional es llamado a la funcion MAIN.
    GrafoUnidireccional graph;

    string cityLine;
    getline(cityFile, cityLine); // Ignorar la primera línea

    while (getline(cityFile, cityLine)) 
    {
        istringstream iss(cityLine);
        string city, connection;
        if (getline(iss, city, ',') && getline(iss, connection)) {
                int weight = 1; // Peso por defecto
                graph.addEdge(city, connection, weight); // Agregar la conexión al grafo
            }
    }

    cityFile.close();

    graph.printDetailedGraph(); // Imprimir lista detallada de ciudades y conexiones
    ifstream guardianFile("Guardianes.txt");
    if (!guardianFile.is_open()) {
    	cout << "Archivo is BROKEN." << endl;
        cout << "Archivo de guardianes no se pudo abrir." << endl;
        return 1;
    } else {
        cout << "Archivo is SAFE." << endl;
        cout << "Archivo abierto de manera satisfactoria." << endl;
    }
	
	// Almacenamiento de Guardianes en vectores.
    vector<Guardian> guardians;

    string guardianLine;
    getline(guardianFile, guardianLine); // Funcion permite saltar primera linea del archivo .txt.

    while (getline(guardianFile, guardianLine)) {
        istringstream iss(guardianLine);
        string name, powerLevelStr, master, city;
        if (getline(iss, name, ',') && getline(iss, powerLevelStr, ',') && 
            getline(iss, master, ',') && getline(iss, city, ',')) {
            int powerLevel = stoi(powerLevelStr);

            Guardian guardian;
            guardian.name = name;
            guardian.powerLevel = powerLevel;
            guardian.master = master;
            guardian.city = city;

            guardians.push_back(guardian);
        }
    }

    guardianFile.close();

    bool exitGame = false;
    
    system("cls") ;

    while (!exitGame) {
        cout << "Bienvenido Forastero" << endl;
        cout << "Al juego de los Guardianes" << endl;
        cout << endl;
        cout << "[MENU]:" << endl;
        cout << "1- Lista de Candidatos" << endl;
        cout << "2- Ver Guardian" << endl;
        cout << "3- Conoce el Reino" << endl;
        cout << "4- Ver Enfrentamiento" << endl;
        cout << "5- Salir del Juego" << endl;

        int opcion;
        cout << endl;
        cout << "Ingresa la opcion [1-5]: ";
        cin >> opcion;

        switch (opcion) {
        	//Lista candidatos
            case 1:
                cout << "[GUARDIANES]:" << endl;
                cout << "[Lista de candidatos]" << endl;
                
                for (const auto& guardian : guardians) {
                    cout << "Nombre: " << guardian.name << endl;
                    cout << "Nivel de Poder: " << guardian.powerLevel << endl;
                    cout << "Maestro: " << guardian.master << endl;
                    cout << "Ciudad: " << guardian.city << endl;
                    cout << endl;
                }
                break;
            case 2:
                break;
            case 3:
            // Conocer el reino
            cout << "1- Lista Ciudades/Conexiones" << endl;
            cout << "2- Conexion con Ciudad a Escoger" << endl;

            int opcionReino;
            cout << "¡Buena decision!" << endl;
            cout << "Ingresa tu eleccion: ";
            cin >> opcionReino;

            if (opcionReino == 1) {
                graph.printDetailedGraph();
                
            } else if (opcionReino == 2) {
                cout << "Las ciudades disponibles son: " << endl;
                
                // Recorre las ciudades disponibles
                for (size_t i = 0; i < graph.getNumberOfCities(); ++i) {
                    cout << i + 1 << ". " << graph.getCityName(i) << endl;
                }

                int numCiudad;
                cout << "Favor de ingresar un numero para conocer sus conexiones: ";
                cin >> numCiudad;

                if (numCiudad >= 1 && numCiudad <= graph.getNumberOfCities()) {
                	
                    string cityToCheck = graph.getCityName(numCiudad - 1);
                    graph.printCityConnections(cityToCheck);
                    
                } else {
                    cout << "Dicho numero ingresado no es válido" << endl;
                }
            } else {
                cout << "Opcion invalida." << endl;
            }
            break;
            case 4:
                break;
                
            case 5:
                exitGame = true;
                break;
            default:
            	
                cout << "Favor ingresar una de las opciones en pantalla." << endl;
                cout << endl;
                break;
        }
    }

    return 0;
}
