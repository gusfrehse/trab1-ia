#pragma once

#include "tabulero.hpp"

using Acao = std::tuple<Canto, int>;

auto solve(const Tabulero& tabulero) -> std::vector<Acao>;