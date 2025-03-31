#ifndef ACADEMICBUILDING_H
#define ACADEMICBUILDING_H

#include "ownable.h"
#include <iostream>
#include <string>
#include <vector>

class Player;

class AcademicBuilding : public Ownable, public std::enable_shared_from_this<AcademicBuilding> {
    std::string monopolyBlock;
    int improvementCost;
    int improvements = 0;
    std::vector<int> tuitions;

public:
    AcademicBuilding(std::string name, int position, int cost, std::string monopolyBlock, int improvementCost, std::vector<int> tuitions);

    // returns building's monopoly block
    std::string getMonopolyBlock() const;

    // attempts to improve the academic building, returns true if suceeded, false otherwise (should print out why it failed)
    // player is intended to be the current player
    bool improve(Player* player);

    // attempts to degrade the academic building, returns true if suceeded, false otherwise (should print out why it failed)
    // player is intended to be the current player
    bool degrade(Player* player);

    // attempts to mortgage the academic building, returns true if suceeded, false otherwise (should print out why it failed)
    void mortgage();

    // attempts to unmortgage the academic building, returns true if suceeded, false otherwise (should print out why it failed)
    void unmortgage();

    // returns true if the object it is called on inherits from ownable
    bool isOwnable() const;

    // returns number of improvements of the academic building
    int numImprovements() const;

    // Draws 'X' for each improvement the academic building has
    void drawImprovements() const;

    // returns improvement cost of the academic building object
    int getImprovementCost() const;

    // returns the fees owned to the owner if another player stepped on the square
    // based on number of improvemetns and number of properties owned
    int calculateFees() override;
};

#endif
