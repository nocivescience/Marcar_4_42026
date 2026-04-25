#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <iostream>

#define WIDTH 800
#define HEIGHT 600
#define RED "\033[31m"
#define RESET "\033[0m"

struct TemporaryShape {
    sf::CircleShape shape;
    sf::Clock lifetime;
};

int main()
{
    sf::RenderWindow window(sf::VideoMode({WIDTH, HEIGHT}), "Puntos Aleatorios - SFML 3");
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(50, 255);
    std::vector<TemporaryShape> points;
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
                std::cout << RED << "Ventana cerrada por el usuario." << RESET << std::endl;
            }
            if (const auto *mouseClick = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mouseClick->button == sf::Mouse::Button::Left)
                {
                    sf::CircleShape point(3.f);
                    point.setFillColor(sf::Color(
                        static_cast<uint8_t>(dis(gen)),
                        static_cast<uint8_t>(dis(gen)),
                        static_cast<uint8_t>(dis(gen))
                    ));
                    point.setPosition({
                        static_cast<float>(mouseClick->position.x) - 3.f,
                        static_cast<float>(mouseClick->position.y) - 3.f
                    });
                    points.push_back({point, sf::Clock()});
                }
            }
        }
        for (auto it = points.begin(); it != points.end(); ) {
            if (it->lifetime.getElapsedTime().asSeconds() > 3.0f) {
                it = points.erase(it); // Borra de la RAM y actualiza el iterador
            } else {
                ++it;
            }
        }
        window.clear(sf::Color(20, 20, 20));
        for (const auto &p : points){
            window.draw(p.shape);
        }
        window.display();
    }
    return 0;
}