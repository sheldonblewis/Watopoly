#ifndef OWNABLE_H
#define OWNABLE_H

#include "square.h"

class Player;

class Ownable : public Square {
protected:
    Player* owner;
    int cost;
    bool mortgaged;

public:
    Ownable(std::string name, int position, int cost, std::string id);
    void purchase(Player* player);
    Player* getOwner() const;
};

#endif
