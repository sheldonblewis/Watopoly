#include "gym.h"
#include <iostream>

Gym::Gym(std::string name, int position, int cost)
    : Ownable{name, position, cost} {}
