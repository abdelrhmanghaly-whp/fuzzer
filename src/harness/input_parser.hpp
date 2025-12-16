#pragma once
#include <cstdint>
#include <vector>
#include "types/graph_types.hpp"
bool parse_graph_input(const uint8_t* data, int size, int& n_out, std::vector<std::vector<edge>>& graph_out, int& source_out);