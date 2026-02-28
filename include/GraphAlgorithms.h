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

    // 近似旅行商路径（最近邻 + 2-opt 改进）
    // 返回访问顺序的城市 id 列表；当 returnToStart 为 true 时为回路
    std::vector<int> tspNearestNeighbor(int start, bool returnToStart=false) const;

    // Steiner 近似：使用完全图上的最小生成树作为近似解（不显式添加辅助点）
    std::vector<Edge> steinerApproxMST() const;
};

#endif