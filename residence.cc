#include "residence.h"
#include "player.h"
#include <iostream>

Residence::Residence(std::string name, int position, int cost, std::string id)
    : Ownable{name, position, cost, id} {}

int Residence::calculateFees() {
    if (!owner) {
        return 0; // if no owner, no tuition
    } else if (owner->residencesOwned.size() == 1) {
        return 25;
    } else if (owner->residencesOwned.size() == 2) {
        return 50;
    } else if (owner->residencesOwned.size() == 3) {
        return 100;
    } else {
        return 200;
    }
} // TODO: implemenmt


