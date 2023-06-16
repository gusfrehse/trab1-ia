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
    //std::stack<std::tuple<int, int>> squaresLeft;
    //squaresLeft.push({xi, yi});

    std::tuple<int, int> squaresLeft[cols * lines];
    int stackSize = 0;

    squaresLeft[stackSize++] = {xi, yi};

    bool visited[cols * lines];
    for (int i = 0; i < cols * lines; i++)
    {
        visited[i] = false;
    }	
    visited[yi * cols + xi] = true;

    uint8_t blockColor = tabulero[yi * cols + xi];

    int area = 0;

    while (stackSize > 0) {
        const auto [x, y] = squaresLeft[--stackSize];

        if (tabulero[y * cols + x] != blockColor)
            continue;

        area += 1;

        if (x + 1 < cols && !visited[y * cols + (x + 1)])
        {
            //squaresLeft.push({x + 1, y});
            squaresLeft[stackSize++] = {x + 1, y};
            visited[y * cols + (x + 1)] = true;
        }

        if (x - 1 >= 0 && !visited[y * cols + (x - 1)])
        {
            //squaresLeft.push({x - 1, y});
            squaresLeft[stackSize++] = {x - 1, y};
            visited[y * cols + (x - 1)] = true;
        }

        if (y + 1 < lines && !visited[(y + 1) * cols + x])
        {
            //squaresLeft.push({x, y + 1});
            squaresLeft[stackSize++] = {x, y + 1};
            visited[(y + 1) * cols + x] = true;
        }

        if (y - 1 >= 0 && !visited[(y - 1) * cols + x])
        {
            //squaresLeft.push({x, y - 1});
            squaresLeft[stackSize++] = {x, y - 1};
            visited[(y - 1) * cols + x] = true;
        }
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

auto Tabulero::calculateAreaLeft() const -> int
{
    return cols * lines - calculateArea();
}

auto Tabulero::paintAt(int xi, int yi, Cor cor) const -> Tabulero
{
    Tabulero newTabulero = clone();
    // std::vector<bool> visited(cols * lines, false);
    bool visited[cols * lines];
    for (int i = 0; i < cols * lines; i++)
    {
        visited[i] = false;
    }	
    std::stack<std::tuple<int, int>> squaresLeft;

    squaresLeft.push({xi, yi});
    visited[yi * cols + xi] = true;

    Cor initialColor = tabulero[yi * cols + xi];

    while (!squaresLeft.empty()) {
        const auto [x, y] = squaresLeft.top();
        squaresLeft.pop();

        if (newTabulero.tabulero[y * cols + x] != initialColor)
            continue;

        newTabulero.tabulero[y * cols + x] = cor;

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

    return newTabulero;
}

auto Tabulero::paint(Canto canto, Cor cor) const -> Tabulero
{
    switch (canto)
    {
    case Canto::TopLeft:
        return paintAt(0, 0, cor);

    case Canto::TopRight:
        return paintAt(cols - 1, 0, cor);

    case Canto::BottomLeft:
        return paintAt(0, lines - 1, cor);
    
    case Canto::BottomRight:
    default:
        return paintAt(cols - 1, lines - 1, cor);
    }
}

auto Tabulero::getColors() const -> int
{
    return colors;
}

auto Tabulero::size() const -> int
{
    return lines * cols;
}

auto operator<<(std::ostream& os, const Tabulero& tabulero) -> std::ostream&
{
    for (int i = 0; i < tabulero.lines; i++)
    {
        for (int j = 0; j < tabulero.cols; j++)
        {
            os << tabulero.tabulero[i * tabulero.cols + j] << " ";
        }
        os << std::endl;
    }

    return os;
}