#ifndef UTILS_H
#define UTILS_H

#include "City.h"
#include <string>
#include <vector>

namespace Utils {
    // 计算两个城市之间的欧几里得距离（四舍五入到整数）
    int calDistance(const City& a, const City& b);

    // 字符串分割
    std::vector<std::string> split(const std::string& s, char delim);

    // 判断字符串是否为整数
    bool isInteger(const std::string& s);
}

#endif // UTILS_H
