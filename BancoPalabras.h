#ifndef WEAVER_BANCOPALABRAS_H
#define WEAVER_BANCOPALABRAS_H

#include <vector>
#include <string>
#include <regex>
#include <fstream>

using namespace std;

class BancoPalabras {
private:
    vector<string> palabras;

public:
    BancoPalabras(const vector<string>& palabras);
    BancoPalabras(const string& pathPalabras);

    bool esPalabraValida(const string& palabra);
    vector<string> getPalabrasRegex(const string& regex_str);
    vector<string> getPalabras();

    static bool difiereUnaLetra(const string& palabra1, const string& palabra2);
    static bool esArchivoVacio(fstream& archivo);
    static bool esArchivoVacio(ifstream& archivo);
    static string toLowerCase(const string& palabra);
};

#endif //WEAVER_BANCOPALABRAS_H
