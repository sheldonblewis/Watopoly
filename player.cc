#include "board.h"
#include "player.h"
#include "square.h"
#include "academicbuilding.h"
#include "residence.h"
#include "gym.h"
#include "ownable.h"
#include <string>
#include <iostream>
#include <vector>
#include <random>
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

std::vector<AcademicBuilding*> Player::getACOwned() const {
    return academicBuildingsOwned;
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
    std::cout << "Player: " << name << " ($" << balance << "), Position: " << position << std::endl;
    // Add more asset info here later (like owned properties)
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

std::vector<Gym*> Player::getGymsOwned() const {
    return gymsOwned;
}

std::vector<Residence*>& Player::getResidencesOwned() {
    return residencesOwned;
}

void Player::addAcademicBuilding(AcademicBuilding* ac) {
    academicBuildingsOwned.emplace_back(ac);
}

void Player::addProperty(Ownable* property) {
    if (auto ab = dynamic_cast<AcademicBuilding*>(property))
        academicBuildingsOwned.push_back(ab);
    else if (auto gym = dynamic_cast<Gym*>(property))
        gymsOwned.push_back(gym);
    else if (auto res = dynamic_cast<Residence*>(property))
        residencesOwned.push_back(res);
}

void Player::removeProperty(Ownable* property) {
    if (auto academic = dynamic_cast<AcademicBuilding*>(property)) {
        academicBuildingsOwned.erase(
            std::remove(academicBuildingsOwned.begin(), academicBuildingsOwned.end(), academic), 
            academicBuildingsOwned.end()
        );
    } else if (auto gym = dynamic_cast<Gym*>(property)) {
        gymsOwned.erase(
            std::remove(gymsOwned.begin(), gymsOwned.end(), gym), 
            gymsOwned.end()
        );
    } else if (auto residence = dynamic_cast<Residence*>(property)) {
        residencesOwned.erase(
            std::remove(residencesOwned.begin(), residencesOwned.end(), residence), 
            residencesOwned.end()
        );
    }
}

bool Player::tradePforP(Player* other, Ownable* give, Ownable* recieve) {
    if (give->getOwner() != this || recieve->getOwner() != other) {
        return false; // one of the players doesn't own the property
    }

    removeProperty(give);
    other->removeProperty(recieve);

    addProperty(recieve);
    other->addProperty(give);

    recieve->changeOwner(this);
    give->changeOwner(other);

    return true;
}

bool Player::tradePforC(Player* other, Ownable* give, int amountRecieve) {
    if (give->getOwner() != this || other->getBalance() < amountRecieve) {
        return false; // player doesn't own property or other doesn't have enough money
    }

    removeProperty(give);
    if (!other->changeBalance(-amountRecieve)) return false;

    if(!changeBalance(amountRecieve)) return false;
    other->addProperty(give);

    give->changeOwner(other);

    return true;

}

bool Player::tradePforC(Player* other, int amountGive, Ownable* recieve) {
    if (getBalance() < amountGive || recieve->getOwner() != other) {
        return false;
    }

    if (!changeBalance(-amountGive)) return false;
    other->removeProperty(recieve);

    addProperty(recieve);
    if (!other->changeBalance(amountGive)) return false;

    recieve->changeOwner(this);

    return true;
}
