#include "Vista.h"
#include <iostream>

Vista::Vista(){
    if(!fuente.loadFromFile("C:/Windows/Fonts/COOPBL.TTF")){
        std::cout << "no cargo";
    }
    texto.setCharacterSize(50);
    texto.setFillColor(sf::Color::Black);
    texto.setFont(fuente);
    std::vector<sf::RectangleShape> linea(4);
    for(int j = 0; j < 2; j++) {
        for (int i = 0; i < 4; i++) {
            linea[i].setSize(sf::Vector2f(100.f, 100.f));
            linea[i].setFillColor(sf::Color(196, 196, 196));
            linea[i].setPosition(i * (100.f + 12.f) + 75.f,  0.f);
        }
        cuadrosEstaticos.push_back(linea);
    }

    nuevaLinea();
    inicioVisible = 0;
    palabras.push_back("");
    palabrasEstaticas.push_back("LIMA");
    palabrasEstaticas.push_back("LOMO");
}

void Vista::principal(){

    window.create(sf::VideoMode(600,700), "SFML Window", sf::Style::Close);

    imprimir();


    while(window.isOpen()){
        while (window.pollEvent(eventos)) {
            if (eventos.type == sf::Event::Closed) {
                window.close();
            }


            if (eventos.type == sf::Event::TextEntered) {
                escritura();
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

void Vista::escritura(){
    // Al presionar "Enter", agregar una nueva línea
    if (eventos.text.unicode == '\r' && palabras[palabras.size()-1].size() >= 4){
        if(palabras.size() >= 3) inicioVisible++;
        palabras.push_back("");
        nuevaLinea();
        imprimir();
    }else if(eventos.text.unicode >= 97 && eventos.text.unicode <= 122 && palabras[palabras.size()-1].size() < 4){
        palabras[palabras.size()-1] += std::toupper(static_cast<char>(eventos.text.unicode));
        if(palabras.size() > 2) inicioVisible = palabras.size()-3;
        imprimir();
    }else if(eventos.text.unicode == 241 && palabras[palabras.size()-1].size() < 4){
        palabras[palabras.size()-1] += "'ñ'";
        if(palabras.size() > 2) inicioVisible = palabras.size()-3;
        imprimir();
    }else if (eventos.key.code == 8){
        if (!palabras[palabras.size()-1].empty()) {
            palabras[palabras.size()-1].pop_back();
        }else if(palabras.size() > 1){
            palabras.pop_back();
            cuadrados.pop_back();
            if(inicioVisible != 0) inicioVisible--;
        }
        imprimir();
    }
}

void Vista::nuevaLinea(){
    std::vector<sf::RectangleShape> linea(4);
    for(int i = 0; i < 4; i++) {
        linea[i].setSize(sf::Vector2f(100.f, 100.f));
        linea[i].setFillColor(sf::Color::Transparent);
        linea[i].setOutlineColor(sf::Color(196, 196, 196));
        linea[i].setOutlineThickness(2.f);
        linea[i].setPosition(i * (100.f + 12.f) + 75.f,0.0f);
    }
    cuadrados.push_back(linea);
}

void Vista::imprimir(){
    int cont = 2;
    int lineasVisibles = 3;

    window.clear(sf::Color::White);


    for (int i = inicioVisible; i < inicioVisible + lineasVisibles && i < cuadrados.size(); i++) {
        for(int j = 0; j < 4; j++) {
            if(palabras[i].size() == j){
                cuadrados[i][j].setOutlineColor(sf::Color::Black);
            }
            cuadrados[i][j].setPosition(cuadrados[i][j].getPosition().x,  100.f * cont * 1.2f - 70.f);
            window.draw(cuadrados[i][j]);
            cuadrados[i][j].setOutlineColor(sf::Color(196, 196, 196));
            if(palabras[i].size() > j){
                texto.setString(palabras[i][j]);
                texto.setPosition(cuadrados[i][j].getPosition().x + 30.f, cuadrados[i][j].getPosition().y + 17.f);
                window.draw(texto);
            }

        }
        cont++;
    }
    cont = 1;
    for(int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            cuadrosEstaticos[i][j].setPosition(cuadrosEstaticos[i][j].getPosition().x,  100.f * cont * 1.2f - 70.f);
            window.draw(cuadrosEstaticos[i][j]);
            texto.setString(palabrasEstaticas[i][j]);
            texto.setPosition(cuadrosEstaticos[i][j].getPosition().x + 30.f, cuadrosEstaticos[i][j].getPosition().y + 17.f);
            window.draw(texto);
        }
        cont = (cuadrados.size() < 3) ?(cuadrados.size()+2) :(5);
    }
    window.display();

}