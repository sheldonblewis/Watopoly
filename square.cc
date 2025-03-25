#include "square.h"

Square::Square(int position, std::string name) : position{position}, name{name} {}

std::string Square::getName() const {
    return name;
}

std::string Square::getId() const {
    return id;
}

int Square::getPosition() const {
    return position;
}
