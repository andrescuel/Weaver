//
// Created by camil on 30/11/2023.
//

#include "BancoPalabras.h"

BancoPalabras::BancoPalabras(const vector<string>& palabras) : palabras(palabras) {

}

bool BancoPalabras::esPalabraValida(const string& palabra) {
    // Revisar si está dentro del vector de palabras
    return find(palabras.begin(), palabras.end(), palabra) != palabras.end();
}

vector<string> BancoPalabras::obtenerPalabrasRegex(const string& regex_str) {
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

vector<string> BancoPalabras::obtenerPalabras() {
    return palabras;
}