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
    
    // sets new owner and adds the property to the new owners
    // properties
    void purchase(Player* player);
    
    // returns the owner of the Ownable object
    Player* getOwner() const;

    // returns purchase cost of the Ownable object
    int getCost() const;

    // returns true if Ownable objects is mortgaged, false otherwise
    bool isMortgaged() const;

    // attempts to mrtgage the property
    void mortgage();

    // attempts to unmortgage the property
    void unmortgage();

    // virtual function to calculate fees
    virtual int calculateFees() = 0;
    
    // always returns false
    virtual bool isGym() const;

    // changes the owner of the ownable object
    void changeOwner(Player* newOwner);

    virtual ~Ownable() = default;
};

#endif
