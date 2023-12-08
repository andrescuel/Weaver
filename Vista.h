#ifndef WEAVER_VISTA_H
#define WEAVER_VISTA_H

#include <SFML/Graphics.hpp>
#include "Solucionador.h"

struct Boton {
    //guarda la caja de los botones que se van a crear
    sf::RectangleShape caja;
    //guarda la caja de colicion por asi decirlo del texto y luego de la caja para poder
    //aprovechar una funcion que me permita validar si hay algo sobre la caja
    sf::FloatRect cajaColision;
    //contructor que me permite crear Botonones con el tamaño correspondiente y sus caracteristicas principales
    Boton(sf::FloatRect);
    Boton();
};

class Vista {
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
    //encargada de controlar la letra de los errores y menus
    sf::Text textoSecundario;
    //guarada los cuadrados que se mostraran por pantalla
    std::vector<std::vector<sf::RectangleShape>> cuadrados;
    //guarda los cuadros que le pertenecen a las palabra inicial y final
    std::vector<std::vector<sf::RectangleShape>> cuadrosEstaticos;
    //desde donde se le permitara ver al usuario de todos los vectores creados anteriormente
    int inicioVisible;
    //valida si el usuario ya gano
    bool winer;
    //vector que guarda las cajas de los botones
    std::vector<Boton> botones;
    //encargado de guardar la posicon del mouse en un momento determinado para su correcto tratamiento
    sf::Vector2i mouse;
    //colicion
    bool colicion;
    //imagen de pausa
    sf::Texture pausa;
    //cuadrado de pausa
    bool pausado;

public:
    //encargado de inicializar todas las respectivas variables
    Vista();
    //para poder reiniciar la variables cuando se desea iniciar un juevo juego
    void reseteo();
    //bucle donde se llama lo encargado de interactuar con el usuario mientras este juega
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
    //Menu para cuando se gana
    void ganador();
    //Menu para empezar el juego
    void inicio();
    //donde se llaman todos los menus y se controla la logica de inicio del juego
    void menus();
    //controla el cambio de color de los botones cuando el mouse esta sobre este
    bool colisionConBoton();
    //controla cuando el usuario hace click sobre los botones y devulve sobre que boton se hizo click
    int click();
    void parar();

};

#endif //WEAVER_VISTA_H
