#ifndef OWNABLE_H
#define OWNABLE_H

#include <memory>
#include <string>
#include "square.h"

class Player;

class Ownable : public Square {
protected:
    Player* owner;
    int cost;
    bool mortgaged;

public:
    Ownable(std::string name, int position, int cost);
    void purchase(Player* player);
    Player* getOwner() const;
    void setOwner(std::shared_ptr<Player> newOwner);
    int getCost() const;
    bool isMortgaged() const;
    void mortgage();
    void unmortgage();
    virtual int calculateFees() = 0;
    virtual bool isGym() const { return false; }
};

#endif
