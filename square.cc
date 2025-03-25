#include "square.h"
#include "player.h"
#include <iostream>

Square::Square(int position, std::string name) : position{position}, name{name} {
    std::vector<std::shared_ptr<Player>> players = {};
}

std::string Square::getName() const {
    return name;
}

const std::vector<std::shared_ptr<Player>>& Square::getPlayers() const {
    return players;
}

void Square::drawPlayers() {
    if (players.size() == 0) {
        std::cout << "      ";
    } else if (players.size() == 1) {
        std::cout << "  " << players[0]->getSymbol() << "   ";
    } else if (players.size() == 2) {
        std::cout << " " << players[0]->getSymbol() << " " << players[1]->getSymbol() << "  ";
    } else if (players.size() == 3) {
        std::cout << players[0]->getSymbol() << " " << players[1]->getSymbol() << " " << players[2]->getSymbol() << " ";
    } else if (players.size() == 4) {
        std::cout << players[0]->getSymbol() << players[1]->getSymbol() << " " << players[2]->getSymbol() << players[3]->getSymbol() << " ";
    } else if (players.size() == 5) {
        std::cout << players[0]->getSymbol() << players[1]->getSymbol() << players[2]->getSymbol() << players[3]->getSymbol() << players[4]->getSymbol() << " ";
    } else {
        std::cout << players[0]->getSymbol() << players[1]->getSymbol() << players[2]->getSymbol() << players[3]->getSymbol() << players[4]->getSymbol() << players[5]->getSymbol();
    }
    return;
}

void Square::addPlayer(std::shared_ptr<Player> player) {
    players.emplace_back(player);
}

void Square::removePlayer(std::shared_ptr<Player> player) {
    for (int i = 0; i < players.size(); ++i) {
        if (players[i] == player) {
            players.erase(players.begin() + i);
            return;
        }
    }
std::string Square::getId() const {
    return id;
}

int Square::getPosition() const {
    return position;
}
