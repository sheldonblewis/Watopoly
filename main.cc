#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include "academicbuilding.h"
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

int main(int argc, char* argv[]) {
    srand(time(nullptr));
    Board board;
    std::vector<std::shared_ptr<Player>> players;

    if (argc > 1 && std::string(argv[1]) == "-load" && argc > 2) {
        std::ifstream file(argv[2]);
        board.loadState(file, players);
    }

    std::vector<char> allowedChars = {'G', 'B', 'D', 'P', 'S', '$', 'L', 'T'};
    std::map<char, std::string> charNames = {
        {'G', "Goose"}, {'B', "GRT Bus"}, {'D', "Tim Hortons Doughnut"},
        {'P', "Professor"}, {'S', "Student"}, {'$', "Money"},
        {'L', "Laptop"}, {'T', "Pink tie"}
    };

    int numPlayers;
    std::string input;
    std::set<char> takenChars;

    while (true) {
        std::cout << "Enter number of players (2-6): ";
        std::cin >> input;
        if (isInteger(input)) {
            numPlayers = std::stoi(input);
            if (numPlayers >= 2 && numPlayers <= 6) {
                break;
            } else {
                std::cout << "Invalid number. Please enter a value between 2 and 6.\n";
            }
        } else {
            std::cout << "Please enter an integer\n";
        }
        
        
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

        int action_done = false;

        while (true) {
            std::cout << "Enter \"help\" for a list of commands.\n";
            Ownable* ownable = dynamic_cast<Ownable*>(board.getSquare(currentPlayer->getPosition()));
            if (rolled && !action_done) {
                if (board.getSquare(currentPlayer->getPosition())->isOwnable()) {
                    if (!ownable->getOwner()) {
                        Ownable* ownable = dynamic_cast<Ownable*>(board.getSquare(currentPlayer->getPosition()));
                        std::cout << board.getSquare(currentPlayer->getPosition())->getName() << " is unowned. Input \"buy\" to purchase it for $"<< ownable->getCost() << ".\nYou currently have $" << currentPlayer->getBalance() << ".\n";
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
                                board.removePlayer(currentPlayer);
                                currentPlayer->declareBankruptcy(nullptr, board, players);
                                players.erase(players.begin() + currentPlayerIndex);
                                break;
                            }
                        }
                    } else if (currentPlayer->ownsAll(dynamic_cast<AcademicBuilding*>(ownable)->getMonopolyBlock())) {
                        std::cout << "You own all properties in the " << dynamic_cast<AcademicBuilding*>(ownable)->getMonopolyBlock() << " monopoly block! Enter \"improve " << ownable->getName() << " buy\" to buy an improvement.\nYou currently have $" << currentPlayer->getBalance() << ".\n";
                    } else {
                        std::cout << "You own " << board.getSquare(currentPlayer->getPosition())->getName() <<".\n";
                    }
                } else if (!board.getSquare(currentPlayer->getPosition())->isOwnable()) {
                    int curr_position = currentPlayer->getPosition();
                    
                    if (curr_position == 2 || curr_position == 17 || curr_position == 33) {
                        // 1% chance to get cup;
                        currentPlayer->chanceForCup();
                        
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
                            currentPlayer->sendToTimsLine(board);
                        } else {
                            currentPlayer->changePosition(0);
                            board.getSquare(0)->addPlayer(currentPlayer->shared_from_this());
                            board.getSquare(currentPlayer->getPosition())->removePlayer(currentPlayer->shared_from_this());
                            board.drawBoard();
                        }

                    } else if (curr_position == 4) { // TUITION

                    } else if (curr_position == 7 || curr_position == 36 || curr_position == 22) { // NEEDLES HALL
                        currentPlayer->chanceForCup();
                        
                        int choice = currentPlayer->randNum(18);
                        int amount_owned;

                        if (choice == 1) {
                            amount_owned = -200;
                        } else if (2 <= choice && choice <= 3) {
                            amount_owned = -100;
                        } else if (4 <= choice && choice <= 6) {
                            amount_owned = -50;
                        } else if (7 <= choice && choice <= 12) {
                            amount_owned = 25;
                        } else if (13 <= choice && choice <= 15) {
                            amount_owned = 50;
                        } else if (16 <= choice && choice <= 17) {
                            amount_owned = 100;
                        } else {
                            amount_owned = 200;
                        }

                        if (amount_owned > 0) {
                            std::cout << "Congratulations you receive $" << amount_owned << " from the Needles Hall!" <<std::endl;
                        } else {
                            std::cout << "You landed on the Needles hall have to pay $" << amount_owned << std::endl;

                            bool transaction_successful = currentPlayer->changeBalance(amount_owned);
    
                            if (transaction_successful) {
                                std::cout << "You have successfully payed the Needles Hall" << std::endl;
                            } else {
                                std::cout << "You don't have enough funds to pay the Needles Hall" << std::endl;
    
                                bool possible_to_survive = currentPlayer->possibleToSurvive(-amount_owned); // checks if the mortgage value of all of players buildings is > 150;
    
                                if (possible_to_survive) {
                                    bool enough_to_pay = false;
                                    
                                    while (!enough_to_pay) {
                                        currentPlayer->mortgageProperties();
    
                                        if (currentPlayer->getBalance() >= 150) {
                                            enough_to_pay = true;
                                        } else {
                                            std::cout << "Your current balance isn't enough to cover the Needles Hall fee. You need to mrtgage more properties." << std::endl;
                                        }
                                    }
    
                                    currentPlayer->changeBalance(amount_owned);
                                } else {
                                    currentPlayer->declareBankruptcy(nullptr, board, players);
                                    board.removePlayer(currentPlayer);
                                    std::cout << "You have declared bankrupcy!" << std::endl;
                                    players.erase(players.begin() + currentPlayerIndex);
                                    break;
                                }
                            }
                        }


                    } else if (curr_position == 10) { // DC TIMS LINE
                        std::cout << "You are visiting the DC Tims Line." << std::endl;

                    } else if (curr_position == 20) { // GOOSE NESTING 
                        std::cout << "You are being attacked by a flock of nesting geese! RUN!" << std::endl;

                    } else if (curr_position == 30) { // GO TO TIMS
                        currentPlayer->sendToTimsLine(board);
                        break;

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
                                currentPlayer->declareBankruptcy(nullptr, board, players);
                                std::cout << "You have declared bankrupcy!" << std::endl;
                                board.removePlayer(currentPlayer);
                                players.erase(players.begin() + currentPlayerIndex);
                                break;
                            }
                        }
                    }
                }

                action_done = true;
            }

            if (currentPlayer->isInTimsLine()) {

                std::string roll;
                std::cout << "You are in the DC Tims Line. You will attempt to roll doubles to get out of the DC Tims Line.";

                bool success = currentPlayer->tryToLeaveTimsLine();

                if (success) {
                    currentPlayer->leaveTimsLine();

                } else {
                    if (currentPlayer->getTurnsInTimsLine() <= 1) { // starts at 0 and player can be in jail for 3 rounds (up to 2)
                        std::string answer;
    
                        if (currentPlayer->getNumCups() > 0) { // player has RUR
                            std::cout << "Would you like to use one of your Roll Up the Rim Cups to leave the DC Tims Line? (Y/N): ";
                            std::cin >> answer;
                            
                            if (answer == "Y") {
                                currentPlayer->useCup();
                                currentPlayer->leaveTimsLine();
                                std::cout << "Transaction succesful, you are leaving the DC Tims Line.";
    
                            } else {
                                std::cout << "Would you like to pay $50 to exit the DC Tims Line? (Y/N): ";
                                std::cin >> answer;
    
                                if (answer == "Y") {
                                    bool transaction_successful = currentPlayer->changeBalance(-50);
    
                                    if (transaction_successful) {
                                        std::cout << "Transaction succesful, you are leaving the DC Tims Line.";
                                        currentPlayer->leaveTimsLine();
                                    } else {
                                        std::cout << "You don't have enough funds to leave the DC Tims Line";
                                        currentPlayer->incTurnsInTimsLine();
                                        break; // player will only be prompted to mortgage properties on the third round in jail
    
                                    }
                                } else {
                                    std::cout << "You will be spending another night in the DC Tims Line!" << std::endl;
                                    currentPlayer->incTurnsInTimsLine();
                                    break;
                                }
                            }
                        } else {

                            std::cout << "Would you like to pay $50 to exit the DC Tims Line? (Y/N): ";
                                std::cin >> answer;
    
                                if (answer == "Y") {
                                    bool transaction_successful = currentPlayer->changeBalance(-50);
    
                                    if (transaction_successful) {
                                        std::cout << "Transaction succesful, you are leaving the DC Tims Line.";
                                        currentPlayer->leaveTimsLine();
                                    } else {
                                        std::cout << "You don't have enough funds to leave the DC Tims Line";
                                        currentPlayer->incTurnsInTimsLine();
                                        break; // player will only be prompted to mortgage properties on the third round in jail
    
                                    }
                                } else {
                                    std::cout << "You will be spending another night in the DC Tims Line!" << std::endl;
                                    currentPlayer->incTurnsInTimsLine();
                                    break;
                                }

                        }
    
                    } else if (currentPlayer->getTurnsInTimsLine() == 2) {
                        std::string answer;
                        
                        if (currentPlayer->getNumCups() > 0) {
                            std::cout << "This is your last chance to get out of the DC Tims Line. Would you like to use your Roll up The Rum Cup?\n"
                            "Note that if you don't use it now and don't have enough funds to pay bail, you will have to declare bancrupcy. (Y/N): ";
                            std::cin >> answer;
                            
                            if (answer == "Y") {
                                currentPlayer->useCup();
                                currentPlayer->leaveTimsLine();
                                std::cout << "Transaction succesful, you are leaving the DC Tims Line." << std::endl;
                            } else {
                                if (currentPlayer->getBalance() < 50) {
                                    currentPlayer->declareBankruptcy(nullptr, board, players);
                                    board.removePlayer(currentPlayer);
                                    std::cout << "You have declared bankrupcy!" << std::endl;
                                    players.erase(players.begin() + currentPlayerIndex);
                                    break;
                                } else {
                                    currentPlayer->leaveTimsLine();
                                }
                            }
                        } else {
                            if (currentPlayer->getBalance() < 50) {
                                currentPlayer->declareBankruptcy(nullptr, board, players);
                                board.removePlayer(currentPlayer);
                                std::cout << "You have declared bankrupcy!" << std::endl;
                                players.erase(players.begin() + currentPlayerIndex);
                                break;
                            } else {
                                currentPlayer->leaveTimsLine();
                            }
                        }
                    }
                }


                

            } else {

                std::cout << "> ";
                std::cin >> command;

                if (command == "roll") {
                    if (!rolled) {
                        rolled = true;
                        std::tuple<int, int, int> roll = currentPlayer->roll(board);
                        int prevPos = std::get<0>(roll);
                        int die1 = std::get<1>(roll);
                        int die2 = std::get<2>(roll);
                        if (die1 == die2) {
                            std::cout << "You rolled doubles! You get to roll again.\n";
                            rolled = false;
                        }
                        board.getSquare(prevPos)->removePlayer(currentPlayer->shared_from_this());
                        board.getSquare(currentPlayer->getPosition())->addPlayer(currentPlayer->shared_from_this());
                        board.drawBoard();
                    } else {
                        std::cout << "You have already rolled this turn.\n";
                    }
                } else if (command == "move") {
                    std::string n;

                    std::cin >> n;
                    
                    if (isInteger(n)) {
                        int n_int = std::stoi(n);
                        int prevPos = currentPlayer->move(n_int, board);
                        board.getSquare(prevPos)->removePlayer(currentPlayer->shared_from_this());
                        board.getSquare(currentPlayer->getPosition())->addPlayer(currentPlayer->shared_from_this());
                        board.drawBoard();
                        std::cout << "Moved to " << board.getSquare(currentPlayer->getPosition())->getName() << std::endl;
                        rolled = true;
                    } else {
                        std::cout << n << " is not an integer.";
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
                        if (ac->numImprovements() == 0) {
                            ac->mortgage();
                            currentPlayer->changeBalance(ac->getCost() / 2);
                            std::cout << property << " has been mortgaged.\n";
                        } else {
                            std::cout << "Can't mortgage an Academic Building with improvements." << std::endl;
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
                    "> roll                        - Roll two dice and move forward.\n"
                    "> next                        - End your turn and pass to the next player.\n"
                    "> trade <name> <give> <receive> - Propose a trade with another player.\n"
                    "    (give/receive can be a property or an amount of money)\n"
                    "> improve <property> buy/sell - Buy or sell an improvement on a property.\n"
                    "> mortgage <property>         - Mortgage a property.\n"
                    "> unmortgage <property>       - Unmortgage a property.\n"
                    "> bankrupt                    - Declare bankruptcy (only when required).\n"
                    "> assets                      - Show current player’s assets.\n"
                    "> all                         - Show all players’ assets.\n"
                    "> save <filename>             - Save the current game state.\n"
                    "> help                        - Show this help message.\n\n"
                    "Note: Properties with improvements cannot be traded or mortgaged.\n"
                    << std::endl;
                } else if (command == "trade") {
                    std::string name;
                    std::string give;
                    std::string receive;

                    std::cin >> name;
                    std::cin >> give;
                    std::cin >> receive;

                    bool giveInt = isInteger(give);
                    bool receiveInt = isInteger(receive);

                    if (giveInt && receiveInt) { // if both give and receive are integers, doesn't work
                        std::cout << "\n Unable to trade money for money, try again." << std::endl;
                    } else {

                        std::cout << "\nDoes " << name << " accept this trade? (Y/N): ";
                        std::string decision;
        
                        std::cin >> decision;
        
                        if (decision == "Y") {
                            if (!giveInt && !receiveInt) { // trade property for property                     
                                Ownable* give_ptr = board.findOwnableByName(give);
                                Ownable* receive_ptr = board.findOwnableByName(receive);
                                std::shared_ptr<Player> player_trade = board.findPlayerByName(name);
                                
                                if (give_ptr && receive_ptr && player_trade) {
                                    bool trade_success = currentPlayer->tradePforP(player_trade, give_ptr, receive_ptr);
                                    if (trade_success) {
                                        std::cout << "Trade successful!" << std::endl;
                                    } else {
                                        std::cout << "Trade failed. Try again." << std::endl;
                                    }
                                } else {
                                    std::cout << "Player or one of the squares do not exist" << std::endl;
                                }

                                
                            } else if (!giveInt && receiveInt) { // trade property for money
                                int money_receive = std::stoi(receive);
                                Ownable* give_ptr = board.findOwnableByName(give);
                                std::shared_ptr<Player> player_trade = board.findPlayerByName(name);
                                
                                if (give_ptr && player_trade) {
                                    bool trade_success = currentPlayer->tradePforC(player_trade, give_ptr, money_receive);
                                    if (trade_success) {
                                        std::cout << "Trade successful!" << std::endl;
                                    } else {
                                        std::cout << "Trade failed. Try again." << std::endl;
                                    }
                                } else {
                                    std::cout << "Trade failed. Try again." << std::endl;
                                }

                            } else if (giveInt && !receiveInt) { // trade money for property
                                int money_give = std::stoi(give);
                                Ownable* receive_ptr = board.findOwnableByName(receive);
                                std::shared_ptr<Player> player_trade = board.findPlayerByName(name);

                                if (receive_ptr && player_trade) {
                                    bool trade_success = currentPlayer->tradeCforP(player_trade, money_give, receive_ptr);
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
                    
                } else if (command == "save") {
                    std::string filename;
                    std::cin >> filename;
                    std::ofstream out(filename);
                    board.saveState(out);
                } else if (command == "load") {
                    std::string filename;
                    std::cin >> filename;
                    std::ifstream in(filename);
                    board.loadState(in, players);
                } else if (command == "bankrupt") {
                    currentPlayer->declareBankruptcyToBank(board, players);
                
                    board.removePlayer(currentPlayer);
                    players.erase(players.begin() + currentPlayerIndex);
                    if (players.size() == 1) {
                        std::cout << players[0]->getName() << " wins the game!\n";
                        break;
                    }
                    continue;
                } else if (command == "money") {
                    int amount;
                    std::cin >> amount;

                    currentPlayer->changeBalance(amount);
                } else {
                    std::cout << "Unknown command. Try again." << std::endl;
                }
            }
        }
        
        currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
    }

    std::cout << players[0]->getName() << " wins the game!\n";
}
