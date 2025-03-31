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
    virtual ~Square() = default; // virtual destructor for proper cleanup of derived classes
    virtual bool isOwnable() const = 0; // pure virtual function to enforce implementation in derived classes

    // returns the name of the square
    std::string getName() const;

    // returns the players currently on the square object
    const std::vector<std::shared_ptr<Player>>& getPlayers() const;

    // draws the players that are currently on the square
    void drawPlayers();

    // add player to the vector of players of square (player steps on square)
    void addPlayer(std::shared_ptr<Player> player);

    // remove player from the vector of players (player leaves the squre)
    void removePlayer(std::shared_ptr<Player> player);

    // returns ID 
    std::string getId() const;

    // returns postion
    int getPosition() const;
};

#endif
