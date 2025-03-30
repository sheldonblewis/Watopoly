// TODO: jail logic, non-property squares, trading, saving/loading game state, bankruptcy, and more detailed error handling.

#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <memory>
#include "academicbuilding.h"
#include <sstream>
#include "board.h"
#include "ownable.h"
#include "player.h"

bool isInteger(const std::string& str) {
    try {
        std::stoi(str);
        return true;
    } catch (const std::invalid_argument& e) {
        return false;
    } catch (const std::out_of_range& e) {
        return false;
    }
}

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
        board.getSquare(0)->addPlayer(player);  // start all players at position 0
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
            if (rolled) {
                if (board.getSquare(currentPlayer->getPosition())->isOwnable()) {
                    if (!ownable->getOwner()) {
                        std::cout << board.getSquare(currentPlayer->getPosition())->getName() << " is unowned. Input \"buy\" to purchase it.\nYou currently have $" << currentPlayer->getBalance() << ".\n";
                    } else if (ownable->getOwner() != currentPlayer.get()) {
                        std::cout << board.getSquare(currentPlayer->getPosition())->getName() << " is owned by " << ownable->getOwner()->getName() << ".\n";
                        if (ownable->isMortgaged()) {
                            std::cout << "This property is mortgaged.\n";
                        } else {
                            if (ownable->isGym()) {
                                std::cout << "Gyms charge rent at 4x the dice roll if the owner has 1 gym, or 10x if they have both. Rolling again...\n";
                            }
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
                } else if (!board.getSquare(currentPlayer->getPosition())->isOwnable()) { // landed on a non-ownable square
                    int curr_position = currentPlayer->getPosition();
                    
                    if (curr_position == 2 || curr_position == 17 || curr_position == 33) { // SLC 
                        // 1% chance to get RUR;
                        currentPlayer->chanceForRUR();
                        
                        int choice = currentPlayer->randNum(24);

                        if (1 <= choice && choice <= 3) {
                            board.movePlayer(currentPlayer, -3);
                        } else if (4 <= choice && choice <= 7) {
                            board.movePlayer(currentPlayer, -2);
                        } else if (8 <= choice && choice <= 11) {
                            board.movePlayer(currentPlayer, -1);
                        } else if (12 <= choice && choice <= 14) {
                            board.movePlayer(currentPlayer, 1);
                        } else if (15 <= choice && choice <= 18) {
                            board.movePlayer(currentPlayer, 2);
                        } else if (19 <= choice && choice <= 22) {
                            board.movePlayer(currentPlayer, 3);
                        } else if (choice == 23) {
                            currentPlayer->sendToJail();
                        } else {

                        }

                    } else if (curr_position == 4) { // TUITION

                    } else if (curr_position == 7 || curr_position == 36 || curr_position == 22) { // NEEDLES HALL

                    } else if (curr_position == 10) { // DC TIMS LINE

                    } else if (curr_position == 20) { // GOOSE NESTING 
                        std::cout << "You are being attacked by a flock of nesting geese! RUN!"

                    } else if (curr_position == 30) { // GO TO TIMS
                        currentPlayer->sendToJail();
                        
                    } else if (curr_position == 38) { // COOP FEE
                        std::cout << "You have to pay the coop fee! ($150)" << std::endl;

                        bool transaction_successful = currentPlayer->changeBalance(-150);

                        if (transaction_successful) {
                            std::cout << "You have successfully payed the Co-op fee" << std::endl;
                        } else {
                            std::cout << "You don't have enough funds to pay the Co-op fee!" << std::endl;

                            bool possible_to_survive = currentPlayer->possibleToSurvive(150); // checks if the mortgage value of all of players buildings is > 150;

                            if (possible_to_survive) {
                                bool enough_to_pay = false;
                                
                                while (!enough_to_pay) {
                                    currentPlayer->mortgageProperties();

                                    if (currentPlayer->getBalance() >= 150) {
                                        enough_to_pay = true;
                                    } else {
                                        std::cout << "Your current balance isn't enough to cover the Co-op fee. You need to mrtgage more properties." << std::endl;
                                    }
                                }

                                currentPlayer->changeBalance(-150);
                            } else {
                                // still have to implement what happens to player when he bankrupts
                            }
                        }
                    }
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
                
                if (action == "buy" && !rolled) {
                    std::cout << "You must roll before you can buy improvements.\n";
                    continue;
                } else {
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

                        if (!currentPlayer->ownsAll(academic->getMonopolyBlock())) {
                            std::cout << "You must own all properties in the " << academic->getMonopolyBlock() << " monopoly block to buy improvements.\n";
                        }

                        if (academic->isMortgaged()) {
                            std::cout << "You cannot improve a mortgaged property.\n";
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

                AcademicBuilding* ac = dynamic_cast<AcademicBuilding*>(ownable);

                if (ac) {
                    if (ac->getImpovements == 0) {
                        ac->mortgage();
                        currentPlayer->changeBalance(ac->getCost() / 2);
                        std::cout << property << " has been mortgaged.\n";
                    } else {
                        std::cout << "Can't mortgage an Academic Building with improvements."
                    }
                } else {
                    ownable->mortgage();
                    currentPlayer->changeBalance(ac->getCost() / 2);
                    std::cout << property << " has been mortgaged.\n";
                }
            
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

                if (currentPlayer->getBalance() < (ownable->getCost() / 2) * 0.1) {
                    std::cout << "Not enough money to unmortgage property" << std::endl;
                } else {
                    ownable->unmortgage();
                    currentPlayer->changeBalance(-((ownable->getCost() / 2) * 0.1));
                    std::cout << property << " has been unmortgaged.\n";
                }
            
                
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
            } else if (command == "trade") {
                std::string name;
                std::string give;
                std::string recieve;

                std::cin >> name;
                std::cin >> give;
                std::cin >> recieve;

                bool giveInt = isInteger(give);
                bool recieveInt = isInteger(recieve);

                if (giveInt && recieveInt) { // if both give and recieve are integers, doesn't work
                    std::cout << "\n Unable to trade money for money, try again." << std::endl;
                } else {

                    std::cout << "\nDoes " << name << " accept this trade? (Y/N): ";
                    std::string decision;
    
                    std::cin >> decision;
    
                    if (decision == "Y") {
                        if (!giveInt && !recieveInt) { // trade property for property                     
                            Ownable* give_ptr = board.findOwnableByName(give);
                            Ownable* recieve_ptr = board.findOwnableByName(recieve);
                            std::shared_ptr<Player> player_trade = board.findPlayerByName(name);
                            
                            if (give_ptr && recieve_ptr && player_trade) {
                                bool trade_success = currentPlayer->tradePforP(player_trade, give_ptr, recieve_ptr);
                                if (trade_success) {
                                    std::cout << "Trade successful!" << std::endl;
                                } else {
                                    std::cout << "Trade failed. Try again." << std::endl;
                                }
                            } else {
                                std::cout << "Player or one of the squares do not exist" << std::endl;
                            }

                            
                        } else if (!giveInt && recieveInt) { // trade property for money
                            int money_recieve = std::stoi(recieve);
                            Ownable* give_ptr = board.findOwnableByName(give);
                            std::shared_ptr<Player> player_trade = board.findPlayerByName(name);
                            
                            if (give_ptr && player_trade) {
                                bool trade_success = currentPlayer->tradePforC(player_trade, give_ptr, money_recieve);
                                if (trade_success) {
                                    std::cout << "Trade successful!" << std::endl;
                                } else {
                                    std::cout << "Trade failed. Try again." << std::endl;
                                }
                            } else {
                                std::cout << "Trade failed. Try again." << std::endl;
                            }

                        } else if (giveInt && !recieveInt) { // trade money for property
                            int money_give = std::stoi(give);
                            Ownable* recieve_ptr = board.findOwnableByName(recieve);
                            std::shared_ptr<Player> player_trade = board.findPlayerByName(name);

                            if (recieve_ptr && player_trade) {
                                bool trade_success = currentPlayer->tradeCforP(player_trade, money_give, recieve_ptr);
                                if (trade_success) {
                                    std::cout << "Trade successful!" << std::endl;
                                } else {
                                    std::cout << "Trade failed. Try again." << std::endl;
                                }
                            } else {
                                std::cout << "Trade failed. Try again." << std::endl;
                            }
                        } 
                    } else if (decision == "N") {
                        std::cout << name << "declines the trade" << std::endl;
                    } else {
                        std::cout << "Invalid answer, try again" << std::endl;
                    }
                }
                
            } else {
                std::cout << "Unknown command. Try again." << std::endl;
            }
        }
        
        currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
    }
}
