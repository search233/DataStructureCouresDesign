#ifndef GRAPH_H
#define GRAPH_H

#include "City.h"
#include "Edge.h"
#include <unordered_map>
#include <vector>
#include <optional>

class Graph {
private:

    // id -> City
    std::unordered_map<int, City> cities;

    // id -> [(neighbor, weight)]
    std::unordered_map<int,
        std::vector<std::pair<int,int>>> adj;

    int calDistance(const City& a,
                        const City& b) const;

public:
    Graph();

    // build
    void build(const std::vector<City>& cityList,
               const std::vector<Edge>& edgeList);

    // city
    bool addCity(const City& city);
    bool removeCity(int id);

    // edge
    bool addEdge(int u, int v);
    bool removeEdge(int u, int v);

    // query
    std::optional<City> getCity(int id) const;
    std::vector<int> getAllCityIds() const;

    const std::vector<std::pair<int,int>>& getNeighbors(int id) const;

    bool hasCity(int id) const;
};

#endif