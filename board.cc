#include <iostream>
#include "board.h"
#include "square.h"
#include "academicbuilding.h"
#include "residence.h"
#include "gym.h"

using namespace std;

Board::Board() {
    squares.emplace_back(std::make_unique<Square>(0, "Collect OSAP"));
    squares.emplace_back(std::make_unique<AcademicBuilding>("AL", 1, 40, "Arts1", 50, vector<int>{2, 10, 30, 90, 160, 250}));
    squares.emplace_back(std::make_unique<Square>(2, "SLC"));
    squares.emplace_back(std::make_unique<AcademicBuilding>("ML", 3, 60, "Arts1", 50, vector<int>{4, 20, 60, 180, 320, 450}));
    squares.emplace_back(std::make_unique<Square>(4, "TUITION"));
    squares.emplace_back(std::make_unique<Residence>("MKV", 5, 200));
    squares.emplace_back(std::make_unique<AcademicBuilding>("ECH", 6, 100, "Arts2", 50, vector<int>{6, 30, 90, 270, 400, 550}));
    squares.emplace_back(std::make_unique<Square>(7, "NEEDLES HALL"));
    squares.emplace_back(std::make_unique<AcademicBuilding>("PAS", 8, 100, "Arts2", 50, vector<int>{6, 30, 90, 270, 400, 550}));
    squares.emplace_back(std::make_unique<AcademicBuilding>("HH", 9, 120, "Arts2", 50, vector<int>{8, 40, 100, 300, 450, 600}));
    squares.emplace_back(std::make_unique<Square>(10, "DC Tims Line"));
    squares.emplace_back(std::make_unique<AcademicBuilding>("RCH", 11, 140, "Eng", 100, vector<int>{10, 50, 150, 450, 625, 750}));
    squares.emplace_back(std::make_unique<Gym>("PAC", 12, 150));
    squares.emplace_back(std::make_unique<AcademicBuilding>("DWE", 13, 140, "Eng", 100, vector<int>{10, 50, 150, 450, 625, 750}));
    squares.emplace_back(std::make_unique<AcademicBuilding>("CPH", 14, 160, "Eng", 100, vector<int>{12, 60, 180, 500, 700, 900}));
    squares.emplace_back(std::make_unique<Residence>("UWP", 15, 200));
    squares.emplace_back(std::make_unique<AcademicBuilding>("LHI", 16, 180, "Health", 100, vector<int>{14, 70, 200, 550, 750, 950}));
    squares.emplace_back(std::make_unique<Square>(17, "SLC"));
    squares.emplace_back(std::make_unique<AcademicBuilding>("BMH", 18, 180, "Health", 100, vector<int>{14, 70, 200, 550, 750, 950}));
    squares.emplace_back(std::make_unique<AcademicBuilding>("OPT", 19, 200, "Health", 100, vector<int>{16, 80, 220, 600, 800, 1000}));
    squares.emplace_back(std::make_unique<Square>(20, "Goose Nesting"));
    squares.emplace_back(std::make_unique<AcademicBuilding>("EV1", 21, 220, "Env", 150, vector<int>{18, 90, 250, 700, 875, 1050}));
    squares.emplace_back(std::make_unique<Square>(22, "NEEDLES HALL"));
    squares.emplace_back(std::make_unique<AcademicBuilding>("EV2", 23, 220, "Env", 150, vector<int>{18, 90, 250, 700, 875, 1050}));
    squares.emplace_back(std::make_unique<AcademicBuilding>("EV3", 24, 240, "Env", 150, vector<int>{20, 100, 300, 750, 925, 1100}));
    squares.emplace_back(std::make_unique<Residence>("V1", 25, 200));
    squares.emplace_back(std::make_unique<AcademicBuilding>("PHYS", 26, 260, "Sci1", 150, vector<int>{22, 110, 330, 800, 975, 1150}));
    squares.emplace_back(std::make_unique<AcademicBuilding>("B1", 27, 260, "Sci1", 150, vector<int>{22, 110, 330, 800, 975, 1150}));
    squares.emplace_back(std::make_unique<Gym>("CIF", 28, 150));
    squares.emplace_back(std::make_unique<AcademicBuilding>("B2", 29, 280, "Sci1", 150, vector<int>{24, 120, 360, 850, 1025, 1200}));
    squares.emplace_back(std::make_unique<Square>(30, "GO TO TIMS"));
    squares.emplace_back(std::make_unique<AcademicBuilding>("EIT", 31, 300, "Sci2", 200, vector<int>{26, 130, 390, 900, 1100, 1275}));
    squares.emplace_back(std::make_unique<AcademicBuilding>("ESC", 32, 300, "Sci2", 200, vector<int>{26, 130, 390, 900, 1100, 1275}));
    squares.emplace_back(std::make_unique<Square>(33, "SLC"));
    squares.emplace_back(std::make_unique<AcademicBuilding>("C2", 34, 320, "Sci2", 200, vector<int>{28, 150, 450, 1000, 1200, 1400}));
    squares.emplace_back(std::make_unique<Residence>("REV", 35, 200));
    squares.emplace_back(std::make_unique<Square>(36, "NEEDLES HALL"));
    squares.emplace_back(std::make_unique<AcademicBuilding>("MC", 37, 350, "Math", 200, vector<int>{35, 175, 500, 1100, 1300, 1500}));
    squares.emplace_back(std::make_unique<Square>(38, "COOP FEE"));
    squares.emplace_back(std::make_unique<AcademicBuilding>("DC", 39, 400, "Math", 200, vector<int>{50, 200, 600, 1400, 1700, 2000}));
}

void Board::addPlayer(std::shared_ptr<Player> player) {
    players.emplace_back(player);
}

Square* Board::getSquare(int position) const {
    return squares.at(position).get();
}

void Board::drawBoard() const {
    cout << "_________________________________________________________________________________________" << endl;
    cout << "|Goose  |       |NEEDLES|       |       |V1     |       |       |CIF    |       |GO TO  |" << endl;
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
    cout << "|       |                                                                       |       |" << endl;
    cout << "|-------|                                                                       |-------|" << endl;
    cout << "|OPT    |                                                                       |EIT    |" << endl;
    cout << "|";
    this->getSquare(19)->drawPlayers();
    cout << "|                                                                       |";
    this->getSquare(31)->drawPlayers();
    cout << "|" << endl;
    cout << "|_______|                                                                       |_______|" << endl;
    cout << "|       |                                                                       |       |" << endl;
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
    cout << "|       |                                                                       |       |" << endl;
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
    cout << "|       |            |_____________________________________________|            |NEEDLES|" << endl;
    cout << "|-------|                                                                       |HALL   |" << endl;
    cout << "|CPH    |                                                                       |       |" << endl;
    cout << "|";
    this->getSquare(14)->drawPlayers();
    cout << "|                                                                       |";
    this->getSquare(35)->drawPlayers();
    cout << "|" << endl;
    cout << "|_______|                                                                       |_______|" << endl;
    cout << "|       |                                                                       |       |" << endl;
    cout << "|-------|                                                                       |-------|" << endl;
    cout << "|DWE    |                                                                       |MC     |" << endl;
    cout << "|";
    this->getSquare(13)->drawPlayers();
    cout << "|                                                                       |";
    this->getSquare(36)->drawPlayers();
    cout << "|" << endl;
    cout << "|_______|                                                                       |_______|" << endl;
    cout << "|PAC    |                                                                       |COOP   |" << endl;
    cout << "|       |                                                                       |FEE    |" << endl;
    cout << "|";
    this->getSquare(12)->drawPlayers();
    cout << "|                                                                       |";
    this->getSquare(37)->drawPlayers();
    cout << "|" << endl;
    cout << "|";
    this->getSquare(11)->drawPlayers();
    cout << "|                                                                       |";
    this->getSquare(38)->drawPlayers();
    cout << "|" << endl;
    cout << "|_______|                                                                       |_______|" << endl;
    cout << "|       |                                                                       |       |" << endl;
    cout << "|-------|                                                                       |-------|" << endl;
    cout << "|RCH    |                                                                       |DC     |" << endl;
    cout << "|";
    this->getSquare(10)->drawPlayers();
    cout << "|                                                                       |";
    this->getSquare(39)->drawPlayers();
    cout << "|" << endl;
    cout << "|_______|_______________________________________________________________________|_______|" << endl;
    cout << "|DC Tims|       |       |NEEDLES|       |MKV    |TUITION|       |SLC    |       |COLLECT|" << endl;
    cout << "|Line   |-------|-------|HALL   |-------|       |       |-------|       |-------|OSAP   |" << endl;
    cout << "|       |HH     |PAS    |       |ECH    |       |       |ML     |       |AL     |       |" << endl;
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
