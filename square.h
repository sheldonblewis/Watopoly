#ifndef SQUARE_H
#define SQUARE_H

#include <string>

class Square {
    int position;
    std::string name;


public:
    Square(int id, std::string name);
    std::string getName() const;
    std::string getId() const;
    int getPosition() const;
};

#endif
