#ifndef WEAVER_SOLUCIONADOR_H
#define WEAVER_SOLUCIONADOR_H

#include <vector>
#include <string>
#include <unordered_map>

#include "BancoPalabras.h"

using namespace std;

class Solucionador {
private:
    BancoPalabras* bancoPalabras;
    unordered_map<string, vector<string>> bucket;

    static bool difiereUnaLetra(const string& palabra1, const string& palabra2);
    void construirGrafo(const vector<string> &palabras);

public:
    Solucionador(const vector<string>& palabras);
};


#endif //WEAVER_SOLUCIONADOR_H
