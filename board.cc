#include <iostream>
#include <map>
#include "academicbuilding.h"
#include "board.h"
#include "gym.h"
#include "nonownable.h"
#include "residence.h"
#include "square.h"

using namespace std;

Board::Board() {
    squares.emplace_back(std::make_unique<NonOwnable>(0, "Collect OSAP"));
    squares.emplace_back(std::make_unique<AcademicBuilding>("AL", 1, 40, "Arts1", 50, vector<int>{2, 10, 30, 90, 160, 250}));
    squares.emplace_back(std::make_unique<NonOwnable>(2, "SLC"));
    squares.emplace_back(std::make_unique<AcademicBuilding>("ML", 3, 60, "Arts1", 50, vector<int>{4, 20, 60, 180, 320, 450}));
    squares.emplace_back(std::make_unique<NonOwnable>(4, "TUITION"));
    squares.emplace_back(std::make_unique<Residence>("MKV", 5, 200));
    squares.emplace_back(std::make_unique<AcademicBuilding>("ECH", 6, 100, "Arts2", 50, vector<int>{6, 30, 90, 270, 400, 550}));
    squares.emplace_back(std::make_unique<NonOwnable>(7, "NEEDLES HALL"));
    squares.emplace_back(std::make_unique<AcademicBuilding>("PAS", 8, 100, "Arts2", 50, vector<int>{6, 30, 90, 270, 400, 550}));
    squares.emplace_back(std::make_unique<AcademicBuilding>("HH", 9, 120, "Arts2", 50, vector<int>{8, 40, 100, 300, 450, 600}));
    squares.emplace_back(std::make_unique<NonOwnable>(10, "DC Tims Line"));
    squares.emplace_back(std::make_unique<AcademicBuilding>("RCH", 11, 140, "Eng", 100, vector<int>{10, 50, 150, 450, 625, 750}));
    squares.emplace_back(std::make_unique<Gym>("PAC", 12, 150));
    squares.emplace_back(std::make_unique<AcademicBuilding>("DWE", 13, 140, "Eng", 100, vector<int>{10, 50, 150, 450, 625, 750}));
    squares.emplace_back(std::make_unique<AcademicBuilding>("CPH", 14, 160, "Eng", 100, vector<int>{12, 60, 180, 500, 700, 900}));
    squares.emplace_back(std::make_unique<Residence>("UWP", 15, 200));
    squares.emplace_back(std::make_unique<AcademicBuilding>("LHI", 16, 180, "Health", 100, vector<int>{14, 70, 200, 550, 750, 950}));
    squares.emplace_back(std::make_unique<NonOwnable>(17, "SLC"));
    squares.emplace_back(std::make_unique<AcademicBuilding>("BMH", 18, 180, "Health", 100, vector<int>{14, 70, 200, 550, 750, 950}));
    squares.emplace_back(std::make_unique<AcademicBuilding>("OPT", 19, 200, "Health", 100, vector<int>{16, 80, 220, 600, 800, 1000}));
    squares.emplace_back(std::make_unique<NonOwnable>(20, "Goose Nesting"));
    squares.emplace_back(std::make_unique<AcademicBuilding>("EV1", 21, 220, "Env", 150, vector<int>{18, 90, 250, 700, 875, 1050}));
    squares.emplace_back(std::make_unique<NonOwnable>(22, "NEEDLES HALL"));
    squares.emplace_back(std::make_unique<AcademicBuilding>("EV2", 23, 220, "Env", 150, vector<int>{18, 90, 250, 700, 875, 1050}));
    squares.emplace_back(std::make_unique<AcademicBuilding>("EV3", 24, 240, "Env", 150, vector<int>{20, 100, 300, 750, 925, 1100}));
    squares.emplace_back(std::make_unique<Residence>("V1", 25, 200));
    squares.emplace_back(std::make_unique<AcademicBuilding>("PHYS", 26, 260, "Sci1", 150, vector<int>{22, 110, 330, 800, 975, 1150}));
    squares.emplace_back(std::make_unique<AcademicBuilding>("B1", 27, 260, "Sci1", 150, vector<int>{22, 110, 330, 800, 975, 1150}));
    squares.emplace_back(std::make_unique<Gym>("CIF", 28, 150));
    squares.emplace_back(std::make_unique<AcademicBuilding>("B2", 29, 280, "Sci1", 150, vector<int>{24, 120, 360, 850, 1025, 1200}));
    squares.emplace_back(std::make_unique<NonOwnable>(30, "GO TO TIMS"));
    squares.emplace_back(std::make_unique<AcademicBuilding>("EIT", 31, 300, "Sci2", 200, vector<int>{26, 130, 390, 900, 1100, 1275}));
    squares.emplace_back(std::make_unique<AcademicBuilding>("ESC", 32, 300, "Sci2", 200, vector<int>{26, 130, 390, 900, 1100, 1275}));
    squares.emplace_back(std::make_unique<NonOwnable>(33, "SLC"));
    squares.emplace_back(std::make_unique<AcademicBuilding>("C2", 34, 320, "Sci2", 200, vector<int>{28, 150, 450, 1000, 1200, 1400}));
    squares.emplace_back(std::make_unique<Residence>("REV", 35, 200));
    squares.emplace_back(std::make_unique<NonOwnable>(36, "NEEDLES HALL"));
    squares.emplace_back(std::make_unique<AcademicBuilding>("MC", 37, 350, "Math", 200, vector<int>{35, 175, 500, 1100, 1300, 1500}));
    squares.emplace_back(std::make_unique<NonOwnable>(38, "COOP FEE"));
    squares.emplace_back(std::make_unique<AcademicBuilding>("DC", 39, 400, "Math", 200, vector<int>{50, 200, 600, 1400, 1700, 2000}));
}

void Board::saveState(std::ostream& out) const {
    out << players.size() << "\n";
    for (auto& p : players) {
        p->saveState(out);
    }
    for (auto& square : squares) {
        if (auto ownable = dynamic_cast<Ownable*>(square.get())) {
            out << ownable->getName() << " ";
            if (ownable->getOwner()) {
                out << ownable->getOwner()->getName();
            } else {
                out << "BANK";
            }
            int imp = ownable->isMortgaged() ? -1 : dynamic_cast<AcademicBuilding*>(ownable)->numImprovements();
            out << " " << imp << "\n";
        }
    }
}

void Board::loadState(std::istream& in, std::vector<std::shared_ptr<Player>>& players) {
    int numPlayers;
    in >> numPlayers;

    players.clear();
    std::string name;
    char symbol;
    int cups, money, position;
    int timsTurns = 0;

    // Load players
    for (int i = 0; i < numPlayers; ++i) {
        in >> name >> symbol >> cups >> money >> position;

        auto player = std::make_shared<Player>(name, symbol);
        player->changeBalance(money-1500);
        player->changePosition(position);
        player->setCups(cups);

        if (position == 10) {
            // Check if in DC Tims Line
            int lineFlag;
            in >> lineFlag;
            if (lineFlag == 1) {
                in >> timsTurns;
                player->sendToTimsLine();
                player->setTurnsInTimsLine(timsTurns);
            }
        }

        players.emplace_back(player);
        addPlayer(player);
        getSquare(position)->addPlayer(player);
    }

    // Load properties
    std::string propertyName;
    while (in >> propertyName) {
        std::string ownerName;
        int improvements;
        in >> ownerName >> improvements;

        Square* square = getSquareByName(propertyName);
        Ownable* ownable = dynamic_cast<Ownable*>(square);

        if (!ownable) {
            std::cerr << "Error: Property " << propertyName << " is not ownable.\n";
            continue;
        }

        if (ownerName != "BANK") {
            for (auto& p : players) {
                if (p->getName() == ownerName) {
                    ownable->changeOwner(p.get());
                    p->addProperty(ownable);
                    break;
                }
            }
        }

        if (improvements == -1) {
            ownable->mortgage();
        } else if (improvements > 0) {
            auto ac = dynamic_cast<AcademicBuilding*>(ownable);
            if (ac) {
                for (int i = 0; i < improvements; ++i) {
                    ac->improve(ac->getOwner());
                }
            }
        }
    }

    std::cout << "Game loaded successfully.\n";
}

void Board::addPlayer(std::shared_ptr<Player> player) {
    players.emplace_back(player);
}

void Board::removePlayer(std::shared_ptr<Player> player) {
    for (size_t i = 0; i < players.size(); ++i) {
        if (players[i] == player) {
            players.erase(players.begin() + i);
            return;
        }
    }
}

Square* Board::getSquare(int position) const {
    if (position < 0 || position >= 40) {
        position = position % 40;
    }
    return squares.at(position).get();
}

Square* Board::getSquareByName(const std::string& name) const {
    for (const auto& square : squares) {
        if (square->getName() == name) {
            return square.get();
        }
    }
    return nullptr;
}

void Board::drawBoard() const {
    cout << "_________________________________________________________________________________________" << endl;
    cout << "|Goose  | ";
    dynamic_cast<AcademicBuilding*>(this->getSquare(21))->drawImprovements();
    cout << " |NEEDLES| ";
    dynamic_cast<AcademicBuilding*>(this->getSquare(23))->drawImprovements();
    cout << " | ";
    dynamic_cast<AcademicBuilding*>(this->getSquare(24))->drawImprovements();
    cout << " |V1     | ";
    dynamic_cast<AcademicBuilding*>(this->getSquare(26))->drawImprovements();
    cout << " | ";
    dynamic_cast<AcademicBuilding*>(this->getSquare(27))->drawImprovements();
    cout << " |CIF    | ";
    dynamic_cast<AcademicBuilding*>(this->getSquare(29))->drawImprovements();
    cout << " |GO TO  |" << endl;
    cout << "|Nesting|-------|HALL   |-------|-------|       |-------|-------|       |-------|TIMS   |" << endl;
    cout << "|       |EV1    |       |EV2    |EV3    |       |PHYS   |B1     |       |B2     |       |" << endl;
    cout << "|";
    this->getSquare(20)->drawPlayers();
    cout << "|";
    this->getSquare(21)->drawPlayers();
    cout << "|";
    this->getSquare(22)->drawPlayers();
    cout << "|";
    this->getSquare(23)->drawPlayers();
    cout << "|";
    this->getSquare(24)->drawPlayers();
    cout << "|";
    this->getSquare(25)->drawPlayers();
    cout << "|";
    this->getSquare(26)->drawPlayers();
    cout << "|";
    this->getSquare(27)->drawPlayers();
    cout << "|";
    this->getSquare(28)->drawPlayers();
    cout << "|";
    this->getSquare(29)->drawPlayers();
    cout << "|";
    this->getSquare(30)->drawPlayers();
    cout << "|" << endl;
    cout << "|_______|_______|_______|_______|_______|_______|_______|_______|_______|_______|_______|" << endl;
    cout << "| ";
    dynamic_cast<AcademicBuilding*>(this->getSquare(19))->drawImprovements();
    cout << " |                                                                       | ";
    dynamic_cast<AcademicBuilding*>(this->getSquare(31))->drawImprovements();
    cout << " |" << endl;
    cout << "|-------|                                                                       |-------|" << endl;
    cout << "|OPT    |                                                                       |EIT    |" << endl;
    cout << "|";
    this->getSquare(19)->drawPlayers();
    cout << "|                                                                       |";
    this->getSquare(31)->drawPlayers();
    cout << "|" << endl;
    cout << "|_______|                                                                       |_______|" << endl;
    cout << "| ";
    dynamic_cast<AcademicBuilding*>(this->getSquare(18))->drawImprovements();
    cout << " |                                                                       | ";
    dynamic_cast<AcademicBuilding*>(this->getSquare(32))->drawImprovements();
    cout << " |" << endl;
    cout << "|-------|                                                                       |-------|" << endl;
    cout << "|BMH    |                                                                       |ESC    |" << endl;
    cout << "|";
    this->getSquare(18)->drawPlayers();
    cout << "|                                                                       |";
    this->getSquare(32)->drawPlayers();
    cout << "|" << endl;
    cout << "|_______|                                                                       |_______|" << endl;
    cout << "|SLC    |                                                                       |SLC    |" << endl;
    cout << "|       |                                                                       |       |" << endl;
    cout << "|       |                                                                       |       |" << endl;
    cout << "|";
    this->getSquare(17)->drawPlayers();
    cout << "|                                                                       |";
    this->getSquare(33)->drawPlayers();
    cout << "|" << endl;
    cout << "|_______|                                                                       |_______|" << endl;
    cout << "| ";
    dynamic_cast<AcademicBuilding*>(this->getSquare(16))->drawImprovements();
    cout << " |                                                                       | ";
    dynamic_cast<AcademicBuilding*>(this->getSquare(34))->drawImprovements();
    cout << " |" << endl;
    cout << "|-------|                                                                       |-------|" << endl;
    cout << "|LHI    |                                                                       |C2     |" << endl;
    cout << "|";
    this->getSquare(16)->drawPlayers();
    cout << "|             _____________________________________________             |";
    this->getSquare(34)->drawPlayers();
    cout << "|" << endl;
    cout << "|_______|            |                                             |            |_______|" << endl;
    cout << "|UWP    |            | #   #  ##  #####  ###  ###   ###  #   #   # |            |REV    |" << endl;
    cout << "|       |            | #   # #  #   #   #   # #  # #   # #   #   # |            |       |" << endl;
    cout << "|       |            | # # # ####   #   #   # ###  #   # #    # #  |            |       |" << endl;
    cout << "|";
    this->getSquare(15)->drawPlayers();
    cout << "|            | # # # #  #   #   #   # #    #   # #     #   |            |";
    this->getSquare(35)->drawPlayers();
    cout << "|" << endl;
    cout << "|_______|            | ##### #  #   #    ###  #     ###  ## #  #   |            |_______|" << endl;
    cout << "| ";
    dynamic_cast<AcademicBuilding*>(this->getSquare(14))->drawImprovements();
    cout << " |            |_____________________________________________|            |NEEDLES|" << endl;
    cout << "|-------|                                                                       |HALL   |" << endl;
    cout << "|CPH    |                                                                       |       |" << endl;
    cout << "|";
    this->getSquare(14)->drawPlayers();
    cout << "|                                                                       |";
    this->getSquare(36)->drawPlayers();
    cout << "|" << endl;
    cout << "|_______|                                                                       |_______|" << endl;
    cout << "| ";
    dynamic_cast<AcademicBuilding*>(this->getSquare(13))->drawImprovements();
    cout << " |                                                                       | ";
    dynamic_cast<AcademicBuilding*>(this->getSquare(37))->drawImprovements();
    cout << " |" << endl;
    cout << "|-------|                                                                       |-------|" << endl;
    cout << "|DWE    |                                                                       |MC     |" << endl;
    cout << "|";
    this->getSquare(13)->drawPlayers();
    cout << "|                                                                       |";
    this->getSquare(37)->drawPlayers();
    cout << "|" << endl;
    cout << "|_______|                                                                       |_______|" << endl;
    cout << "|PAC    |                                                                       |COOP   |" << endl;
    cout << "|       |                                                                       |FEE    |" << endl;
    cout << "|       |                                                                       |       |" << endl;
    cout << "|";
    this->getSquare(12)->drawPlayers();
    cout << "|                                                                       |";
    this->getSquare(38)->drawPlayers();
    cout << "|" << endl;
    cout << "|_______|                                                                       |_______|" << endl;
    cout << "| ";
    dynamic_cast<AcademicBuilding*>(this->getSquare(11))->drawImprovements();
    cout << " |                                                                       | ";
    dynamic_cast<AcademicBuilding*>(this->getSquare(39))->drawImprovements();
    cout << " |" << endl;
    cout << "|-------|                                                                       |-------|" << endl;
    cout << "|RCH    |                                                                       |DC     |" << endl;
    cout << "|";
    this->getSquare(11)->drawPlayers();
    cout << "|                                                                       |";
    this->getSquare(39)->drawPlayers();
    cout << "|" << endl;
    cout << "|_______|_______________________________________________________________________|_______|" << endl;
    cout << "|DC Tims| ";
    dynamic_cast<AcademicBuilding*>(this->getSquare(9))->drawImprovements();
    cout << " | ";
    dynamic_cast<AcademicBuilding*>(this->getSquare(8))->drawImprovements();
    cout << " |NEEDLES| ";
    dynamic_cast<AcademicBuilding*>(this->getSquare(6))->drawImprovements();
    cout << " |MKV    |TUITION| ";
    dynamic_cast<AcademicBuilding*>(this->getSquare(3))->drawImprovements();
    cout << " |SLC    | ";
    dynamic_cast<AcademicBuilding*>(this->getSquare(1))->drawImprovements();
    cout << " |COLLECT|" << endl;
    cout << "|Line   |-------|-------|HALL   |-------|       |       |-------|       |-------|OSAP   |" << endl;
    cout << "|       |HH     |PAS    |       |ECH    |       |       |ML     |       |AL     |       |" << endl;
    cout << "|";
    this->getSquare(10)->drawPlayers();
    cout << "|";
    this->getSquare(9)->drawPlayers();
    cout << "|";
    this->getSquare(8)->drawPlayers();
    cout << "|";
    this->getSquare(7)->drawPlayers();
    cout << "|";
    this->getSquare(6)->drawPlayers();
    cout << "|";
    this->getSquare(5)->drawPlayers();
    cout << "|";
    this->getSquare(4)->drawPlayers();
    cout << "|";
    this->getSquare(3)->drawPlayers();
    cout << "|";
    this->getSquare(2)->drawPlayers();
    cout << "|";
    this->getSquare(1)->drawPlayers();
    cout << "|";
    this->getSquare(0)->drawPlayers();
    cout << "|" << endl;
    cout << "|_______|_______|_______|_______|_______|_______|_______|_______|_______|_______|_______|" << endl;
}

std::vector<std::unique_ptr<Square>>& Board::getSquares() {
    return squares;
}

Ownable* Board::findOwnableByName(std::string name) {
    for (auto &square : squares) {
        Ownable* ownable = dynamic_cast<Ownable*>(square.get());
        if (ownable && ownable->getName() == name) {
            return ownable;
        }
    }
    return nullptr;
}

std::shared_ptr<Player> Board::findPlayerByName(std::string name) {
    for (auto &player : players) {
        if (player->getName() == name) {
            return player;
        }
    }
    return nullptr;
}

void Board::movePlayer(shared_ptr<Player> player, int n) {
    int prevPos = player->move(n, *this);
    getSquare(prevPos)->removePlayer(player->shared_from_this());
    getSquare(player->getPosition())->addPlayer(player->shared_from_this());
    drawBoard();
}

void Board::startAuction(std::shared_ptr<Ownable> property, std::vector<std::shared_ptr<Player>>& players) {
    std::map<std::string, bool> activeBidders;
    for (auto& player : players) {
        if (player->isBankrupt()) continue;
        activeBidders[player->getName()] = true;
    }

    int currentBid = 0;
    std::shared_ptr<Player> highestBidder = nullptr;

    while (true) {
        for (auto& player : players) {
            if (!activeBidders[player->getName()] || player->isBankrupt()) continue;

            std::cout << player->getName() << "'s turn to bid (current bid: $" << currentBid << "). Enter bid or 'withdraw': ";
            std::string input;
            std::cin >> input;

            if (input == "withdraw") {
                activeBidders[player->getName()] = false;
                continue;
            }

            int bid = std::stoi(input);
            if (bid > currentBid && bid <= player->getBalance()) {
                currentBid = bid;
                highestBidder = player;
            } else {
                std::cout << "Invalid bid. Must be greater than $" << currentBid << " and <= your current money.\n";
            }
        }

        // Check how many active bidders are left
        int remaining = 0;
        for (auto& [_, active] : activeBidders) if (active) ++remaining;
        if (remaining <= 1) break;
    }

    if (highestBidder) {
        std::cout << highestBidder->getName() << " wins the auction and buys " << property->getName() << " for $" << currentBid << "!\n";
        highestBidder->changeBalance(-currentBid);
        property->changeOwner(highestBidder.get());
        highestBidder->addProperty(property.get());
    } else {
        std::cout << "No one bought " << property->getName() << ". It remains with the Bank.\n";
    }
}

void Board::returnCups(int num) {
    cupsAvailable += num;
    if (cupsAvailable > 4) cupsAvailable = 4;
}

bool Board::canGiveCup() const {
    return cupsAvailable > 0;
}

void Board::giveCup(std::shared_ptr<Player> p) {
    if (cupsAvailable > 0) {
        p->setCups(p->getNumCups() + 1);
        --cupsAvailable;
    }
}
