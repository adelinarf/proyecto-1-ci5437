#pragma once
#include <optional>

std::optional<int> BFS(state_t root);
std::optional<int> BFS_Prunning(state_t root);