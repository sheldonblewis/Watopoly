#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <memory>
#include <iostream>
#include "square.h"
#include "player.h"
#include "ownable.h"

class Board {
    std::vector<std::shared_ptr<Player>> players;
    std::vector<std::unique_ptr<Square>> squares;

public:
    Board();
    void addPlayer(std::shared_ptr<Player> player);
    Square* getSquare(int position) const;
    void drawBoard() const;
    std::vector<Player>& getPlayers();
    std::vector<std::unique_ptr<Square>>& getSquares();
    
    // give the string that is a name of an ownable square, return 
    // an ownable pointer
    Ownable* findOwnableByName(std::string name);

    // return pointer to player given their name
    std::shared_ptr<Player> findPlayerByName(std::string name);
    
};

#endif
