#include "residence.h"
#include <iostream>

Residence::Residence(std::string name, int position, int cost)
    : Ownable{name, position, cost} {}
