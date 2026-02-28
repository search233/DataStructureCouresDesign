#ifndef EDGE_H
#define EDGE_H

#include <string>

class Edge {
private:
    int u;
    int v;

public:
    Edge();
    Edge(int u, int v);

    // getters
    int getU() const;
    int getV() const;

    // setters
    void setU(int u);
    void setV(int v);

    // 文件序列化
    std::string serialize() const;
    static Edge deserialize(const std::string& line);
};

#endif