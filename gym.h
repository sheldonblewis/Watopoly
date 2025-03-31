#ifndef GYM_H
#define GYM_H

#include "ownable.h"
#include "player.h"
#include <string>

class Gym : public Ownable, public std::enable_shared_from_this<Gym> {

public:
    Gym(std::string name, int position, int cost);

    // calculates fees based on how many other gyms owner has returns the fees that player that stepped on owes
    int calculateFees();

    // always returns true
    bool isOwnable() const override;

    // always returns true
    bool isGym() const override;
};

#endif
