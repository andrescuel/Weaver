#include "Vista.h"
#include <iostream>

Vista::Vista(){
    if(!fuente.loadFromFile("C:/Windows/Fonts/MATURASC.TTF")){
        std::cout << "no cargo";
    }
    texto.setFillColor(sf::Color::Black);
    texto.setFont(fuente);
    nuevaLinea();
    inicioVisible = 0;
}

void Vista::principal(){

    window.create(sf::VideoMode(800, 800), "SFML Window");


    imprimirCuadrados();


    while(window.isOpen()){
        while (window.pollEvent(eventos)) {
            if (eventos.type == sf::Event::KeyPressed) {
                if (eventos.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }

            if (eventos.type == sf::Event::TextEntered) {
                // Al presionar "Enter", agregar una nueva línea
                if (eventos.text.unicode == '\r') {

                    nuevaLinea();
                    imprimirCuadrados();
                }
            }
            if (eventos.type == sf::Event::MouseWheelScrolled){
                if (eventos.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
                    if (eventos.mouseWheelScroll.delta > 0 && inicioVisible > 0 && cuadrados.size() > 2) {
                        inicioVisible--;
                        imprimirCuadrados();
                    }
                    else if (eventos.mouseWheelScroll.delta < 0 && inicioVisible < cuadrados.size() - 3 && cuadrados.size() > 2) {
                        // Desplazar hacia abajo
                        inicioVisible++;
                        imprimirCuadrados();
                    }
                }
            }
        }
    }

}

sf::Text Vista::imprimir() {
    texto.setString(frace);
    texto.setPosition(50.f, 50.f);
    return texto;
}

void Vista::tamañoLetra(int tamano ){
    texto.setCharacterSize(tamano);
}

sf::Color generarColorAleatorio() {
    int r = std::rand() % 256;
    int g = std::rand() % 256;
    int b = std::rand() % 256;

    return sf::Color(r, g, b);
}

void Vista::nuevaLinea(){
    std::vector<sf::RectangleShape> linea(4);
    for(int i = 0; i < 4; i++) {
        linea[i].setSize(sf::Vector2f(100.f, 100.f));
        linea[i].setFillColor(sf::Color::Transparent);
        linea[i].setOutlineColor(sf::Color::Black);
        linea[i].setOutlineThickness(2.f);
        linea[i].setPosition(i * (100.f + 12.f) + 50.f,0.0f);
    }
    cuadrados.push_back(linea);
}

void Vista::imprimirCuadrados(){
    int cont = 1;

    int lineasVisibles = 3;
    window.clear(sf::Color::White);

    if(cuadrados.size()-1 >= lineasVisibles && eventos.text.unicode == '\r'){
        inicioVisible++;
    }
    for (int i = inicioVisible; i < inicioVisible + lineasVisibles && i < cuadrados.size(); ++i) {
        for(int j = 0; j < 4; j++) {
            cuadrados[i][j].setPosition(cuadrados[i][j].getPosition().x, 150.f + 100.f * cont * 1.2f);
            window.draw(cuadrados[i][j]);
        }
        cont++;
    }
    window.display();


}
