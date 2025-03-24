#ifndef ACADEMICBUILDING_H
#define ACADEMICBUILDING_H

#include "ownable.h"
#include <string>

class AcademicBuilding : public Ownable {
    std::string monopolyBlock;
    int improvementCost;
    int improvements = 0;

public:
    AcademicBuilding(std::string name, int position, int cost,
                     std::string monopolyBlock, int improvementCost);

    void display() const;
    void action(Player &p);
};

#endif
