#include <iostream>
#include "tabulero.hpp"

int main() {

    Tabulero t = Tabulero::readFromInput();
    std::cout << t.calculateArea() << std::endl;
}