#include "residence.h"
#include "player.h"
#include <iostream>

Residence::Residence(std::string name, int position, int cost)
    : Ownable{name, position, cost} {}

int Residence::calculateFees() {
    if (!owner) {
        return 0; // if no owner, no tuition
    } else if (owner->getResidencesOwned().size() == 1) {
        return 25;
    } else if (owner->getResidencesOwned().size() == 2) {
        return 50;
    } else if (owner->getResidencesOwned().size() == 3) {
        return 100;
    } else {
        return 200;
    }
} // TODO: implemenmt


