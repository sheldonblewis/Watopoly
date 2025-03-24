#include "ownable.h"

Ownable::Ownable(std::string name, int position, int cost) :
    Square{name, position}, owner{nullptr}, cost{cost}, mortgaged{false} {}

void Ownable::purchase(Player* player) {
    owner = player;
}

Player* Ownable::getOwner() const { return owner; }
