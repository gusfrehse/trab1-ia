#pragma once

#include "tabulero.hpp"

#include <deque>

using Acao = std::pair<Canto, int>;

auto solve(const Tabulero& tabulero) -> std::deque<Acao>;