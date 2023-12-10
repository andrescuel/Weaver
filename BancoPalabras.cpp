#include "BancoPalabras.h"

BancoPalabras::BancoPalabras(const vector<string>& palabras) : palabras(palabras) {

}

BancoPalabras::BancoPalabras(const std::string &pathPalabras) {
    ifstream archivoPalabras(pathPalabras);
    if(archivoPalabras.is_open() && !BancoPalabras::esArchivoVacio(archivoPalabras)) {
        std::string line;
        while (std::getline(archivoPalabras, line)) {
            palabras.push_back(line);
        }
    }
}

bool BancoPalabras::esPalabraValida(const string& palabra) {
    string palabraLower;
    // Convierte a minusculas
    for(char letra: palabra){
        if(letra == '\321'){
            palabraLower.append("ñ");
        }else{
            palabraLower += tolower(letra);
        }
    }
    return find(palabras.begin(), palabras.end(), palabraLower) != palabras.end();
}

vector<string> BancoPalabras::getPalabrasRegex(const string& regex_str) {
    regex patron(regex_str);
    vector<string> palabrasEncontradas;

    for (const string& palabra: palabras) {
        // Si la palabra cumple el patrón, agregar al vector de palabras encontradas
        if (regex_match(palabra, patron)) {
            palabrasEncontradas.push_back(palabra);
        }
    }

    return palabrasEncontradas;
}

vector<string> BancoPalabras::getPalabras() {
    return palabras;
}

bool BancoPalabras::difiereUnaLetra(const string &palabra1, const string &palabra2) {
    int cuentaDif = 0;
    for (size_t i = 0; i < palabra1.length(); i++) {
        if (palabra1[i] != palabra2[i]){
            if (++cuentaDif > 1)
                return false;
        }
    }
    return true;
}

bool BancoPalabras::esArchivoVacio(fstream& archivo) {
    return archivo.peek() == ifstream::traits_type::eof();
}

bool BancoPalabras::esArchivoVacio(ifstream& archivo) {
    return archivo.peek() == ifstream::traits_type::eof();
}