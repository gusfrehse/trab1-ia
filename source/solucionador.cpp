#include "solucionador.hpp"

#include <tuple>
#include <queue>
#include <iostream>

// Solucionador::Solucionador()
// {
// }


// TODO: adicionar struct para substituir tupla pq precisamos saber o caminho.
// Guarda tabulero, heuristica, canto + cor. 
auto solve(const Tabulero& tabulero) -> void
{   
    const auto pQueueComp = [](const auto &a, const auto &b) {
        return std::get<1>(a) > std::get<1>(b);
    };
    
    auto pQueue = std::priority_queue<
                    std::tuple<Tabulero, int>, 
                    std::vector<std::tuple<Tabulero, int>>,
                    decltype(pQueueComp)
                    >(pQueueComp);

    for (auto cor = 0; cor < tabulero.getColors(); cor++)
    {
        for (auto canto : {Canto::TopLeft, Canto::TopRight, Canto::BottomLeft, Canto::BottomRight})
        {
            auto tabuleroCopia = tabulero.paint(Canto::TopLeft, cor);
            pQueue.push(std::make_tuple(tabuleroCopia, tabuleroCopia.calculateArea()));  
        }
    }

    while (!pQueue.empty())
    {
        auto tabuleroAtual = std::get<0>(pQueue.top());
        auto perimetroAtual = std::get<1>(pQueue.top());
        pQueue.pop();

        if (tabuleroAtual.isSolved())
        {
            std::cout << "Solucion encontrada con perimetro " << perimetroAtual << std::endl;
            return;
        }

        for (auto cor = 0; cor < tabuleroAtual.getColors(); cor++)
        {
            for (auto canto : {Canto::TopLeft, Canto::TopRight, Canto::BottomLeft, Canto::BottomRight})
            {
                auto tabuleroCopia = tabuleroAtual.paint(canto, cor);
                pQueue.push(std::make_tuple(tabuleroCopia, tabuleroCopia.calculateArea()));  
            }
        }
    }
}