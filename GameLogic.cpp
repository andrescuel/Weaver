//
// Created by Juan on 12/8/2023.
//

#include "GameLogic.h"


GameLogic::GameLogic() : solucionador("../archivos/palabras.txt","Bucket"){}

bool GameLogic::esPalabraValida(const string &palabra) {
    return solucionador.bancoPalabras.esPalabraValida(palabra);
}

bool GameLogic::difiereUnaLetra(const string &palabra1, const string &palabra2) {
    return solucionador.bancoPalabras.difiereUnaLetra(palabra1,palabra2);
}

vector<string> GameLogic::encontrarCaminoMinimoPalabras(const string &p1, const string &p2) {
    return solucionador.encontrarCaminoMinimoPalabras(p1,p2);
}

vector<string> GameLogic::mostarPalabrasInicioYFin() {
    vector<string> palabrasInicioFin;
    string palabraInicio, palabraFin;

    std::random_device rd;   // Obtener una semilla aleatoria del dispositivo
    std::mt19937 gen(rd());  // generador
    std::uniform_int_distribution<> distribucion(1, solucionador.getGrafoPalabras().vertexList.size() - 1); // rango
    int randomNum = distribucion(gen);

    palabraInicio = solucionador.getGrafoPalabras().vertexList.get(randomNum)->data;
    palabrasInicioFin.push_back(palabraInicio);
    /*for (int i = 0; i < randomNum; i++){

    }*/

    return palabrasInicioFin;
}

void GameLogic::guardarPartida(const vector<string> palabras, const string& nombreArchivo) {
    fstream archivoPartida(nombreArchivo);
    if(archivoPartida.is_open()) {
        if (!BancoPalabras::esArchivoVacio(archivoPartida)){
            ofstream archivoPartidaBorrar(nombreArchivo, std::ios::trunc);
            if(archivoPartidaBorrar.is_open()) archivoPartidaBorrar.close();
        }
        for (const string& palabra : palabras) {
            archivoPartida << palabra << endl;
        }
    }
}

vector<string> GameLogic::cargarPartida(const string& nombreArchivo) {
    vector<string> palabrasGuardadas;
    ifstream archivoPartida(nombreArchivo);
    if(archivoPartida.is_open() && !BancoPalabras::esArchivoVacio(archivoPartida)) {
        string line;
        while (std::getline(archivoPartida, line)) {
            palabrasGuardadas.push_back(line);
        }
    }
    return palabrasGuardadas;
}


