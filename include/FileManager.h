#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "City.h"
#include "Edge.h"
#include <vector>
#include <optional>

class FileManager {
private:
    std::vector<City> cities;
    std::vector<Edge> edges;

public:
    // 文件操作
    void load();
    void save();

    // City 
    void addCity(const City& city);
    bool removeCity(int id);
    std::optional<City*> findCity(int id);
    std::vector<City>& getCities();

    // Edge
    void addEdge(const Edge& edge);
    bool removeEdge(int u, int v);
    std::vector<Edge>& getEdges();
};

#endif