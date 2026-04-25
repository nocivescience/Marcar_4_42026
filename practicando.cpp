#include <SFML/Graphics.hpp>
#include <vector>
# include <random>
#include <iostream>

#define WIDTH 800
#define HEIGHT 600
#define RED "\033[31m"
#define RESET "\033[0m"

int main() {
    std::cout << RED << "Hola" << RESET << "\nmundo" << std::endl;
    return 0;
}