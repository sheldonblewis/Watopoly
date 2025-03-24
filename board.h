#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <memory>
#include <iostream>
#include "square.h"
#include "player.h"

class Board {
    std::vector<std::shared_ptr<Player>> players;
    std::vector<std::shared_ptr<Square>> squares;

public:
    Board();
    void addPlayer(std::shared_ptr<Player> player);
    std::shared_ptr<Square> getSquare(int position) const;
    void drawBoard() const;
    int numSquares() const;
};

#endif
