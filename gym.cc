#include "gym.h"
#include "player.h"
#include <iostream>
#include <random>

Gym::Gym(std::string name, int position, int cost) : Ownable{name, position, cost} {}

int Gym::calculateFees() {
    int die1 = rand() % 6 + 1;
    int die2 = rand() % 6 + 1;
    int sum = die1 + die2;

    std::cout << "Rolled a " << die1 << " + " << die2 << " = " << sum << "!" << std::endl;

    if (owner->getGymsOwned().size() == 1) {
        return 4 * sum;
    } else {
        return 10 * sum;
    }
}


bool Gym::isOwnable() const {
    return true;
}


bool Gym::isGym() const {
    return true;
}
