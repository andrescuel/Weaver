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
    std::string texto;

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
                if (eventos.text.unicode == '\r' && texto.size() == 4){
                    palabras.push_back(texto);
                    nuevaLinea();
                    imprimirCuadrados();
                    std::cout << "dibuje texto" << std::endl;
                    window.draw(imprimir(texto));
                    texto = "";
                }else if(eventos.text.unicode >= 97 && eventos.text.unicode <= 122 && texto.size() < 4){
                    texto += static_cast<char>(eventos.text.unicode);
                }else if(eventos.text.unicode == 241 && texto.size() < 4){
                    texto += "'ñ'";

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
        std::cout << "imprimi lo dibujado" << std::endl;
        window.display();
        std::cout << "limpie lo dibujado" << std::endl;
        //window.clear(sf::Color::White);
    }

}

sf::Text Vista::imprimir(std::string palabra) {
    texto.setString(palabra);
    texto.setPosition(50.f, 50.f);
    return texto;
}

void Vista::tamañoLetra(int tamano ){
    texto.setCharacterSize(tamano);
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



    if(cuadrados.size()-1 >= lineasVisibles && eventos.text.unicode == '\r'){
        inicioVisible++;
    }
    for (int i = inicioVisible; i < inicioVisible + lineasVisibles && i < cuadrados.size(); ++i) {
        for(int j = 0; j < 4; j++) {
            cuadrados[i][j].setPosition(cuadrados[i][j].getPosition().x, 150.f + 100.f * cont * 1.2f);
            std::cout << "dibuje cuadros" << std::endl;
            window.draw(cuadrados[i][j]);
        }
        cont++;
    }

}