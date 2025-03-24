#include "academicbuilding.h"

AcademicBuilding::AcademicBuilding(std::string name, int position, int cost, std::string block, int improvementCost) :
    Ownable{name, position, cost}, block{block}, improvements{0}, improvementCost{improvementCost} {}

void AcademicBuilding::landOn() {
    // Basic rent logic here
}

void AcademicBuilding::buyImprovement() {
    if(improvements < 5) improvements++;
}

void AcademicBuilding::sellImprovement() {
    if(improvements > 0) improvements--;
}
