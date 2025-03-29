#ifndef NONOWNABLE_H
#define NONOWNABLE_H

#include "square.h"
#include <string>

class NonOwnable : public Square {
public:
    NonOwnable(int position, std::string name);
    bool isOwnable() const override;
};

#endif
