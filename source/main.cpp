#include <iostream>
#include "tabulero.hpp"
#include "solucionador.hpp"

int main()
{
    Tabulero tabulero = Tabulero::readFromInput();

    //std::cout << tabulero.calculateArea() << std::endl;

    //exit(0);

    auto solucion = solve(tabulero);

    std::cout << solucion.size() << std::endl;
    
    for (const auto& acao : solucion)
    {
        std::cout << ((char) acao.first) << " " << acao.second << " ";
    }

    std::cout << std::endl;

    return 0;
}