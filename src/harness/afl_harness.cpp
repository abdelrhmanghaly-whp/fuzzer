#include <iostream>
#include <vector>
// #include <cstdlib>
// #include <cstring>
#include <unistd.h>
#include "algorithms/dijkstra.hpp"
#include "reference/dijkstra_ref.hpp"
#include "harness/input_parser.hpp"
__AFL_FUZZ_INIT();

int main() {
#ifdef __AFL_HAVE_MANUAL_CONTROL
    __AFL_INIT();
#endif

    unsigned char *buf = __AFL_FUZZ_TESTCASE_BUF;
    while (__AFL_LOOP(10000)) {
        int len = __AFL_FUZZ_TESTCASE_LEN;
        int n, source;
        std::vector<std::vector<edge>> graph;
        if (!parse_graph_input(buf, len, n, graph, source)) {
            continue;
        }
        auto result_impl = dijkstra(n, graph, source);
        auto result_ref = dijkstra_ref(n, graph, source);
        if (result_impl.size() != result_ref.size()) {
            std::cerr << "Size mismatch\n"; // wla mmatch heheheheh (sorry)
            abort();
        }
        for (size_t i = 0; i < result_impl.size(); ++i) {
            bool impl_is_inf = (result_impl[i] >= inf / 2);
            bool ref_is_inf = (result_ref[i] >= inf / 2);
            if (impl_is_inf != ref_is_inf) {
                std::cerr << "Reachability mismatch at node " << i << "!\n";
                std::cerr << "Impl: " << result_impl[i] << ", Ref: " << result_ref[i] << "\n";
                abort();
            }
            if (!impl_is_inf && !ref_is_inf && result_impl[i] != result_ref[i]) {
                std::cerr << "Distance mismatch at node " << i << "!\n";
                std::cerr << "Impl: " << result_impl[i] << ", Ref: " << result_ref[i] << "\n";
                abort();
            }
        }
    }
    return 0;
}