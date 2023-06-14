#include <iostream>
#include "tabulero.hpp"
#include "solucionador.hpp"

int main()
{
    std::cout << "Hello, World!" << std::endl;
    
    Tabulero tabulero = Tabulero::readFromInput();
    solve(tabulero);
    return 0;
}