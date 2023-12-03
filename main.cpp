#include <SFML/Graphics.hpp>

int main() {
    // Crear una ventana
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");

    // Crear un círculo
    sf::CircleShape circle(50.0f);
    circle.setFillColor(sf::Color::Green);
    circle.setPosition(375.0f, 275.0f);

    while (window.isOpen()) {
        // Procesar eventos
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Borrar la ventana
        window.clear();

        // Dibujar el círculo
        window.draw(circle);

        // Mostrar los cambios
        window.display();
    }

    return 0;
}
