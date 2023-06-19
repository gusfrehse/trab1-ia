#pragma once

#include <cstdint>
#include <vector>
#include <iostream>

using Color = int;

enum Corner { TopLeft = 'a', TopRight = 'b', BottomLeft = 'd', BottomRight = 'c', Null = '?' };

class Board {
private:
    int lines, cols, colors;
    std::vector<Color> board;

    auto calculateAreaAt(int x, int y) const -> int;

public:
    Board() = default;
    Board(int lines, int cols, int colors);
    static auto readFromInput() -> Board;
    auto clone() const -> Board;
    auto isSolved() const -> bool;
    auto calculateArea() const -> int;
    auto calculateAreaLeft() const -> int;
    auto heuristicY() const -> int;
    auto minimumStepsToSolve() const -> int;
    auto paintAt(int x, int y, Color cor) const -> Board;
    auto paint(Corner canto, Color cor) const -> Board;
    auto getColors() const -> int;
    auto size() const -> int;

    friend auto operator<<(std::ostream& os, const Board& beard) -> std::ostream&;
};