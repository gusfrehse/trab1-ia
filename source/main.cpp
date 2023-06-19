#include <iostream>
#include "board.hpp"
#include "solver.hpp"

int main()
{
    Board board = Board::readFromInput();

    auto solution = solve(board);

    std::cout << solution.size() << std::endl;
    
    for (const auto& acao : solution)
    {
        std::cout << ((char) acao.first) << " " << acao.second << " ";
    }

    std::cout << std::endl;

    return 0;
}