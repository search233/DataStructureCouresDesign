#ifndef CITY_H
#define CITY_H

#include <string>

class City {
private:
    int id;
    std::string name;
    int x;
    int y;
    std::string description;

public:
    City();
    City(int id, const std::string& name,
         int x, int y,
         const std::string& description);

    // getters
    int getId() const;
    std::string getName() const;
    int getX() const;
    int getY() const;
    std::string getDescription() const;

    // setters
    void setName(const std::string& name);
    void setPosition(int x, int y);
    void setDescription(const std::string& desc);

    // 文件序列化
    std::string serialize() const;
    static City deserialize(const std::string& line);
};

#endif