#include "../include/Edge.h"
#include <sstream>
#include <vector>

Edge::Edge() : u(0), v(0) {}

Edge::Edge(int u, int v) : u(u), v(v) {}

// getters
int Edge::getU() const { return u; }
int Edge::getV() const { return v; }


// setters
void Edge::setU(int u) { this->u = u; }
void Edge::setV(int v) { this->v = v; }


// 文件序列化
std::string Edge::serialize() const {
    return std::to_string(u) + "|" + std::to_string(v);
}

Edge Edge::deserialize(const std::string& line) {
    std::stringstream ss(line);
    std::string token;
    std::vector<std::string> parts;

    while (getline(ss, token, '|'))
        parts.push_back(token);

    return Edge(
        std::stoi(parts[0]),
        std::stoi(parts[1])
    );
}