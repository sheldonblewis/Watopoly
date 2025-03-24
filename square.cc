#include "square.h"

Square::Square(std::string name, int position) : name{name}, position{position} {}
std::string Square::getName() const { return name; }
