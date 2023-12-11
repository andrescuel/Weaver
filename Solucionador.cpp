#include "Solucionador.h"

Solucionador::Solucionador(const vector<string>& palabras, const string& pathBucket): bancoPalabras(palabras), pathBucket(pathBucket) {
    construirGrafo();
}

Solucionador::Solucionador(const string& pathPalabras, const string& pathBucket): bancoPalabras(pathPalabras), pathBucket(pathBucket) {
    construirGrafo();
}

void Solucionador::construirGrafo() {
    const unordered_map<string, vector<string>>& bucket = getBucket();

    for(auto[k,v]: bucket){
        for(const string& word: v){
            grafoPalabras.addEdge(k, word);
        }
    }
}

unordered_map<string, vector<string>> Solucionador::getBucket() {
    unordered_map<string, vector<string>> bucket;
    fstream archivoBucket(pathBucket, ios::out|ios::in|ios::app);

    if(archivoBucket.is_open() && !BancoPalabras::esArchivoVacio(archivoBucket)) {
        std::string line;
        while (std::getline(archivoBucket, line)) {
            std::istringstream iss(line);
            std::string key;
            iss >> key;

            std::vector<std::string> values;
            std::string value;
            while (iss >> value) {
                values.push_back(value);
            }

            bucket[key] = values;
        }
    }
    else {
        bucket = construirBucket();

        if(archivoBucket.is_open()) {
            archivoBucket.seekg(0, ios::beg);
            for (const auto& par : bucket) {
                // Escribir la key primero
                archivoBucket << par.first << ' ';

                // Escribir los valores que almacena el vector
                for (const auto& value : par.second) {
                    archivoBucket << value << ' ';
                }

                // Añadir un enter para cada par key-valor
                archivoBucket << '\n';
            }
        }
    }

    archivoBucket.close();
    return bucket;
}

Graph<string> Solucionador::getGrafoPalabras() {
    return grafoPalabras;
}

unordered_map<string, vector<string>> Solucionador::construirBucket() {
    const vector<string> &palabras = bancoPalabras.getPalabras();
    unordered_map<string, vector<string>> bucket;

    for (size_t i = 0; i < palabras.size(); i++){
        for (size_t j = i + 1; j < palabras.size(); j++){
            if (BancoPalabras::difiereUnaLetra(palabras[i], palabras[j])) {
                bucket[palabras[i]].push_back(palabras[j]);
                bucket[palabras[j]].push_back(palabras[i]);
            }
        }
    }

    return bucket;
}

vector<string> Solucionador::encontrarCaminoMinimoPalabras(const string &p1, const string &p2) {
    return grafoPalabras.dijkstraShortestPath(BancoPalabras::toLowerCase(p1), BancoPalabras::toLowerCase(p2));
}






