#pragma once
#include <optional>

std::optional<int> BFS(state_t state);
std::optional<int> BFS_Prunning(state_t state);