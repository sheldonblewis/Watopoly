#include "academicbuilding.h"
#include <iostream>

AcademicBuilding::AcademicBuilding(std::string name, int position, int cost,
                                   std::string monopolyBlock, int improvementCost)
    : Ownable{name, position, cost},
      monopolyBlock{monopolyBlock},
      improvementCost{improvementCost} {}
