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

    // attempts to inprove the academic building, returns true if suceeded, false otherwise (should print out why it failed)
    // player is intended to be the current player
    bool improve(Player* player);

    bool degrade(Player* player) {
        if (owner != player) {
            return false;
        }

        if (improvements == 0) {
            return false;
        }

        improvements--;
        owner->changeBalance(improvementCost / 2);
        return true;
    }

    // attempts to mortgage the academic building, returns true if suceeded, false otherwise (should print out why it failed)
    void mortgage();

    // attempts to unmortgage the academic building, returns true if suceeded, false otherwise (should print out why it failed)
    void unmortgage();

    bool isOwnable() const;

    int numImprovements() const {
        return improvements;
    }

    void drawImprovements() const {
        for (int i = 0; i < 5; ++i) {
            if (i < improvements) {
                std::cout << "I";
            } else {
                std::cout << " ";
            }
        }
    }

    int getImprovementCost() const {
        return improvementCost;
    }

    int calculateFees() override {
        if (owner->ownsAll(monopolyBlock) && improvements == 0) {
            std::cout << getOwner() <<" has all properties in the " << monopolyBlock << " block, charging double tuition.\n";
            return tuitions[0] * 2;
        } else if (improvements != 0) {
            std::cout << getOwner() << " has " << improvements << " improvements on " << getName() << ".\n";
            return tuitions[improvements];
        } else {
            return tuitions[0];
        }
    }
};

#endif
