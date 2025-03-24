#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <memory>
class Board;

class Player {
    std::string name;
    char symbol;
    int position = 0;

public:
    Player(std::string name, char symbol);
    void roll(Board& board);
    int getPosition() const;
    std::string getName() const;
};

#endif
