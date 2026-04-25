#include <SFML/Graphics.hpp>
#include <vector>
#include <random> // Librería para números aleatorios modernos

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Puntos Aleatorios - SFML 3");
    
    // Configuración del generador aleatorio
    std::random_device rd;  
    std::mt19937 gen(rd()); // Generador Mersenne Twister
    std::uniform_int_distribution<> dis(50, 255); // Rango de 50 a 255 para evitar colores muy oscuros

    std::vector<sf::CircleShape> points;

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (const auto* mouseClick = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mouseClick->button == sf::Mouse::Button::Left) {
                    sf::CircleShape point(3.f);
                    
                    // Generamos los valores y los pasamos directamente
                    // El compilador entenderá que son los canales R, G y B
                    point.setFillColor(sf::Color(
                        static_cast<uint8_t>(dis(gen)), 
                        static_cast<uint8_t>(dis(gen)), 
                        static_cast<uint8_t>(dis(gen))
                    ));

                    point.setPosition({
                        static_cast<float>(mouseClick->position.x) - 3.f, 
                        static_cast<float>(mouseClick->position.y) - 3.f
                    });
                    
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