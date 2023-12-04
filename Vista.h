#ifndef WEAVER_VISTA_H
#define WEAVER_VISTA_H

#include <SFML/Graphics.hpp>

class Vista {

    std::vector<std::string> palabras;
    sf::RenderWindow window;
    sf::Event eventos;
    sf::Font fuente;
    sf::Text texto;
    std::vector<std::vector<sf::RectangleShape>> cuadrados;
    int inicioVisible;

public:
    Vista();
    //bucle principal
    void principal();
    sf::Text imprimir(std::string);
    void nuevaLinea();
    void tamañoLetra(int);
    void imprimirCuadrados();
};


#endif //WEAVER_VISTA_H
