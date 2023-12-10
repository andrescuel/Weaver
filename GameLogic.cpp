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
    vector<string> visitados;
    Vertex<string>* palabraInicio;
    Vertex<string>* palabraFin;
    bool fueVisitado = false;

    std::random_device rd;   // Obtener una semilla aleatoria del dispositivo
    std::mt19937 gen(rd());  // generador
    std::uniform_int_distribution<> distribucion(4, solucionador.getGrafoPalabras().vertexList.size() - 2); // rango
    int randomNum = 2;

    palabraInicio = solucionador.getGrafoPalabras().vertexList.get(randomNum);
    palabraFin = palabraInicio;

    // facil dificultad = 1
    // medio dificultad = 2
    // dificil dificultad = 3
    for (int i = 0; i < pow(randomNum,dificultad); i++){
        if (palabraFin->connectedTo.size() > 0){
            for (const string& v : visitados){
                if (v == palabraFin->data){
                    fueVisitado = true;
                    break;
                }
            }
            if (!fueVisitado) {
                visitados.push_back(palabraFin->data);
                palabraFin = palabraFin->connectedTo.get(0)->to;
            }
        }
        else if (palabraFin->connectedTo.size() < 1 && i < pow(randomNum,dificultad) / 2){
            palabraInicio = solucionador.getGrafoPalabras().vertexList.get(randomNum + 1);
            palabraFin = palabraInicio;
        }
        else {
            break;
        }
    }
    palabrasInicioFin.push_back(palabraInicio->data);
    palabrasInicioFin.push_back(palabraFin->data);

    return palabrasInicioFin;
}

void GameLogic::guardarPartida(const vector<string>& palabras, const string& nombreArchivo) {
    fstream archivoPartida(nombreArchivo);
    ofstream archivoPartidaBorrar(nombreArchivo);

    if(archivoPartida.is_open()) {
        ofstream archivoPartidaBorrar(nombreArchivo, std::ios::trunc);
        for (const string& palabra : palabras) {
            if (palabra != "" && palabra != " ") archivoPartida << palabra << endl;
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


