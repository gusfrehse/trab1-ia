#include "solucionador.hpp"
#include "tabulero.hpp"
#include <tuple>
#include <queue>
#include <iostream>


struct ArvoreBuscaTabuleroGrafoNodo
{
    Tabulero tabulero;
    int heuristica;
    Acao acaoUsada;
    const ArvoreBuscaTabuleroGrafoNodo* pai;
    std::vector<const ArvoreBuscaTabuleroGrafoNodo*> filhos;
    
    friend auto operator<(const ArvoreBuscaTabuleroGrafoNodo& a, const ArvoreBuscaTabuleroGrafoNodo& b) -> bool
    {
        return a.heuristica < b.heuristica;
    }
};

// Solucionador::Solucionador()
// {
// }


// TODO: adicionar struct para substituir tupla pq precisamos saber o caminho.
// Guarda tabulero, heuristica, canto + cor. 
auto solve(const Tabulero& tabulero) -> std::vector<Acao>
{   
    // const auto pQueueComp = [](const auto &a, const auto &b) {
    //     return std::get<1>(a) > std::get<1>(b);
    // };
    
    // auto pQueue = std::priority_queue<
    //                 ArvoreBuscaTabuleroGrafoNodo,
    //                 std::vector<ArvoreBuscaTabuleroGrafoNodo>,
    //                 decltype(pQueueComp)
    //                 >(pQueueComp);
    
    std::priority_queue<ArvoreBuscaTabuleroGrafoNodo> pQueue;
    
    auto raiz = ArvoreBuscaTabuleroGrafoNodo{tabulero, tabulero.calculateArea(), std::make_tuple(Canto::TopLeft, 0), nullptr, {}};

    for (auto cor = 0; cor < tabulero.getColors(); cor++)
    {
        for (auto canto : {Canto::TopLeft, Canto::TopRight, Canto::BottomLeft, Canto::BottomRight})
        {
            auto tabuleroCopia = tabulero.paint(canto, cor);
            // pQueue.push(std::make_tuple(tabuleroCopia, tabuleroCopia.calculateArea())); 
            pQueue.push({tabuleroCopia, tabuleroCopia.calculateArea(), std::make_tuple(canto, cor), &raiz, {}});
            pQueue.top().pai->filhos.push_back(&pQueue.top()); 
        }
    }

    while (true)
    {
        auto nodoAtual = pQueue.top();
        auto tabuleroAtual = pQueue.top().tabulero;
        auto scoreAtual = pQueue.top().heuristica;
        // pQueue.pop();

        if (tabuleroAtual.isSolved())
        {
            std::cout << "Solucion encontrada con score " << scoreAtual << std::endl;
            return {};
        }

        for (auto cor = 0; cor < tabuleroAtual.getColors(); cor++)
        {
            for (auto canto : {Canto::TopLeft, Canto::TopRight, Canto::BottomLeft, Canto::BottomRight})
            {
                auto tabuleroCopia = tabulero.paint(canto, cor);
                pQueue.push({tabuleroCopia, tabuleroCopia.calculateArea(), std::make_tuple(canto, cor), &pQueue.top(), {}});
                pQueue.top().pai->filhos.push_back(&pQueue.top());   
            }
        }
    }
}