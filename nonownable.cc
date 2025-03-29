#include "nonownable.h"

NonOwnable::NonOwnable(int position, std::string name)
    : Square(position, name) {}

bool NonOwnable::isOwnable() const {
    return false;
}
