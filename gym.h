#ifndef GYM_H
#define GYM_H

#include "ownable.h"
#include "player.h"
#include <string>

class Gym : public Ownable {

public:
    Gym(std::string name, ,int position, int cost, std::string id);

    // calculates fees based on how many other gyms owner has
    // returns the fees that player that stepped on owes
    int calculateFees();
};

#endif
