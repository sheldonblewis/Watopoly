#ifndef SQUARE_H
#define SQUARE_H

#include <string>

class Square {
    int id;
    std::string name;

public:
    Square(int id, std::string name);
    std::string getName() const;
};

#endif
