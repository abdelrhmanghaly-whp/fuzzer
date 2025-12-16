#include "harness/input_parser.hpp"
#include <cstring>

bool parse_graph_input(const uint8_t* data, size_t size,int& n_out,std::vector<std::vector<edge>>& graph_out,int& source_out) {
    if (size < 5) return false;
    size_t idx = 0;
    int n = static_cast<int>(data[idx]);
    idx++;
    if (n<=0||n>1000) return false;
    uint32_t m;
    if (idx+4>size)return false;
    std::memcpy(&m, data + idx, 4);
    idx+=4;
    if(m>50000)return false;
    graph_out.assign(n, std::vector<edge>());
    for (uint32_t i = 0; i < m; i++) {
        if (idx + 8 > size) break;
        uint16_t u, v;
        int32_t w;
        std::memcpy(&u, data + idx, 2); idx += 2;
        std::memcpy(&v, data + idx, 2); idx += 2;
        std::memcpy(&w, data + idx, 4); idx += 4;
        if (u >= n || v >= n) continue;
        graph_out[u].push_back({static_cast<int>(v), static_cast<int>(w)});
    }
    int source = 0;
    if (idx < size) {
        source = data[idx] % n;
    }
    n_out = n;
    source_out = source;
    return true;
}