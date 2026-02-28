#include "../include/FileManager.h"
#include <fstream>

using namespace std;

static const string CITY_FILE = "data/cities.txt";
static const string EDGE_FILE = "data/edges.txt";

void FileManager::load() {
    cities.clear();
    edges.clear();

    ifstream fc(CITY_FILE);
    string line;

    while (getline(fc, line)) {
        if (!line.empty()) {
            City c = City::deserialize(line);
            addCity(c);
        }
    }

    fc.close();

    ifstream fe(EDGE_FILE);
    while (getline(fe, line)) {
        if (!line.empty()) {
            Edge e = Edge::deserialize(line);
            addEdge(e);
        }
    }

    fe.close();
}

void FileManager::save() {
    ofstream fc(CITY_FILE);

    for (auto& c : cities)
        fc << c.serialize() << "\n";

    fc.close();

    ofstream fe(EDGE_FILE);

    for (auto& e : edges)
        fe << e.serialize() << "\n";

    fe.close();
}

// City
void FileManager::addCity(const City& city) {
    for (auto& c : cities) {
        if (c.getId() == city.getId()) {
            return;
        }
    }
    cities.push_back(city);
}

bool FileManager::removeCity(int id) {
    bool removed = false;
    for (auto it = cities.begin(); it != cities.end();) {
        if (it->getId() == id) {
            it = cities.erase(it);
            removed = true;
        } else {
            ++it;
        }
    }
    return removed;
}

optional<City*> FileManager::findCity(int id) {
    for (auto& c : cities)
        if (c.getId() == id)
            return &c;
    return nullopt;
}

vector<City>& FileManager::getCities() {
    return cities;
}

// Edge
void FileManager::addEdge(const Edge& edge) {
    for (auto& e : edges) {
        if ((e.getU() == edge.getU() && e.getV() == edge.getV()) ||
            (e.getU() == edge.getV() && e.getV() == edge.getU())) {
            return;
        }
    }
    edges.push_back(edge);
}

bool FileManager::removeEdge(int u, int v) {
    bool removed = false;
    for (auto it = edges.begin(); it != edges.end();) {
        if ((it->getU() == u && it->getV() == v) ||
            (it->getU() == v && it->getV() == u)) {
            it = edges.erase(it);
            removed = true;
        } else {
            ++it;
        }
    }
    return removed;
}

vector<Edge>& FileManager::getEdges() {
    return edges;
}