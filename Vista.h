#ifndef WEAVER_VISTA_H
#define WEAVER_VISTA_H

#include <SFML/Graphics.hpp>
#include "Solucionador.h"

class Vista {
    bool prueba = false;
    //encargado de mirar si hay errores en el programa
    bool error;
    //caja donde se imprimira el texto que indique el error existente
    sf::RectangleShape cajaError;
    //guardar la linea de cuadrados con sus modificaciones pertinentes para agilizar el procesamiento
    std::vector<sf::RectangleShape> linea;
    //guarda las palabras incio y final
    std::vector<std::string> palabrasEstaticas;
    //guarda las palabras digitadas por el usuario
    std::vector<std::string> palabras;
    //ventana que se renderizara y donde se realizaran todos los cambios
    sf::RenderWindow window;
    //variable encargadad de estar atenta de todos los eventos de la ventana renderizada
    sf::Event eventos;
    //guarda en su interior el tipo de fuente que se utilziara durante el programa
    sf::Font fuente;
    //encargado de guardar el texto que aparecera por pantalla
    sf::Text texto;
    //encargada guardar el error que se mostrara por pantalla
    sf::Text textoError;
    //guarada los cuadrados que se mostraran por pantalla
    std::vector<std::vector<sf::RectangleShape>> cuadrados;
    //guarda los cuadros que le pertenecen a las palabra inicial y final
    std::vector<std::vector<sf::RectangleShape>> cuadrosEstaticos;
    //desde donde se le permitara ver al usuario de todos los vectores creados anteriormente
    int inicioVisible;

public:
    //encargado de inicializar todas las respectivas variables
    Vista();
    //bucle principal
    void principal();
    //encargada de tomar las letres que el usuario ingrese y guardarlas para su correcto procesamiento
    void escritura();
    //encargada de dibujar en pantalla los cuadros del texto y el texto perteneciente a cada cuadro
    void imprimirCuadrado();
    //encargada de imprimir el texto y los cuadrados de la palabra incial y final
    void imprimirCuadradosEstaticos();
    //econtrar los errores existentes y mostrarlos por pantalla
    void imprimirErrores();
    //imprime to do por pantalla
    void imprimir();
    //cambia el color para indicar cual que caracter es igual al final
    void cambiarColorCuadro();
    //cambia el color al borrar las palabras
    void devolverColor();
};

#endif //WEAVER_VISTA_H
