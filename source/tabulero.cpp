#include "tabulero.hpp"

#include <iostream>
#include <stack>
#include <tuple>
#include <algorithm>

Tabulero::Tabulero(int lines, int cols, int colors) : lines(lines), cols(cols), colors(colors), tabulero(lines * cols) 
{
}

auto Tabulero::readFromInput() -> Tabulero
{
    int lines, cols, colors;
    std::cin >> lines >> cols >> colors;
    Tabulero tabulero(lines, cols, colors);

    for (int i = 0; i < lines; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            std::cin >> tabulero.tabulero[i * cols + j];
        }
    }

    return tabulero;
}

auto Tabulero::isSolved() const -> bool
{
    const auto firstColor = tabulero[0];
    for (int i = 0; i < lines * cols; i++)
    {
        if (tabulero[i] != firstColor)
        {
            return false;
        }
    }

    return true;
}

auto Tabulero::clone() const -> Tabulero
{
    Tabulero newTabulero;
    newTabulero.lines = lines;
    newTabulero.cols = cols;
    newTabulero.colors = colors;
    newTabulero.tabulero = tabulero;
    return newTabulero;
}

auto Tabulero::calculateAreaAt(int xi, int yi) const -> int {
    std::vector<bool> visited(cols * lines, false);
    std::stack<std::tuple<int, int>> squaresLeft;
    squaresLeft.push({xi, yi});

    uint8_t blockColor = tabulero[xi * cols + yi];

    int area = 0;

    while (!squaresLeft.empty()) {
        const auto [x, y] = squaresLeft.top();
        squaresLeft.pop();
        visited[x * cols + y] = true;

        if (tabulero[x * cols + y] != blockColor)
            continue;

        area += 1;

        if (x + 1 < cols && visited[(x + 1) * cols + y])
            squaresLeft.push({x + 1, y});

        if (x - 1 >= 0 && visited[(x - 1) * cols + y])
            squaresLeft.push({x - 1, y});

        if (y + 1 < lines && visited[x * cols + y + 1])
            squaresLeft.push({x, y + 1});

        if (y - 1 >= 0 && visited[x * cols + y - 1])
            squaresLeft.push({x, y - 1});
    }

    return area;
}

auto Tabulero::calculateArea() const -> int
{
    return std::max({
        calculateAreaAt(0, 0),
        calculateAreaAt(cols - 1, 0),
        calculateAreaAt(cols - 1, lines - 1),
        calculateAreaAt(0, lines - 1),        
    });
}

auto Tabulero::paint(Canto canto, Cor cor) const -> Tabulero
{
    Tabulero newTabulero = clone();

    switch (canto)
    {
    case Canto::TopLeft:
        newTabulero.tabulero[0] = cor;
        break;

    case Canto::TopRight:
        newTabulero.tabulero[cols - 1] = cor;
        break;

    case Canto::BottomLeft:
        newTabulero.tabulero[lines * cols - cols] = cor;
        break;
        
    case Canto::BottomRight:
        newTabulero.tabulero[lines * cols - 1] = cor;
        break;
    }

    return newTabulero;
}

auto Tabulero::getColors() const -> int
{
    return colors;
}