#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <memory>
#include "board.h"
#include "player.h"

int main() {
    srand(time(nullptr));
    Board board;
    std::vector<std::shared_ptr<Player>> players;

    std::vector<char> allowedChars = {'G', 'B', 'D', 'P', 'S', '$', 'L', 'T'};
    std::map<char, std::string> charNames = {
        {'G', "Goose"}, {'B', "GRT Bus"}, {'D', "Tim Hortons Doughnut"},
        {'P', "Professor"}, {'S', "Student"}, {'$', "Money"},
        {'L', "Laptop"}, {'T', "Pink tie"}
    };

    int numPlayers;
    std::set<char> takenChars;

    while (true) {
        std::cout << "Enter number of players (2-6): ";
        std::cin >> numPlayers;
        if (numPlayers >= 2 && numPlayers <= 6) break;
        std::cout << "Invalid number. Please enter a value between 2 and 6.\n";
    }

    for (int i = 0; i < numPlayers; ++i) {
        std::string name;
        char symbol;

        std::cout << "Enter name for Player " << (i + 1) << ": ";
        std::cin >> name;

        while (true) {
            std::cout << "Choose a character from the list:\n";
            for (char ch : allowedChars) {
                if (takenChars.find(ch) == takenChars.end()) {
                    std::cout << ch << " (" << charNames[ch] << ")\n";
                }
            }

            std::cout << "Enter character: ";
            std::cin >> symbol;

            if (std::find(allowedChars.begin(), allowedChars.end(), symbol) != allowedChars.end()
                && takenChars.find(symbol) == takenChars.end()) {
                takenChars.insert(symbol);
                break;
            } else {
                std::cout << "Invalid or already taken character. Try again.\n";
            }
        }
        
        auto player = std::make_shared<Player>(name, symbol);
        board.addPlayer(player);
        players.push_back(player);
        board.getSquare(0)->addPlayer(player);  // Start all players at position 0
        std::cout << name << " has chosen " << charNames[symbol] << " (" << symbol << ").\n";
    }

    std::cout << "Game starting!" << std::endl;
    int currentPlayerIndex = 0;
    std::string command;

    board.drawBoard();

    while (players.size() > 1) {
        auto currentPlayer = players[currentPlayerIndex];
        std::cout << "\nIt's " << currentPlayer->getName() << "'s turn (" << currentPlayer->getSymbol() << ")." << std::endl;

        while (true) {
            std::cout << "> ";
            std::cin >> command;

            if (command == "roll") {
                int prevPos = currentPlayer->roll(board);
                board.getSquare(prevPos)->removePlayer(currentPlayer->shared_from_this());
                board.getSquare(currentPlayer->getPosition())->addPlayer(currentPlayer->shared_from_this());
                board.drawBoard();
                break;
            } else if (command == "next") {
                break;
            } else if (command == "assets") {
                currentPlayer->displayAssets();
            } else if (command == "all") {
                for (auto& p : players) {
                    p->displayAssets();
                }
            } else {
                std::cout << "Unknown command. Try again." << std::endl;
            }
        }
        
        currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
    }
}
