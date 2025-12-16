#include "harness/input_parser.hpp"
#include <cstring>

bool parse_graph_input(const uint8_t* data, int size, int& n_out, std::vector<std::vector<edge>>& graph_out, int& source_out) {
    if(size<9)return false;
    int idx=0;
    int n;
    std::memcpy(&n, data + idx, 4);
    idx+=4;
    if (n<=0||n>1000)return false;
    int m;
    std::memcpy(&m, data + idx, 4);
    idx+=4;
    if (m>50000)return false;

    graph_out.assign(n, std::vector<edge>());
    
    for (int i = 0; i < m; i++) {
        if(idx+12>size) break;
        int u,v,w;
        std::memcpy(&u, data + idx, 4); idx += 4;
        std::memcpy(&v, data + idx, 4); idx += 4;
        std::memcpy(&w, data + idx, 4); idx += 4;
        if (u>= n||v>= n||u<0||v<0) continue;
        graph_out[u].push_back({v, w});
    }
    
    int src = 0;
    if (idx+4<= size) {
        int raw_source;
        std::memcpy(&raw_source, data + idx, 4);
        src=raw_source%n;
    }
    n_out=n;
    source_out=src;
    return true;
}