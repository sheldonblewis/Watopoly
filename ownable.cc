#include "ownable.h"
#include "square.h"

Ownable::Ownable(std::string name, int position, int cost)
    : Square{position, name}, owner{nullptr}, cost{cost}, mortgaged{false} {}

void Ownable::purchase(Player* player) {
    owner = player;
}

Player* Ownable::getOwner() const { return owner; }

int Ownable::getCost() const { return cost; }

bool Ownable::isMortgaged() const { return mortgaged; }

void Ownable::mortgage() { mortgaged = true; }

void Ownable::unmortgage() { mortgaged = false; }
