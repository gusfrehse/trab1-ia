#pragma once

#include "board.hpp"

#include <deque>

using Action = std::pair<Corner, int>;

auto solve(const Board& board) -> std::deque<Action>;