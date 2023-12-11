//
// Created by Juan on 12/8/2023.
//

#include "GameLogic.h"


GameLogic::GameLogic() : solucionador("../archivos/palabras.txt","../archivos/bucket.txt"){}

bool GameLogic::esPalabraValida(const string &palabra) {
    return solucionador.bancoPalabras.esPalabraValida(palabra);
}

bool GameLogic::difiereUnaLetra(const string &palabra1, const string &palabra2) {
    return solucionador.bancoPalabras.difiereUnaLetra(palabra1,palabra2);
}

vector<string> GameLogic::encontrarCaminoMinimoPalabras(const string &p1, const string &p2) {
    return solucionador.encontrarCaminoMinimoPalabras(p1,p2);
}

vector<string> GameLogic::mostarPalabrasInicioYFin(int& dificultad) {
    vector<string> palabrasInicioFin;

    srand(time(0));

    int inicio = rand() % 2700, fin = rand() % 2700;

    palabrasInicioFin.push_back(solucionador.bancoPalabras.getPalabras()[inicio]);
    palabrasInicioFin.push_back(solucionador.bancoPalabras.getPalabras()[fin]);
    palabrasInicioFin[0] = solucionador.bancoPalabras.devolver(palabrasInicioFin[0]);
    palabrasInicioFin[1] = solucionador.bancoPalabras.devolver(palabrasInicioFin[1]);
    return palabrasInicioFin;
}

void GameLogic::guardarPartida(const vector<string>& palabras, const int& numeroArchivo) {
    string nombreArchivo = "Partida" + to_string(numeroArchivo);
    fstream archivoPartida(nombreArchivo);
    ofstream archivoPartidaBorrar(nombreArchivo);
    ofstream archivoPartidas("../archivos/partidas.txt", std::ios::app);

    if(archivoPartida.is_open()) {
        ofstream archivoPartidaBorrar(nombreArchivo, std::ios::trunc);
        for (const string& palabra : palabras) {
            if (palabra != "" && palabra != " ") archivoPartida << palabra << endl;
        }
        archivoPartida.close();
    }
    if(archivoPartidas.is_open()) {
        for (const string& palabra : palabras) {
            if (palabra != "" && palabra != " ") archivoPartida << palabra << endl;
        }
        archivoPartidas.close();
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


