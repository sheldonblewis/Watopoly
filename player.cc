#include "player.h"
#include "board.h"
#include <iostream>
#include <random>

Player::Player(std::string name, char symbol) : name{name}, symbol{symbol} {}

int Player::getPosition() const {
    return position;
}

std::string Player::getName() const {
    return name;
}

int Player::getBalance() const{
    return balance;
}

void Player::roll(Board& board) {
    int die1 = rand() % 6 + 1;
    int die2 = rand() % 6 + 1;
    int move = die1 + die2;
    std::cout << name << " rolled " << die1 << " + " << die2 << " = " << move << std::endl;

    position = (position + move) % board.numSquares();
    std::cout << name << " moved to " << board.getSquare(position)->getName() << std::endl;
}

bool Player::changeBalance(int amount) {
    if (amount < 0) { // amount is negative so we are decreasing balance
        if (-amount > balance) {
            return false; // not enough funds 
        }
    }

    // if amount is positive, or negative but its absolute value isn't 
    // greater than current balance
    // -> change current balance
    balance += amount;
    return true;
}

bool Player::ownsGym(Gym* gym) const {
    if (gymsOwned.empty()) {
        return false;
    }
    
    for (const auto& ownedGym : gymsOwned) {
        if (ownedGym == gym) {
            return true;
        }
    }
    return false;
}

bool Player::ownsResidence(Residence* residence) const {
    if (residencesOwnded.empty()) {
        return false;
    }
    
    for (const auto& ownedRes : residencesOwnded) {
        if (ownedRes == residence) {
            return true;
        }
    }
    return false;
}

bool Player::ownsAcademicBuilding(Residence* ac) const {
    if (academicBuildingsOwned.empty()) {
        return false;
    }
    
    for (const auto& ownedAC : academicBuildingsOwned) {
        if (ownedAC == ac) {
            return true;
        }
    }
    return false;
}


