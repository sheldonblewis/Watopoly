#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

class Square;

class Player {
    std::string name;
    char symbol;
    int money;
    int position;
    int timsCups;

public:
    Player(std::string name, char symbol, int money = 1500, int position = 0);
    void move(int steps);
    int getPosition() const;
    std::string getName() const;
    char getSymbol() const;
    int getMoney() const;
    void changeMoney(int amount);
};

#endif
