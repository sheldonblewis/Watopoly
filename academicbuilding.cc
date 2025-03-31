#include "academicbuilding.h"
#include "player.h"
#include <iostream>
#include <vector>

AcademicBuilding::AcademicBuilding(std::string name, int position, int cost, std::string monopolyBlock, int improvementCost, std::vector<int> tuitions) : Ownable{name, position, cost}, monopolyBlock{monopolyBlock}, improvementCost{improvementCost}, tuitions{tuitions} {}

std::string AcademicBuilding::getMonopolyBlock() const {
  return monopolyBlock;
}

bool AcademicBuilding::isOwnable() const {
  return true;
}

bool AcademicBuilding::improve(Player* player) {
  // have to check whether the player trying to improve
  if (owner != player) {
    return false;
  }

  // first need to check whether the owner owns the rest of the buildings in the monopoly block

  int counter = 0;

  for (const auto& building : owner->getACOwned()) {
    if (building->getMonopolyBlock() == monopolyBlock) {
        counter++;
    }
  }

  // arts1 and math are the only two blocks with only 2 academic buildings each
  if (monopolyBlock == "Arts1" || monopolyBlock == "Math") {
    if (counter != 2) {
      return false;
    }
  } else {
    if (counter != 3) {
      return false;
    }
  }

  // then we check whether the owner has enough money to improve the building

  // owner->changeBalance attempts to take moeny from account if funds aren't sufficient, balance unchanged and return false
  
  if(!owner->changeBalance(-improvementCost)) {
    return false;
  }

  improvements++;
  return true;
}

void AcademicBuilding::mortgage() { mortgaged = true; }

void AcademicBuilding::unmortgage() { mortgaged = false; }


void AcademicBuilding::drawImprovements() const {
  for (int i = 0; i < 5; ++i) {
      if (i < improvements) {
          std::cout << "X";
      } else {
          std::cout << " ";
      }
  }
}


int AcademicBuilding::numImprovements() const {
  return improvements;
}


int AcademicBuilding::calculateFees() {
  if (owner->ownsAll(monopolyBlock)) {
      return tuitions[improvements] * 2;
  }
  return tuitions[improvements];
}


int AcademicBuilding::getImprovementCost() const {
  return improvementCost;
}

bool AcademicBuilding::degrade(Player* player) {
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
