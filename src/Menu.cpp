#include "../include/Menu.h"
#include "../include/Utils.h"
#include <iostream>
#include <algorithm>

using namespace std;

Menu::Menu() {}

void Menu::showMain() {
    cout << "\n=== 通信网络设计系统 ===\n";
    cout << "1. 加载数据\n";
    cout << "2. 保存数据\n";
    cout << "3. 列出城市\n";
    cout << "4. 列出线路\n";
    cout << "5. 添加城市\n";
    cout << "6. 删除城市\n";
    cout << "7. 添加线路\n";
    cout << "8. 删除线路\n";
    cout << "9. 判断连通性\n";
    cout << "10. 单源最短路径 (Dijkstra)\n";
    cout << "11. 最小生成树 (Kruskal 近似)\n";
    cout << "0. 退出\n";
    cout << "选择: ";
}

void Menu::listCities() {
    cout << "\n--- 城市列表 ---\n";
    for (auto &c : fm.getCities()) {
        cout << c.getId() << " " << c.getName()
             << " (" << c.getX() << "," << c.getY() << ") "
             << c.getDescription() << "\n";
    }
}

void Menu::listEdges() {
    cout << "\n--- 线路列表 ---\n";
    for (auto &e : fm.getEdges()) {
        cout << e.getU() << " <-> " << e.getV() << "\n";
    }
}

void Menu::run() {
    bool running = true;
    while (running) {
        showMain();
        int choice;
        if (!(cin >> choice)) break;

        switch (choice) {
            case 1: {
                fm.load();
                graph.build(fm.getCities(), fm.getEdges());
                cout << "已加载数据。\n";
                break;
            }
            case 2: {
                fm.save();
                cout << "已保存数据。\n";
                break;
            }
            case 3: {
                listCities();
                break;
            }
            case 4: {
                listEdges();
                break;
            }
            case 5: {
                int id, x, y; string name, desc;
                cout << "输入 id name x y description（以空格分隔，描述无空格）：\n";
                cin >> id >> name >> x >> y >> desc;
                City c(id, name, x, y, desc);
                fm.addCity(c);
                graph.addCity(c);
                cout << "已添加城市。\n";
                break;
            }
            case 6: {
                int id; cout << "输入要删除的城市 id: "; cin >> id;
                fm.removeCity(id);
                graph.removeCity(id);
                cout << "已删除（如果存在）。\n";
                break;
            }
            case 7: {
                int u,v; cout << "输入起点 u 和 终点 v: "; cin >> u >> v;
                fm.addEdge(Edge(u,v));
                graph.addEdge(u,v);
                cout << "已添加线路（若城市存在且未重复）。\n";
                break;
            }
            case 8: {
                int u,v; cout << "输入要删除的线路 u v: "; cin >> u >> v;
                fm.removeEdge(u,v);
                graph.removeEdge(u,v);
                cout << "已删除线路（如存在）。\n";
                break;
            }
            case 9: {
                GraphAlgorithms ga(graph);
                bool ok = ga.isConnected();
                cout << (ok ? "图是连通的。\n" : "图不是连通的。\n");
                break;
            }
            case 10: {
                int s; cout << "输入起点 id: "; cin >> s;
                GraphAlgorithms ga(graph);
                auto dist = ga.dijkstra(s);
                vector<pair<int,int>> items;
                for (auto &p : dist) items.emplace_back(p.first, p.second);
                sort(items.begin(), items.end(), [](auto &a, auto &b){ return a.second < b.second; });
                cout << "节点 距离\n";
                for (auto &it : items) {
                    cout << it.first << " " << it.second << "\n";
                }
                break;
            }
            case 11: {
                GraphAlgorithms ga(graph);
                auto edges = ga.kruskal();
                cout << "Kruskal 结果（MST 边列表）:\n";
                for (auto &e : edges) cout << e.getU() << " - " << e.getV() << "\n";
                break;
            }
            case 0: {
                running = false; break;
            }
            default:
                cout << "无效选择。\n";
        }
    }
}
