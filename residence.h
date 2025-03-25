#ifndef RESIDENCE_H
#define RESIDENCE_H

#include "ownable.h"
#include "player.h"
#include <string>

class Residence : public Ownable {

public:
    Residence(std::string name, int position, int cost);

    // calculates fees based on how many other residences owner has
    // returns the fees that player that stepped on owes
    int calculateFees();
};

#endif
