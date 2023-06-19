#include "board.hpp"

#include <iostream>
#include <iomanip>
#include <stack>
#include <tuple>
#include <algorithm>

Board::Board(int lines, int cols, int colors) : lines(lines), cols(cols), colors(colors), board(lines * cols) {}

auto Board::readFromInput() -> Board
{
    int lines, cols, colors;
    std::cin >> lines >> cols >> colors;
    Board board(lines, cols, colors);

    for (int i = 0; i < lines; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            std::cin >> board.board[i * cols + j];
        }
    }

    return board;
}

auto Board::isSolved() const -> bool
{
    const auto firstColor = board[0];
    for (int i = 0; i < lines * cols; i++)
    {
        if (board[i] != firstColor)
        {
            return false;
        }
    }

    return true;
}

auto Board::clone() const -> Board
{
    Board newBoard;
    newBoard.lines = lines;
    newBoard.cols = cols;
    newBoard.colors = colors;
    newBoard.board = board;
    return newBoard;
}

auto Board::calculateAreaAt(int xi, int yi) const -> int {
    std::tuple<int, int> squaresLeft[cols * lines];
    int stackSize = 0;

    squaresLeft[stackSize++] = {xi, yi};

    bool visited[cols * lines];
    for (int i = 0; i < cols * lines; i++)
    {
        visited[i] = false;
    }	
    visited[yi * cols + xi] = true;

    uint8_t blockColor = board[yi * cols + xi];

    int area = 0;

    while (stackSize > 0) {
        const auto [x, y] = squaresLeft[--stackSize];

        if (board[y * cols + x] != blockColor)
            continue;

        area += 1;

        if (x + 1 < cols && !visited[y * cols + (x + 1)])
        {
            squaresLeft[stackSize++] = {x + 1, y};
            visited[y * cols + (x + 1)] = true;
        }

        if (x - 1 >= 0 && !visited[y * cols + (x - 1)])
        {
            squaresLeft[stackSize++] = {x - 1, y};
            visited[y * cols + (x - 1)] = true;
        }

        if (y + 1 < lines && !visited[(y + 1) * cols + x])
        {
            squaresLeft[stackSize++] = {x, y + 1};
            visited[(y + 1) * cols + x] = true;
        }

        if (y - 1 >= 0 && !visited[(y - 1) * cols + x])
        {
            squaresLeft[stackSize++] = {x, y - 1};
            visited[(y - 1) * cols + x] = true;
        }
    }

    return area;
}

auto Board::calculateArea() const -> int
{
    return std::max({
        calculateAreaAt(0, 0),
        calculateAreaAt(cols - 1, 0),
        calculateAreaAt(cols - 1, lines - 1),
        calculateAreaAt(0, lines - 1),        
    });
}

auto Board::calculateAreaLeft() const -> int
{
    return cols * lines - calculateArea();
}

auto Board::heuristicY() const -> int
{
    int count = 0;
    Color lastColor = board[0];
    for (int j = 1; j < cols; j++)
    {
        if (board[(j - 1) * cols + j] != lastColor)
        {
            count += 19;
            lastColor = board[(j - 1) * cols + j];
        }
        if (board[j * cols + j] != lastColor)
        {
            count += 19;
            lastColor = board[j * cols + j];
        }
    }

    return count;
}

auto Board::minimumStepsToSolve() const -> int
{
    bool hasThisColor[colors];
    for (int i = 0; i < colors; i++)
    {
        hasThisColor[i] = false;
    }

    for (int i = 0; i < lines * cols; i++)
    {
        int currentColor = board[i];
        hasThisColor[currentColor - 1] = true;
    }

    return std::count(hasThisColor, hasThisColor + colors, true);
}

auto Board::paintAt(int xi, int yi, Color cor) const -> Board
{
    Board newBoard = clone();
    bool visited[cols * lines];
    for (int i = 0; i < cols * lines; i++)
    {
        visited[i] = false;
    }	
    std::stack<std::tuple<int, int>> squaresLeft;

    squaresLeft.push({xi, yi});
    visited[yi * cols + xi] = true;

    Color initialColor = board[yi * cols + xi];

    while (!squaresLeft.empty()) {
        const auto [x, y] = squaresLeft.top();
        squaresLeft.pop();

        if (newBoard.board[y * cols + x] != initialColor)
            continue;

        newBoard.board[y * cols + x] = cor;

        if (x + 1 < cols && !visited[y * cols + (x + 1)])
        {
            squaresLeft.push({x + 1, y});
            visited[y * cols + (x + 1)] = true;
        }

        if (x - 1 >= 0 && !visited[y * cols + (x - 1)])
        {
            squaresLeft.push({x - 1, y});
            visited[y * cols + (x - 1)] = true;
        }

        if (y + 1 < lines && !visited[(y + 1) * cols + x])
        {
            squaresLeft.push({x, y + 1});
            visited[(y + 1) * cols + x] = true;
        }

        if (y - 1 >= 0 && !visited[(y - 1) * cols + x])
        {
            squaresLeft.push({x, y - 1});
            visited[(y - 1) * cols + x] = true;
        }
    }

    return newBoard;
}

auto Board::paint(Corner canto, Color cor) const -> Board
{
    switch (canto)
    {
    case Corner::TopLeft:
        return paintAt(0, 0, cor);

    case Corner::TopRight:
        return paintAt(cols - 1, 0, cor);

    case Corner::BottomLeft:
        return paintAt(0, lines - 1, cor);
    
    case Corner::BottomRight:
    default:
        return paintAt(cols - 1, lines - 1, cor);
    }
}

auto Board::getColors() const -> int
{
    return colors;
}

auto Board::size() const -> int
{
    return lines * cols;
}

auto operator<<(std::ostream& os, const Board& board) -> std::ostream&
{
    for (int i = 0; i < board.lines; i++)
    {
        for (int j = 0; j < board.cols; j++)
        {
            os << std::setw(2) << board.board[i * board.cols + j] << " ";
        }
        os << std::endl;
    }

    return os;
}