#pragma once

#include "tabulero.hpp"

#include <deque>

using Acao = std::tuple<Canto, int>;

auto solve(const Tabulero& tabulero) -> std::deque<Acao>;