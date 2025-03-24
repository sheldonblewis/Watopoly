#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <memory>
#include "square.h"

class Board {
    std::vector<std::unique_ptr<Square>> squares;

public:
    Board();
    Square* getSquare(int position) const;
};

#endif
