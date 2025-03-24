#include "player.h"
#include "board.h"
#include <iostream>
#include <random>

Player::Player(std::string name, char symbol) : name{name}, symbol{symbol} {}

int Player::getPosition() const {
    return position;
}

std::string Player::getName() const {
    return name;
}

void Player::roll(Board& board) {
    int die1 = rand() % 6 + 1;
    int die2 = rand() % 6 + 1;
    int move = die1 + die2;
    std::cout << name << " rolled " << die1 << " + " << die2 << " = " << move << std::endl;

    position = (position + move) % board.numSquares();
    std::cout << name << " moved to " << board.getSquare(position)->getName() << std::endl;
}
