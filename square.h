#ifndef SQUARE_H
#define SQUARE_H

#include <memory>
#include <string>
#include <vector>
#include "player.h"

class Square {
    int position;
    std::string name;
    std::vector<std::shared_ptr<Player>> players = {};


public:
    Square(int position, std::string name);
    std::string getName() const;
    const std::vector<std::shared_ptr<Player>>& getPlayers() const;
    void drawPlayers();
    void addPlayer(std::shared_ptr<Player> player);
    void removePlayer(std::shared_ptr<Player> player);
    std::string getId() const;
    int getPosition() const;
    virtual ~Square() = default;
};

#endif
