#include "gym.h"
#include "player.h"
#include <iostream>
#include <random>

Gym::Gym(std::string name, int position, int cost, std::string id)
    : Ownable{name, position, cost, id} {}

int Gym::calculateFees() {
    if (!owner) {
        return 0; // if no owner, no fee
    }

    int die1 = rand() % 6 + 1;
    int die2 = rand() % 6 + 1;
    int sum = die1 + die2;

    if (owner->gymsOwned.size() == 1) {
        return 4 * sum;
    } else {
        return 10 * sum;
    }


}


