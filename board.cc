#include <iostream>
#include "board.h"
#include "square.h"
#include "academicbuilding.h"

using namespace std;

Board::Board() {
    squares.emplace_back(std::make_unique<AcademicBuilding>("AL", 1, 40, "Arts1", 50));
    squares.emplace_back(std::make_unique<AcademicBuilding>("ML", 3, 60, "Arts1", 50));
    squares.emplace_back(std::make_unique<AcademicBuilding>("ECH", 6, 100, "Arts2", 50));
    squares.emplace_back(std::make_unique<AcademicBuilding>("PAS", 8, 100, "Arts2", 50));
    squares.emplace_back(std::make_unique<AcademicBuilding>("HH", 9, 120, "Arts2", 50));
    squares.emplace_back(std::make_unique<AcademicBuilding>("RCH", 11, 140, "Eng", 100));
    squares.emplace_back(std::make_unique<AcademicBuilding>("DWE", 13, 140, "Eng", 100));
    squares.emplace_back(std::make_unique<AcademicBuilding>("CPH", 14, 160, "Eng", 100));
    squares.emplace_back(std::make_unique<AcademicBuilding>("LHI", 16, 180, "Health", 100));
    squares.emplace_back(std::make_unique<AcademicBuilding>("BMH", 18, 180, "Health", 100));
    squares.emplace_back(std::make_unique<AcademicBuilding>("OPT", 19, 200, "Health", 100));
    squares.emplace_back(std::make_unique<AcademicBuilding>("EV1", 21, 220, "Env", 150));
    squares.emplace_back(std::make_unique<AcademicBuilding>("EV2", 23, 220, "Env", 150));
    squares.emplace_back(std::make_unique<AcademicBuilding>("EV3", 24, 240, "Env", 150));
    squares.emplace_back(std::make_unique<AcademicBuilding>("PHYS", 26, 260, "Sci1", 150));
    squares.emplace_back(std::make_unique<AcademicBuilding>("B1", 27, 260, "Sci1", 150));
    squares.emplace_back(std::make_unique<AcademicBuilding>("B2", 29, 280, "Sci1", 150));
    squares.emplace_back(std::make_unique<AcademicBuilding>("EIT", 31, 300, "Sci2", 200));
    squares.emplace_back(std::make_unique<AcademicBuilding>("ESC", 32, 300, "Sci2", 200));
    squares.emplace_back(std::make_unique<AcademicBuilding>("C2", 34, 320, "Sci2", 200));
    squares.emplace_back(std::make_unique<AcademicBuilding>("MC", 37, 350, "Math", 200));
    squares.emplace_back(std::make_unique<AcademicBuilding>("DC", 39, 400, "Math", 200));
}

void Board::addPlayer(std::shared_ptr<Player> player) {
    players.emplace_back(player);
}

std::shared_ptr<Square> Board::getSquare(int position) const {
    return squares.at(position);
}

int Board::numSquares() const {
    return squares.size();
}

void Board::drawBoard() const {
    cout << "_________________________________________________________________________________________" << endl;
    cout << "|Goose  |       |NEEDLES|       |       |V1     |       |       |CIF    |       |GO TO  |" << endl;
    cout << "|Nesting|-------|HALL   |-------|-------|       |-------|-------|       |-------|TIMS   |" << endl;
    cout << "|       |EV1    |       |EV2    |EV3    |       |PHYS   |B1     |       |B2     |       |" << endl;
    cout << "|       |       |       |       |       |       |       |       |       |       |       |" << endl;
    cout << "|_______|_______|_______|_______|_______|_______|_______|_______|_______|_______|_______|" << endl;
    cout << "|       |                                                                       |       |" << endl;
    cout << "|-------|                                                                       |-------|" << endl;
    cout << "|OPT    |                                                                       |EIT    |" << endl;
    cout << "|       |                                                                       |       |" << endl;
    cout << "|_______|                                                                       |_______|" << endl;
    cout << "|       |                                                                       |       |" << endl;
    cout << "|-------|                                                                       |-------|" << endl;
    cout << "|BMH    |                                                                       |ESC    |" << endl;
    cout << "|       |                                                                       |       |" << endl;
    cout << "|_______|                                                                       |_______|" << endl;
    cout << "|SLC    |                                                                       |SLC    |" << endl;
    cout << "|       |                                                                       |       |" << endl;
    cout << "|       |                                                                       |       |" << endl;
    cout << "|       |                                                                       |       |" << endl;
    cout << "|_______|                                                                       |_______|" << endl;
    cout << "|       |                                                                       |       |" << endl;
    cout << "|-------|                                                                       |-------|" << endl;
    cout << "|LHI    |                                                                       |C2     |" << endl;
    cout << "|       |             _____________________________________________             |       |" << endl;
    cout << "|_______|            |                                             |            |_______|" << endl;
    cout << "|UWP    |            | #   #  ##  #####  ###  ###   ###  #   #   # |            |REV    |" << endl;
    cout << "|       |            | #   # #  #   #   #   # #  # #   # #   #   # |            |       |" << endl;
    cout << "|       |            | # # # ####   #   #   # ###  #   # #    # #  |            |       |" << endl;
    cout << "|       |            | # # # #  #   #   #   # #    #   # #     #   |            |       |" << endl;
    cout << "|_______|            | ##### #  #   #    ###  #     ###  ## #  #   |            |_______|" << endl;
    cout << "|       |            |_____________________________________________|            |NEEDLES|" << endl;
    cout << "|-------|                                                                       |HALL   |" << endl;
    cout << "|CPH    |                                                                       |       |" << endl;
    cout << "|       |                                                                       |       |" << endl;
    cout << "|_______|                                                                       |_______|" << endl;
    cout << "|       |                                                                       |       |" << endl;
    cout << "|-------|                                                                       |-------|" << endl;
    cout << "|DWE    |                                                                       |MC     |" << endl;
    cout << "|       |                                                                       |       |" << endl;
    cout << "|_______|                                                                       |_______|" << endl;
    cout << "|PAC    |                                                                       |COOP   |" << endl;
    cout << "|       |                                                                       |FEE    |" << endl;
    cout << "|       |                                                                       |       |" << endl;
    cout << "|       |                                                                       |       |" << endl;
    cout << "|_______|                                                                       |_______|" << endl;
    cout << "|       |                                                                       |       |" << endl;
    cout << "|-------|                                                                       |-------|" << endl;
    cout << "|RCH    |                                                                       |DC     |" << endl;
    cout << "|       |                                                                       |       |" << endl;
    cout << "|_______|_______________________________________________________________________|_______|" << endl;
    cout << "|DC Tims|       |       |NEEDLES|       |MKV    |TUITION|       |SLC    |       |COLLECT|" << endl;
    cout << "|Line   |-------|-------|HALL   |-------|       |       |-------|       |-------|OSAP   |" << endl;
    cout << "|       |HH     |PAS    |       |ECH    |       |       |ML     |       |AL     |       |" << endl;
    cout << "|       |       |       |       |       |       |       |       |       |       |       |" << endl;
    cout << "|_______|_______|_______|_______|_______|_______|_______|_______|_______|_______|_______|" << endl;
}
