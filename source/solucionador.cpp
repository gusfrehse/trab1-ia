#include "solucionador.hpp"
#include "tabulero.hpp"
#include <tuple>
#include <queue>
#include <deque>
#include <iostream>
#include <unistd.h>


struct ArvoreBuscaTabuleroGrafoNodo
{
    Tabulero tabulero;
    int heuristica;
    int passos;
    Acao acaoUsada;
    const ArvoreBuscaTabuleroGrafoNodo* pai;
    
    friend auto operator<(const ArvoreBuscaTabuleroGrafoNodo& a, const ArvoreBuscaTabuleroGrafoNodo& b) -> bool
    {
        return a.heuristica + a.passos > b.heuristica + b.passos;
    }
};

// Solucionador::Solucionador()
// {
// }


static auto collectActiones(const ArvoreBuscaTabuleroGrafoNodo* no) -> std::deque<Acao>
{
    std::deque<Acao> out;
    const ArvoreBuscaTabuleroGrafoNodo* atual = no;

    do
    {
        // std::cerr << "laksdfj: " << std::get<0>(atual->acaoUsada) << " " << std::get<1>(atual->acaoUsada) << std::endl;
        out.push_front(atual->acaoUsada);
        atual = atual->pai;
        // sleep(1);
    }
    while (atual);

    out.pop_front();

    return out;
}

// TODO: adicionar struct para substituir tupla pq precisamos saber o caminho.
// Guarda tabulero, heuristica, canto + cor. 
auto solve(const Tabulero& tabulero) -> std::deque<Acao>
{   
    const auto pQueueComp = [](const auto &a, const auto &b) {
        return a->heuristica + a->passos > b->heuristica + b->passos;
    };
    
    auto pQueue = std::priority_queue<
                   ArvoreBuscaTabuleroGrafoNodo*,
                   std::vector<ArvoreBuscaTabuleroGrafoNodo*>,
                   decltype(pQueueComp)
                   >(pQueueComp);
    
    // std::priority_queue<ArvoreBuscaTabuleroGrafoNodo*, pQueueComp> pQueue;
    
    auto raiz = new ArvoreBuscaTabuleroGrafoNodo{tabulero, tabulero.size(), 0, std::make_tuple(Canto::Null, -1), nullptr};
    const ArvoreBuscaTabuleroGrafoNodo *prev = raiz;
    pQueue.push(raiz);

    while (true)
    {
        const auto nodoAtual = pQueue.top();
        const auto& tabuleroAtual = pQueue.top()->tabulero;
        const auto& scoreAtual = pQueue.top()->heuristica;
        const auto& passosAtual = pQueue.top()->passos;
        // std::cerr << "======================== " << (char) std::get<0>(nodoAtual->acaoUsada) << " " << std::get<1>(nodoAtual->acaoUsada) << " ========================" << std::endl;
        // std::cerr << "tam queue: " << pQueue.size() << " nodoAtual = " << (char) std::get<0>(nodoAtual->acaoUsada) << " " << std::get<1>(nodoAtual->acaoUsada) << " heuristica = " << scoreAtual << " | passos = " << passosAtual << std::endl;
        //std::cerr << tabuleroAtual << std::endl;;
        // usleep(50000);
        pQueue.pop();

        if (tabuleroAtual.isSolved())
        {
            // std::cout << "Solucion encontrada con score " << scoreAtual << std::endl;
            return collectActiones(nodoAtual);
        }

        // std::cerr << "====> Filhos" << std::endl;
        for (auto cor = 1; cor <= tabuleroAtual.getColors(); cor++)
        {
            for (auto canto : {Canto::TopLeft, Canto::TopRight, Canto::BottomLeft, Canto::BottomRight})
            {
                auto tabuleroCopia = tabuleroAtual.paint(canto, cor);
                auto nodo = new ArvoreBuscaTabuleroGrafoNodo{tabuleroCopia, tabuleroCopia.calculateAreaLeft(), nodoAtual->passos + 1, std::make_tuple(canto, cor), nodoAtual};
                pQueue.push(nodo);
                // std::cerr << "pai canto e cor: " << std::get<0>(nodo->pai->acaoUsada) << " " << std::get<1>(nodo->pai->acaoUsada) << std::endl;
                // std::cerr << "filho canto = " << (char) canto << " | cor = " << cor << std::endl;
                // std::cerr << "heuristica = " << nodo->heuristica << std::endl;
                // std::cerr << "passos = " << nodo->passos << std::endl;
                // std::cerr << tabuleroCopia << std::endl;
                getchar();
            }
        }

        prev = nodoAtual;
    }
}