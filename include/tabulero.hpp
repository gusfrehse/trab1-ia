#include <cstdint>
#include <vector>

using Cor = uint8_t;

enum Canto { TopLeft = 'a', TopRight = 'b', BottomLeft = 'd', BottomRight = 'c' };

class Tabulero {
private:
    int lines, cols, colors;
    std::vector<Cor> tabulero;

    auto calculateAreaAt(int x, int y) const -> int;

public:
    Tabulero() = default;
    Tabulero(int lines, int cols, int colors);
    static auto readFromInput() -> Tabulero;
    auto clone() const -> Tabulero;
    auto isSolved() const -> bool;
    auto calculateArea() const -> int;
    auto paint(Canto canto, Cor cor) const -> Tabulero;
    auto getColors() const -> int;
};