#ifndef RESIDENCE_H
#define RESIDENCE_H

#include "ownable.h"
#include <string>

class Residence : public Ownable {

public:
    Residence(std::string name, int position, int cost);

    void display() const;
    void action(Player &p);
};

#endif
