#ifndef SQUARE_H
#define SQUARE_H

#include <string>

class Square {
protected:
    std::string name;
    int position;

public:
    Square(std::string name, int position);
    virtual ~Square() = default;
    std::string getName() const;
    virtual void landOn() = 0;
};

#endif
