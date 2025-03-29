#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <memory>
#include "academicbuilding.h"
#include "board.h"
#include "ownable.h"
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
    bool rolled;

    while (players.size() > 1) {
        auto currentPlayer = players[currentPlayerIndex];
        std::cout << "\nIt's " << currentPlayer->getName() << "'s turn (" << currentPlayer->getSymbol() << ")." << std::endl;

        rolled = false;

        while (true) {
            std::cout << "Enter \"help\" for a list of commands.\n";
            Ownable* ownable = dynamic_cast<Ownable*>(board.getSquare(currentPlayer->getPosition()));
            if (rolled && board.getSquare(currentPlayer->getPosition())->isOwnable()) {
                if (!ownable->getOwner()) {
                    std::cout << board.getSquare(currentPlayer->getPosition())->getName() << " is unowned. Input \"buy\" to purchase it.\nYou currently have $" << currentPlayer->getBalance() << ".\n";
                } else if (ownable->getOwner() != currentPlayer.get()) {
                    std::cout << board.getSquare(currentPlayer->getPosition())->getName() << " is owned by " << ownable->getOwner()->getName() << ".\n";
                    if (ownable->isMortgaged()) {
                        std::cout << "This property is mortgaged.\n";
                    } else {
                        int fees = ownable->calculateFees();
                        if (currentPlayer->changeBalance(-fees)) {
                            ownable->getOwner()->changeBalance(fees);
                            std::cout << currentPlayer->getName() << " paid $" << fees << " in rent to " << ownable->getOwner()->getName() << ".\n";
                        } else {
                            std::cout << currentPlayer->getName() << " cannot afford the rent and is bankrupt!\n";
                            players.erase(players.begin() + currentPlayerIndex);
                            break;
                        }
                    }
                } else if (currentPlayer->ownsAll(dynamic_cast<AcademicBuilding*>(ownable)->getMonopolyBlock())) {
                    std::cout << "You own all properties in the " << dynamic_cast<AcademicBuilding*>(ownable)->getMonopolyBlock() << " monopoly block! Enter \"improve " << ownable->getName() << " buy\" to buy an improvement.\nYou currently have $" << currentPlayer->getBalance() << ".\n";
                } else {
                    std::cout << "You own << " << board.getSquare(currentPlayer->getPosition())->getName() <<".\n";
                }
            }

            std::cout << "> ";
            std::cin >> command;

            if (command == "roll") {
                if (!rolled) {
                    rolled = true;
                    int prevPos = currentPlayer->roll(board);
                    board.getSquare(prevPos)->removePlayer(currentPlayer->shared_from_this());
                    board.getSquare(currentPlayer->getPosition())->addPlayer(currentPlayer->shared_from_this());
                    board.drawBoard();
                } else {
                    std::cout << "You have already rolled this turn.\n";
                }
            } else if (command == "buy") {
                if (!rolled) {
                    std::cout << "You must roll before you can buy.\n";
                    continue;
                } else if (board.getSquare(currentPlayer->getPosition())->isOwnable()) {
                    if (ownable->getOwner()) {
                        std::cout << "This property is already owned by " << ownable->getOwner()->getName() << ".\n";
                    } else if (currentPlayer->changeBalance(-ownable->getCost())) {
                        ownable->purchase(currentPlayer.get());
                        std::cout << currentPlayer->getName() << " purchased " << ownable->getName() << " for $" << ownable->getCost() << ".\n";
                        std::cout << "New balance: $" << currentPlayer->getBalance() << "\n";
                    } else {
                        std::cout << "Not enough funds to purchase this property.\n";
                    }
                } else {
                    std::cout << "This property cannot be purchased.\n";
                }
            } else if (command == "next" && rolled) {
                break;
            } else if (command == "assets") {
                currentPlayer->displayAssets();
            } else if (command == "all") {
                for (auto& p : players) {
                    p->displayAssets();
                }
            } else if (command == "improve") {
                std::string property, action;
                std::cin >> property >> action;
                
                if (board.getSquareByName(property) == nullptr) {
                    std::cout << "Property not found.\n";
                    continue;
                } else { 
                    auto square = board.getSquareByName(property);

                    auto academic = dynamic_cast<AcademicBuilding*>(square);
                    if (!academic) {
                        std::cout << "Improvement only applies to academic buildings.\n";
                        continue;
                    }
                
                    if (academic->getOwner() != currentPlayer.get()) {
                        std::cout << "You don't own " << property << ".\n";
                        continue;
                    }

                    if (action == "buy") {
                        academic->improve(currentPlayer.get());
                    } else if (action == "sell") {
                        academic->degrade(currentPlayer.get());
                    } else {
                        std::cout << "Unknown action. Use 'buy' or 'sell'.\n";
                    }
                }
            } else if (command == "mortgage") {
                std::string property;
                std::cin >> property;
            
                auto ownable = dynamic_cast<Ownable*>(board.getSquareByName(property));
                if (!ownable) {
                    std::cout << "Not a mortgageable property.\n";
                    continue;
                }
            
                if (ownable->getOwner() != currentPlayer.get()) {
                    std::cout << "You don't own this property.\n";
                    continue;
                }
            
                ownable->mortgage();
                std::cout << property << " has been mortgaged.\n";
            
            } else if (command == "unmortgage") {
                std::string property;
                std::cin >> property;
            
                auto ownable = dynamic_cast<Ownable*>(board.getSquareByName(property));
                if (!ownable) {
                    std::cout << "Not a mortgageable property.\n";
                    continue;
                }
            
                if (ownable->getOwner() != currentPlayer.get()) {
                    std::cout << "You don't own this property.\n";
                    continue;
                }
            
                ownable->unmortgage();
                std::cout << property << " has been unmortgaged.\n";
            } else if (command == "help") {
                std::cout <<
                "Available commands:\n"
                "• roll                        - Roll two dice and move forward.\n"
                "• next                        - End your turn and pass to the next player.\n"
                "• trade <name> <give> <receive> - Propose a trade with another player.\n"
                "    (give/receive can be a property or an amount of money)\n"
                "• improve <property> buy/sell - Buy or sell an improvement on a property.\n"
                "• mortgage <property>         - Mortgage a property.\n"
                "• unmortgage <property>       - Unmortgage a property.\n"
                "• bankrupt                    - Declare bankruptcy (only when required).\n"
                "• assets                      - Show current player’s assets.\n"
                "• all                         - Show all players’ assets.\n"
                "• save <filename>             - Save the current game state.\n"
                "• help                        - Show this help message.\n\n"
                "Note: Properties with improvements cannot be traded or mortgaged.\n"
                << std::endl;
            } else {
                std::cout << "Unknown command. Try again." << std::endl;
            }
        }
        
        currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
    }
}
