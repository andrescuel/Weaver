//
// Created by rubio on 1/12/2023.
//

#include "Solucionador.h"

Solucionador::Solucionador(const vector<string>& palabras): bancoPalabras(new BancoPalabras(palabras)) {

}

bool Solucionador::difiereUnaLetra(const string &palabra1, const string &palabra2) {
    int cuentaDif = 0;
    for (size_t i = 0; i < palabra1.length(); i++) {
        if (palabra1[i] != palabra2[i]){
            if (++cuentaDif > 1)
                return false;
        }
    }
    return true;
}

void Solucionador::construirGrafo(const vector<string> &palabras) {
    for (size_t i = 0; i < palabras.size(); i++){
        for (size_t j = i + 1; i < palabras.size(); j++){
            if (difiereUnaLetra(palabras[i], palabras[j])) {
                bucket[palabras[i]].push_back(palabras[j]);
                bucket[palabras[j]].push_back(palabras[i]);
            }
        }
    }
}




