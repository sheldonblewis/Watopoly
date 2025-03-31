#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <memory>
#include <vector>

class AcademicBuilding;
class Board;
class Gym;
class Residence;
class Ownable;

class Player : public std::enable_shared_from_this<Player> {
    std::string name;
    char symbol;
    int position = 0;
    int balance = 1500;
    bool inTimsLine = false;
    int turnsInTimsLine = 0;
    int cups = 0;
    bool bankrupt = false;

    std::vector<AcademicBuilding*> academicBuildingsOwned;
    std::vector<Gym*> gymsOwned;
    std::vector<Residence*> residencesOwned;
    

public:
    Player(std::string name, char symbol);
    bool isBankrupt() const;
    int roll(Board& board);
    int getPosition();
    std::string getName() const;
    char getSymbol() const;
    void displayAssets() const;
    std::vector<AcademicBuilding*> getACOwned() const;
    std::vector<Gym*> getGymsOwned() const;
    std::vector<Residence*>& getResidencesOwned();
    void addAcademicBuilding(AcademicBuilding* ac);
    void addGym(Gym* gym);
    void addResidence(Residence* residence);
    int getBalance() const;

    // returns number of roll up rims player has
    int getNumCups();

    // called when player lands on NH or SLC for a 1% chance of RUR
    void chanceForCup();

    // return true if change balance was successful, false if the player doens't have enough money
    bool changeBalance(int amount);

    // takes in a gym pointer and returns true if player owns that gym, false otherwise
    bool ownsGym(Gym* gym) const;

    // takes in a residence pointer and returns true if player owns that residence, false otherwise
    bool ownsResidence(Residence* residence) const;

    // takes in a academic building pointer and returns true if player owns that academic building, false otherwise
    bool ownsAcademicBuilding(AcademicBuilding* ac) const;

    bool ownsAll(const std::string& monopolyBlock) const;

    void sendToTimsLine() {
        position = 10;
        inTimsLine = true;
    }
    // removes the property from the correcponding vector in the players attribute
    // ASSUMES PLAYER OWNS PROPERTY
    void removeProperty(Ownable* property);

    // adds property to the corresponding 
    void addProperty(Ownable* property);

    // attempts to initiate trade between *this and other, property for property, returns true if successful, false otherwise
    bool tradePforP(std::shared_ptr<Player> other, Ownable* give, Ownable* receive);


    // attempts to initiate trade between *this and other, property for cash, returns true if successful, false otherwise
    bool tradePforC(std::shared_ptr<Player> other, Ownable* give, int amountreceive);

    // attempts to initiate trade between *this and other, property for cash, returns true if successful, false otherwise
    bool tradeCforP(std::shared_ptr<Player> other, int amountGive, Ownable* receive);

    // when player doesn't have enough funds to pay for something this function gets called letting the user mortgage his ownables
    bool mortgageProperties();

    // calculates whether player can pay sum after mortgaging all properties
    bool possibleToSurvive(int balance_owned);

    // generates random number between 1 and n inclusive
    int randNum(int n);

    // moves the player n squares, n can be both negative and positive
    int move(int n, Board& board);

    // sends the player to jail
    void sendToTimsLine(Board& board);

    // returns true if player is in jail false otherwise
    bool isInTimsLine();

    // get the number of rounds the player has been in jail
    int getTurnsInTimsLine();

    void setTurnsInTimsLine(int turns) {
        this->turnsInTimsLine = turns;
    }

    // sets inTimsLine to false and num rounds in jail to 0
    void leaveTimsLine();

    // decreases the number of roll up rims
    void useCup();

    void setCups(int cups) {
        this->cups = cups;
    }

    // increases num rounds in jail by 1
    void incTurnsInTimsLine();

    // returns true if player rolls doubles, false otherwise
    bool tryToLeaveTimsLine();

    // changes position of player to n
    void changePosition(int n);

    void declareBankruptcy(std::shared_ptr<Player> creditor, Board& board, std::vector<std::shared_ptr<Player>>& players);
    void declareBankruptcyToBank(Board& board, std::vector<std::shared_ptr<Player>>& players);
    
    void loadState(std::istream& in);
    void saveState(std::ostream& out) const;
};

#endif
