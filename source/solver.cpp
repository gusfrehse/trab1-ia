#include "solver.hpp"
#include "board.hpp"
#include <tuple>
#include <queue>
#include <deque>
#include <iostream>

struct SearchTreeNode
{
    Board board;
    int heuristic;
    int steps;
    Action usedAction;
    const SearchTreeNode* parent;
};


static auto collectActions(const SearchTreeNode* node) -> std::deque<Action>
{
    std::deque<Action> out;
    const SearchTreeNode* current = node;

    do
    {
        out.push_front(current->usedAction);
        current = current->parent;
    }
    while (current);

    out.pop_front();

    return out;
}


auto solve(const Board& board) -> std::deque<Action>
{   
    const auto pQueueComp = [](const auto &a, const auto &b) {
        return a->heuristic + a->steps > b->heuristic + b->steps;
    };
    
    auto pQueue = std::priority_queue<
                   SearchTreeNode*,
                   std::vector<SearchTreeNode*>,
                   decltype(pQueueComp)
                   >(pQueueComp);
    
    auto root = new SearchTreeNode{board, board.size(), 0, std::make_pair(Corner::Null, -1), nullptr};
    pQueue.push(root);

    while (true)
    {
        const auto currentNode = pQueue.top();
        const auto& currentBoard = pQueue.top()->board;
    
        pQueue.pop();

        if (currentBoard.isSolved())
        {
            return collectActions(currentNode);
        }

        for (auto color = 1; color <= currentBoard.getColors(); color++)
        {
            for (auto corner : {Corner::TopLeft, Corner::TopRight, Corner::BottomLeft, Corner::BottomRight})
            {
                auto boardCopy = currentBoard.paint(corner, color);
                auto nodo = new SearchTreeNode{boardCopy, boardCopy.heuristicY() + boardCopy.calculateAreaLeft() + boardCopy.minimumStepsToSolve(), currentNode->steps + 1, std::make_pair(corner, color), currentNode};

                pQueue.push(nodo);
            }
        }
    }
}