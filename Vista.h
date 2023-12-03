#ifndef WEAVER_VISTA_H
#define WEAVER_VISTA_H

#include <SFML/Graphics.hpp>

class Vista {

    std::string frace;
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
    sf::Text imprimir();
    void nuevaLinea();
    void tamañoLetra(int);
    void imprimirCuadrados();
};


#endif //WEAVER_VISTA_H
