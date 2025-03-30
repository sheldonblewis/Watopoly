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
    int cupsAvailable = 4;

public:
    Board();
    void addPlayer(std::shared_ptr<Player> player);
    void removePlayer(std::shared_ptr<Player> player);
    Square* getSquare(int position) const;
    Square* getSquareByName(const std::string& name) const;
    void drawBoard() const;
    std::vector<Player>& getPlayers();
    std::vector<std::unique_ptr<Square>>& getSquares();
    std::vector<std::shared_ptr<Player>> getPlayers() const { return players; };
    
    // give the string that is a name of an ownable square, return an ownable pointer
    Ownable* findOwnableByName(std::string name);

    // return pointer to player given their name
    std::shared_ptr<Player> findPlayerByName(std::string name);

    std::shared_ptr<Square> getSquareSharedByName(const std::string& name);

    // moves player by n squares
    void movePlayer(std::shared_ptr<Player> player, int n);
    void returnCups(int count);
    bool canGiveCup() const;
    void giveCup(std::shared_ptr<Player> player);
    void startAuction(std::shared_ptr<Ownable> property, std::vector<std::shared_ptr<Player>>& players);
    
    void loadState(std::istream& in, std::vector<std::shared_ptr<Player>>& players);
    void saveState(std::ostream& out) const;
};

#endif
