#ifndef ACADEMICBUILDING_H
#define ACADEMICBUILDING_H

#include "ownable.h"

class AcademicBuilding : public Ownable {
    std::string block;
    int improvements;
    int improvementCost;

public:
    AcademicBuilding(std::string name, int position, int cost, std::string block, int improvementCost);
    void landOn() override;
    void buyImprovement();
    void sellImprovement();
};

#endif
