#include "../include/Graph.h"
#include "../include/Utils.h"
#include <algorithm>

using namespace std;

Graph::Graph() {}

void Graph::build(const vector<City>& cityList, const vector<Edge>& edgeList) {

    cities.clear();
    adj.clear();

    for (const auto& c : cityList) {
        cities[c.getId()] = c;
        adj[c.getId()] = {};
    }

    for (const auto& e : edgeList) {
        addEdge(e.getU(), e.getV());
    }
}

// city
bool Graph::addCity(const City& city) {
    int id = city.getId();
    if (cities.count(id)) return false;

    cities[id] = city;
    adj[id] = {};
    return true;
}

bool Graph::removeCity(int id) {
    if (!cities.count(id)) return false;

    cities.erase(id);
    adj.erase(id);

    for (auto& [u, vec] : adj) {
        vec.erase(remove_if(vec.begin(), vec.end(),
            [id](auto& p){ 
                return p.first == id; }),
            vec.end());
    }
    return true;
}

// edge
bool Graph::addEdge(int u, int v) {
    if (!hasCity(u) || !hasCity(v))
        return false;

    int w = Utils::calDistance(cities[u], cities[v]);

    adj[u].push_back({v, w});
    adj[v].push_back({u, w});

    return true;
}

bool Graph::removeEdge(int u, int v) {
    if (!adj.count(u) || !adj.count(v))
        return false;

    auto eraseEdge = [&](int a, int b) {
        auto& vec = adj[a];
        vec.erase(remove_if(vec.begin(), vec.end(),
            [b](auto& p){ return p.first == b; }),
            vec.end());
    };

    eraseEdge(u,v);
    eraseEdge(v,u);
    return true;
}

bool Graph::hasCity(int id) const {
    return cities.count(id);
}

optional<City> Graph::getCity(int id) const {
    if (!cities.count(id)) return nullopt;
    return cities.at(id);
}

vector<int> Graph::getAllCityIds() const {
    vector<int> ids;
    for (auto& [id,_] : cities)
        ids.push_back(id);
    return ids;
}

const vector<pair<int,int>>& Graph::getNeighbors(int id) const {
    return adj.at(id);
}