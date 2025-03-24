#include "player.h"

Player::Player(std::string name, char symbol, int money, int position) :
    name{name}, symbol{symbol}, money{money}, position{position}, timsCups{0} {}

void Player::move(int steps) {
    position = (position + steps) % 40; 
}

int Player::getPosition() const { return position; }
std::string Player::getName() const { return name; }
char Player::getSymbol() const { return symbol; }
int Player::getMoney() const { return money; }
void Player::changeMoney(int amount) { money += amount; }
