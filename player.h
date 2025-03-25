#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <memory>
#include <vector>
#include "gym.h"
#include "residence.h"
#include "academicbuilding.h"

class Board;

class Player {
    std::string name;
    char symbol;
    int position = 0;
    int balance;

    std::vector<AcademicBuilding*> academicBuildingsOwned;
    std::vector<Gym*> gymsOwned;
    std::vector<Residence> residencesOwnded;
    

public:
    Player(std::string name, char symbol);
    void roll(Board& board);
    int getPosition() const;
    std::string getName() const;

    int getBalance() const;

    // return true if change balance was successfull 
    // false if the player doens't have enough money
    bool changeBalance(int amount);

    // takes in a gym pointer and returns true if player owns
    // that gym, false otherwise
    bool ownsGym(Gym* gym) const;


    // takes in a residence pointer and returns true if player owns
    // that residence, false otherwise
    bool ownsResidence(Residence* residence) const;


    // takes in a academic building pointer and returns true if player 
    // owns that academic building, false otherwise
    bool ownsAcademicBuilding(AcademicBuilding* ac) const;
};

#endif
