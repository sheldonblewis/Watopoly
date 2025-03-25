#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <memory>
class Board;

class Player : public std::enable_shared_from_this<Player> {
    std::string name;
    char symbol;
    int position = 0;
    int money = 1500;

public:
    Player(std::string name, char symbol);
    int roll(Board& board);
    int getPosition() const;
    std::string getName() const;
    char getSymbol() const;
    void displayAssets() const;
};

#endif
