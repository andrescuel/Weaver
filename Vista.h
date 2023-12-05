#ifndef WEAVER_VISTA_H
#define WEAVER_VISTA_H

#include <SFML/Graphics.hpp>

class Vista {
    std::vector<std::string> palabrasEstaticas;
    std::vector<std::string> palabras;
    sf::RenderWindow window;
    sf::Event eventos;
    sf::Font fuente;
    sf::Text texto;
    std::vector<std::vector<sf::RectangleShape>> cuadrados;
    std::vector<std::vector<sf::RectangleShape>> cuadrosEstaticos;
    int inicioVisible;

public:
    Vista();
    //bucle principal
    void principal();
    void escritura();
    void nuevaLinea();
    void imprimir();
};


#endif //WEAVER_VISTA_H
