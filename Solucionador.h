#ifndef WEAVER_SOLUCIONADOR_H
#define WEAVER_SOLUCIONADOR_H

#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>

#include "BancoPalabras.h"
#include "Graph.h"

using namespace std;

class Solucionador {
private:
    Graph<string> grafoPalabras;
    fstream archivoBucket;

    void construirGrafo();
    unordered_map<string, vector<string>> construirBucket();

public:
    BancoPalabras bancoPalabras;
    Solucionador(const vector<string>& palabras, const string& pathBucket);
    Solucionador(const string& pathPalabras, const string& pathBucket);

    vector<string> encontrarCaminoMinimoPalabras(const string& p1, const string& p2);

    unordered_map<string, vector<string>> getBucket();
    Graph<string> getGrafoPalabras();
};


#endif //WEAVER_SOLUCIONADOR_H
