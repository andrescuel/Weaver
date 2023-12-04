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
    palabras.push_back("");
}

void Vista::principal(){

    window.create(sf::VideoMode::getDesktopMode(), "SFML Window", sf::Style::None);

    imprimir();


    while(window.isOpen()){
        while (window.pollEvent(eventos)) {
            if (eventos.type == sf::Event::KeyPressed) {
                if (eventos.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }

            if (eventos.type == sf::Event::TextEntered) {
                // Al presionar "Enter", agregar una nueva línea
                if (eventos.text.unicode == '\r' && palabras[palabras.size()-1].size() >= 4){
                    nuevaLinea();
                    imprimir();
                    palabras.push_back("");
                }else if(eventos.text.unicode >= 97 && eventos.text.unicode <= 122 && palabras[palabras.size()-1].size() < 4){
                    palabras[palabras.size()-1] += static_cast<char>(eventos.text.unicode);
                    imprimir();
                }else if(eventos.text.unicode == 241 && palabras[palabras.size()-1].size() < 4){
                    palabras[palabras.size()-1] += "'ñ'";
                    imprimir();
                }
            }
            if (eventos.type == sf::Event::MouseWheelScrolled){
                if (eventos.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
                    if (eventos.mouseWheelScroll.delta > 0 && inicioVisible > 0 && cuadrados.size() > 2) {
                        inicioVisible--;
                        imprimir();
                    }
                    else if (eventos.mouseWheelScroll.delta < 0 && inicioVisible < cuadrados.size() - 3 && cuadrados.size() > 2) {
                        // Desplazar hacia abajo
                        inicioVisible++;
                        imprimir();
                    }
                }
            }
        }
    }
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

void Vista::imprimir(){
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
            if(palabras.size() > i){
                if(palabras[i].size() > j){
                    texto.setString(palabras[i][j]);
                    texto.setPosition(cuadrados[i][j].getPosition().x + 3, cuadrados[i][j].getPosition().y+3);
                    window.draw(texto);
                }

            }
        }
        cont++;
    }
    window.display();

}