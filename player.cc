#include "board.h"
#include "player.h"
#include "square.h"
#include <iostream>
#include <random>
#include <vector>

Player::Player(std::string name, char symbol) : name{name}, symbol{symbol} {}

int Player::getPosition() const {
    return position;
}

std::string Player::getName() const {
    return name;
}

int Player::roll(Board& board) {
    int die1 = rand() % 6 + 1;
    int die2 = rand() % 6 + 1;
    int move = die1 + die2;
    std::cout << name << " rolled " << die1 << " + " << die2 << " = " << move << std::endl;

    position = (position + move) % 40;

    std::cout << name << " moved to " << board.getSquare(position)->getName() << std::endl;

    return (position - move) % 40;
}


char Player::getSymbol() const {
    return symbol;
}

void Player::displayAssets() const {
    std::cout << "Player: " << name << " ($" << money << "), Position: " << position << std::endl;
    // Add more asset info here later (like owned properties)
}
