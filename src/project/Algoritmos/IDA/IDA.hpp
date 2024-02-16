#pragma once
#include <optional>
#include "../pdb.hpp"

std::optional<int> ida_search(state_t state, PDB pdb);
