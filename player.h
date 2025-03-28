#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <memory>
#include <vector>

class AcademicBuilding;
class Board;
class Gym;
class Residence;

class Player : public std::enable_shared_from_this<Player> {
    std::string name;
    char symbol;
    int position = 0;
    int balance = 1500;

    std::vector<AcademicBuilding*> academicBuildingsOwned;
    std::vector<Gym*> gymsOwned;
    std::vector<Residence*> residencesOwned;
    

public:
    Player(std::string name, char symbol);
    int roll(Board& board);
    int getPosition() const;
    std::vector<AcademicBuilding*> getACOwned() const;
    std::string getName() const;
    char getSymbol() const;
    void displayAssets() const;
    std::vector<Gym*> getGymsOwned() const;
    std::vector<Residence*>& getResidencesOwned();
    void addAcademicBuilding(AcademicBuilding* ac);
    void addGym(Gym* gym);
    void addResidence(Residence* residence);
    int getBalance() const;

    // return true if change balance was successfull 
    // false if the player doens't have enough money
    bool changeBalance(int amount);

    // takes in a gym pointer and returns true if player owns
    // that gym, false otherwise
    bool ownsGym(Gym* gym) const;


    // takes in a residence pointer and returns true if player owns
    // that residence, false otherwise
    bool ownsResidence(Residence* residence) const;


    // takes in a academic building pointer and returns true if player 
    // owns that academic building, false otherwise
    bool ownsAcademicBuilding(AcademicBuilding* ac) const;
};

#endif
