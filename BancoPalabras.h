//
// Created by camil on 30/11/2023.
//

#ifndef WEAVER_BANCOPALABRAS_H
#define WEAVER_BANCOPALABRAS_H

#include <vector>
#include <string>
#include <regex>

using namespace std;

class BancoPalabras {
private:
    vector<string> palabras;

public:
    BancoPalabras(const vector<string>& palabras);

    bool esPalabraValida(const string& palabra);
    vector<string> obtenerPalabrasRegex(const string& regex_str);
    vector<string> obtenerPalabras();
};

#endif //WEAVER_BANCOPALABRAS_H
