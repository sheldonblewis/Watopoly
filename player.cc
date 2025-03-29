#include "academicbuilding.h"
#include "board.h"
#include "gym.h"
#include "player.h"
#include "residence.h"
#include "square.h"
#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <vector>

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

int Player::roll(Board& board) {
    int die1 = rand() % 6 + 1;
    int die2 = rand() % 6 + 1;
    int move = die1 + die2;
    std::cout << name << " rolled " << die1 << " + " << die2 << " = " << move << std::endl;

    position = (position + move) % 40;

    std::cout << name << " moved to " << board.getSquare(position)->getName() << std::endl;

    return (position - move) % 40;
}


char Player::getSymbol() const {
    return symbol;
}

void Player::displayAssets() const {
    std::cout << "Player: " << name << " ($" << balance << ")" << std::endl;
    for (const auto& ac : academicBuildingsOwned) {
        std::cout << "  Academic Building: " << ac->getName() << " ";
        if (ac->isMortgaged()) {
            std::cout << "(mortgaged)";
        }
        for (int i = 0; i < ac->numImprovements(); ++i) {
            std::cout << "X";
        }
        std::cout << std::endl;
    }
    for (const auto& res : residencesOwned) {
        std::cout << "  Residence: " << res->getName();
        if (res->isMortgaged()) {
            std::cout << " (mortgaged)";
        }
        std::cout << std::endl;
    }
    for (const auto& gym : gymsOwned) {
        std::cout << "  Gym: " << gym->getName();
        if (gym->isMortgaged()) {
            std::cout << " (mortgaged)";
        }
        std::cout << std::endl;
    }
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
    if (residencesOwned.empty()) {
        return false;
    }
    
    for (const auto& ownedRes : residencesOwned) {
        if (ownedRes->getName() == residence->getName()) {
            return true;
        }
    }
    return false;
}

bool Player::ownsAcademicBuilding(AcademicBuilding* ac) const {
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

bool Player::ownsAll(const std::string& monopolyBlock) const {
    if (academicBuildingsOwned.empty()) {
        return false;
    }
    
    int counter = 0;
    for (const auto& ownedAC : academicBuildingsOwned) {
        if (ownedAC->getMonopolyBlock() == monopolyBlock) {
            counter++;
        }
    }

    // arts1 and math are the only two blocks with only 2 
    // academic buildings each
    if (monopolyBlock == "Arts1" || monopolyBlock == "Math") {
        return counter == 2;
    } else {
        return counter == 3;
    }
}

std::vector<AcademicBuilding*> Player::getACOwned() const {
    return academicBuildingsOwned;
}

std::vector<Gym*> Player::getGymsOwned() const {
    return gymsOwned;
}

std::vector<Residence*>& Player::getResidencesOwned() {
    return residencesOwned;
}

void Player::addAcademicBuilding(AcademicBuilding* ac) {
    auto it = std::lower_bound(
        academicBuildingsOwned.begin(),
        academicBuildingsOwned.end(),
        ac,
        [](AcademicBuilding* a, AcademicBuilding* b) {
            return a->getPosition() < b->getPosition();
        }
    );
    academicBuildingsOwned.insert(it, ac);
}

void Player::addGym(Gym* gym) {
    auto it = std::lower_bound(
        gymsOwned.begin(),
        gymsOwned.end(),
        gym,
        [](Gym* a, Gym* b) {
            return a->getPosition() < b->getPosition();
        });
    gymsOwned.insert(it, gym);
}

void Player::addResidence(Residence* residence) {
    auto it = std::lower_bound(
        residencesOwned.begin(),
        residencesOwned.end(),
        residence,
        [](Residence* a, Residence* b) {
            return a->getPosition() < b->getPosition();
        });
    residencesOwned.insert(it, residence);
}
