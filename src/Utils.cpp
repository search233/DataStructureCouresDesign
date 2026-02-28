#include "../include/Utils.h"
#include <cmath>
#include <sstream>

namespace Utils {

int calDistance(const City& a, const City& b) {
    int dx = a.getX() - b.getX();
    int dy = a.getY() - b.getY();
    return static_cast<int>(std::round(std::sqrt(dx * dx + dy * dy)));
}

std::vector<std::string> split(const std::string& s, char delim) {
    std::vector<std::string> parts;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        parts.push_back(item);
    }
    return parts;
}

bool isInteger(const std::string& s) {
    if (s.empty()) return false;
    size_t start = 0;
    if (s[0] == '+' || s[0] == '-') start = 1;
    for (size_t i = start; i < s.size(); ++i) {
        if (!std::isdigit(static_cast<unsigned char>(s[i])))
            return false;
    }
    return true;
}

} // namespace Utils
