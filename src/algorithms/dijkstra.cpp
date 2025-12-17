#include "algorithms/dijkstra.hpp"
#include <queue>
#include <algorithm>
vll dijkstra(int n, std::vector<std::vector<edge>>&adj, int src) {
    vll dist(n,inf);
    dist[src]=0;
    std::priority_queue<pli,std::vector<pli>,std::greater<pli>>pq;
    pq.push({0,src});
    while (!pq.empty()) {
        auto[d,u]=pq.top();
        pq.pop();
        if (d!=dist[u])continue;
        for (auto& e:adj[u]) {
            if (e.weight< -limit ||e.weight>limit)continue;
            ll ndist=d+e.weight;
            if (ndist<dist[e.to]) {
                dist[e.to]=ndist;
                pq.push({ndist,e.to});
            }
        }
    }
    return dist;
}