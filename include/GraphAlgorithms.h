#ifndef GRAPH_ALGORITHMS_H
#define GRAPH_ALGORITHMS_H

#include "Graph.h"
#include "Utils.h"
#include <vector>
#include <unordered_map>

class GraphAlgorithms {
private:
    const Graph& graph;

public:
    GraphAlgorithms(const Graph& g);

    bool isConnected() const;

    std::unordered_map<int,int>
    dijkstra(int start) const;

    std::vector<Edge>
    kruskal() const;
};

#endif