#ifndef ACADEMICBUILDING_H
#define ACADEMICBUILDING_H

#include "ownable.h"
#include <vector>
#include <string>

class AcademicBuilding : public Ownable {
    std::string monopolyBlock;
    int improvementCost;
    int improvements = 0;
    std::vector<int> tuitions;

public:
    AcademicBuilding(std::string name, int position, int cost,
                     std::string monopolyBlock, int improvementCost, std::vector<int> tuitions);

    // returns buildings monopoly block
    std::string getMonopolyBlock() const;

    // attempts to inprove the academic building, returns true
    // if suceeded, false otherwise (should print out why it failed)
    // player is intented to be the current player
    bool improve(Player* player);

    // attempts to mortgage the academic building, returns true
    // if suceeded, false otherwise (should print out why it failed)
    bool mortgage();

    // attempts to unmortgage the academic building, returns true
    // if suceeded, false otherwise (should print out why it failed)
    bool unmortgage();
};

#endif
