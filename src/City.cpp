#include "../include/City.h"
#include <sstream>
#include <vector>

City::City() : id(0), x(0), y(0) {}

City::City(int id, const std::string& name,
           int x, int y,
           const std::string& description)
    : id(id), name(name), 
      x(x), y(y), 
      description(description) {}


// getters
int City::getId() const { return id; }
std::string City::getName() const { return name; }
int City::getX() const { return x; }
int City::getY() const { return y; }
std::string City::getDescription() const { return description; }

// setters
void City::setName(const std::string& n) { name = n; }
void City::setPosition(int nx, int ny) { x = nx; y = ny; }
void City::setDescription(const std::string& d) { description = d; }

// 文件序列化
std::string City::serialize() const {
    return std::to_string(id) + "|" + name + "|" +
           std::to_string(x) + "|" +
           std::to_string(y) + "|" + description;
}

City City::deserialize(const std::string& line) {
    std::stringstream ss(line);
    std::string token;
    std::vector<std::string> parts;

    while (getline(ss, token, '|'))
        parts.push_back(token);

    return City(
        std::stoi(parts[0]),
        parts[1],
        std::stoi(parts[2]),
        std::stoi(parts[3]),
        parts[4]
    );
}