//
// Created by Juan on 12/8/2023.
//

#ifndef WEAVER_GAMELOGIC_H
#define WEAVER_GAMELOGIC_H
#include "Solucionador.h"
#include <random>
#include <cmath>

class GameLogic {
    Solucionador solucionador;
public:
    GameLogic();
    bool esPalabraValida(const string& palabra);
    bool difiereUnaLetra(const string& palabra1, const string& palabra2);
    vector<string> encontrarCaminoMinimoPalabras(const string& p1, const string& p2);
    vector<string> mostarPalabrasInicioYFin(int& dificultad);
    void guardarPartida(const vector<string>& palabras, const string& nombreArchivo);
    vector<string> cargarPartida(const string& nombreArchivo);
};


#endif //WEAVER_GAMELOGIC_H
