//
// Created by Juan on 12/8/2023.
//

#ifndef WEAVER_GAMELOGIC_H
#define WEAVER_GAMELOGIC_H
#include "Solucionador.h"
#include <random>

class GameLogic {
    Solucionador solucionador;
public:
    bool esPalabraValida(const string& palabra);
    bool difiereUnaLetra(const string& palabra1, const string& palabra2);
    vector<string> encontrarCaminoMinimoPalabras(const string& p1, const string& p2);
    vector<string> mostarPalabrasInicioYFin();
};


#endif //WEAVER_GAMELOGIC_H
