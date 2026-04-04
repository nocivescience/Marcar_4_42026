#include <SFML/Graphics.hpp>
#include <vector>

int main() {
    // En SFML 3, VideoMode ahora prefiere sf::Vector2u
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Marcador de Puntos - SFML 3");
    
    std::vector<sf::CircleShape> points;

    while (window.isOpen()) {
        // En SFML 3, pollEvent() devuelve un std::optional<sf::Event>
        while (const std::optional event = window.pollEvent()) {
            
            // 1. Cerrar ventana
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            // 2. Detectar clic del ratón
            // Usamos getIf para verificar el tipo de evento de forma segura
            if (const auto* mouseClick = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mouseClick->button == sf::Mouse::Button::Left) {
                    sf::CircleShape point(3.f); // Radio del punto
                    point.setFillColor(sf::Color::Cyan);
                    
                    // Las coordenadas ahora están dentro de la estructura del evento específico
                    point.setPosition({static_cast<float>(mouseClick->position.x) - 3.f, 
                                      static_cast<float>(mouseClick->position.y) - 3.f});
                    
                    points.push_back(point);
                }
            }
        }

        window.clear(sf::Color(20, 20, 20));

        for (const auto& p : points) {
            window.draw(p);
        }

        window.display();
    }

    return 0;
}