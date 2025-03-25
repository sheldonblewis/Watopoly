#ifndef GYM_H
#define GYM_H

#include "ownable.h"
#include <string>

class Gym : public Ownable {

public:
    Gym(std::string name, int position, int cost);

    void display() const;
    void action(Player &p);
};

#endif
