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
    Square* getSquare(int position) const;
    Square* getSquareByName(const std::string& name) const;
    std::vector<Player>& getPlayers();
    std::vector<std::unique_ptr<Square>>& getSquares();
    std::vector<std::shared_ptr<Player>> getPlayers() const { return players; };
    
    // adds a player to the game
    void addPlayer(std::shared_ptr<Player> player);

    // removes the player from the game (if bankrupt)
    void removePlayer(std::shared_ptr<Player> player);

    // draws the board
    void drawBoard() const;

    // give the string that is a name of an ownable square, return an ownable pointer
    Ownable* findOwnableByName(std::string name);

    // return pointer to player given their name
    std::shared_ptr<Player> findPlayerByName(std::string name);

    std::shared_ptr<Square> getSquareSharedByName(const std::string& name);

    // moves player by n squares
    void movePlayer(std::shared_ptr<Player> player, int n);

    // returns the number of roll up the rim cups
    void returnCups(int count);

    // if the number of cups available greater than 0 returns true, false otherwise
    bool canGiveCup() const;

    // increases the number of roll up the rim cups the user owns by 1
    void giveCup(std::shared_ptr<Player> player);

    // starts the auction
    void startAuction(std::shared_ptr<Ownable> property, std::vector<std::shared_ptr<Player>>& players);
    
    // given a input stream from a file loads the game state saved in the given file
    void loadState(std::istream& in, std::vector<std::shared_ptr<Player>>& players);

    // saves the current state of the game to the output stream (file)
    void saveState(std::ostream& out) const;
};

#endif
