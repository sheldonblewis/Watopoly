#include "square.h"

Square::Square(int id, std::string name) : id{id}, name{name} {}

std::string Square::getName() const {
    return name;
}
