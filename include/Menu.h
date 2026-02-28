#ifndef MENU_H
#define MENU_H

#include "FileManager.h"
#include "Graph.h"
#include "GraphAlgorithms.h"
#include <string>

class Menu {
private:
    FileManager fm;
    Graph graph;

    void showMain();
    void listCities();
    void listEdges();

public:
    Menu();
    void run();
};

#endif
