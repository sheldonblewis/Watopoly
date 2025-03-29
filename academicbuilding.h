#ifndef ACADEMICBUILDING_H
#define ACADEMICBUILDING_H

#include "ownable.h"
#include <vector>
#include <string>

class Player;

class AcademicBuilding : public Ownable {
    std::string monopolyBlock;
    int improvementCost;
    int improvements = 0;
    std::vector<int> tuitions;

public:
    AcademicBuilding(std::string name, int position, int cost, std::string monopolyBlock, int improvementCost, std::vector<int> tuitions);

    // returns buildings monopoly block
    std::string getMonopolyBlock() const;

    // attempts to inprove the academic building, returns true
    // if suceeded, false otherwise (should print out why it failed)
    // player is intented to be the current player
    bool improve(Player* player);

    bool degrade(Player* player) {
        if (owner != player) {
            return false;
        }

        if (improvements == 0) {
            return false;
        }

        improvements--;
        owner->changeBalance(improvementCost / 2); // half the cost of improvement
        return true;
    }

    // attempts to mortgage the academic building, returns true
    // if suceeded, false otherwise (should print out why it failed)
    bool mortgage();

    // attempts to unmortgage the academic building, returns true
    // if suceeded, false otherwise (should print out why it failed)
    bool unmortgage();

    bool isOwnable() const;

    int numImprovements() const {
        return improvements;
    }

    void drawImprovements() const {
        for (int i = 0; i < 5; ++i) {
            if (i < improvements) {
                std::cout << "X";
            } else {
                std::cout << " ";
            }
        }
    }

    int getImprovementCost() const {
        return improvementCost;
    }

    int calculateFees() override {
        if (owner->ownsAll(monopolyBlock)) {
            return tuitions[improvements] * 2;
        }
        return tuitions[improvements];
    }
};

#endif
