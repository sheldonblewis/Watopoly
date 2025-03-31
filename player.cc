#include "academicbuilding.h"
#include "board.h"
#include "gym.h"
#include "player.h"
#include "residence.h"
#include "square.h"
#include <algorithm>
#include "ownable.h"
#include <string>
#include <iostream>
#include <random>
#include <string>
#include <vector>

Player::Player(std::string name, char symbol) : name{name}, symbol{symbol} {}

void Player::saveState(std::ostream& out) const {
    out << name << " " << symbol << " " << cups << " " << balance << " " << position;
    if (inTimsLine) out << " 1 " << turnsInTimsLine;
    out << "\n";
}

void Player::loadState(std::istream& in) {
    int dcTims, timsCounter;
    in >> name >> symbol >> cups >> balance >> position;
    if (position == 10) {
        if (in.peek() == '\n') {
            inTimsLine = false;
        } else {
            in >> dcTims >> timsCounter;
            inTimsLine = true;
            turnsInTimsLine = timsCounter;
        }
    }
}

int Player::getPosition() {
    if (position < 0 || position >= 40) {
        position = position % 40;
    }
    
    return position;
}

std::string Player::getName() const {
    return name;
}

int Player::getBalance() const {
    return balance;
}

int Player::getNetWorth() const {
    int netWorth = balance;
    for (const auto& ac : academicBuildingsOwned) {
        netWorth += ac->getCost() + (ac->numImprovements() * ac->getImprovementCost());
    }
    for (const auto& gym : gymsOwned) {
        netWorth += gym->getCost();
    }
    for (const auto& res : residencesOwned) {
        netWorth += res->getCost();
    }
    return netWorth;
}

std::tuple<int, int, int> Player::roll(bool testing) {
    int die1, die2;
    if (testing) {
        std::cin >> die1 >> die2;
    } else {
        die1 = rand() % 6 + 1;
        die2 = rand() % 6 + 1;
    }
    int move = die1 + die2;

    position += move;

    int prev = (position - move) % 40;

    if (position >= 40) {
        position -= 40;
        changeBalance(200);
        std::cout << name << " passed \"Collect OSAP\" and collected $200!" << std::endl;
    }

    return std::tuple(prev, die1, die2);
}


char Player::getSymbol() const {
    return symbol;
}

void Player::displayAssets() const {
    std::cout << "Player: " << name << " ($" << balance << ")" << std::endl;
    for (const auto& ac : academicBuildingsOwned) {
        std::cout << "  Academic Building: " << ac->getName() << " ";
        if (ac->isMortgaged()) {
            std::cout << "(mortgaged)";
        }
        for (int i = 0; i < ac->numImprovements(); ++i) {
            std::cout << "X";
        }
        std::cout << std::endl;
    }
    for (const auto& res : residencesOwned) {
        std::cout << "  Residence: " << res->getName();
        if (res->isMortgaged()) {
            std::cout << " (mortgaged)";
        }
        std::cout << std::endl;
    }
    for (const auto& gym : gymsOwned) {
        std::cout << "  Gym: " << gym->getName();
        if (gym->isMortgaged()) {
            std::cout << " (mortgaged)";
        }
        std::cout << std::endl;
    }
}

int Player::getNumCups() { return cups; };

bool Player::changeBalance(int amount) {
    if (amount < 0) { // amount is negative so we are decreasing balance
        if (-amount > balance) {
            return false; // not enough funds 
        }
    }

    // if amount is positive, or negative but its absolute value isn't greater than current balance -> change current balance
    balance += amount;
    return true;
}

bool Player::ownsGym(Gym* gym) const {
    if (gymsOwned.empty()) {
        return false;
    }
    
    for (const auto& ownedGym : gymsOwned) {
        if (ownedGym == gym) {
            return true;
        }
    }
    return false;
}

bool Player::ownsResidence(Residence* residence) const {
    if (residencesOwned.empty()) {
        return false;
    }
    
    for (const auto& ownedRes : residencesOwned) {
        if (ownedRes->getName() == residence->getName()) {
            return true;
        }
    }
    return false;
}

bool Player::ownsAcademicBuilding(AcademicBuilding* ac) const {
    if (academicBuildingsOwned.empty()) {
        return false;
    }
    
    for (const auto& ownedAC : academicBuildingsOwned) {
        if (ownedAC == ac) {
            return true;
        }
    }
    return false;
}

bool Player::ownsAll(const std::string& monopolyBlock) const {
    if (academicBuildingsOwned.empty()) {
        return false;
    }
    
    int counter = 0;
    for (const auto& ownedAC : academicBuildingsOwned) {
        if (ownedAC->getMonopolyBlock() == monopolyBlock) {
            counter++;
        }
    }

    // arts1 and math are the only two blocks with only 2 academic buildings each
    if (monopolyBlock == "Arts1" || monopolyBlock == "Math") {
        return counter == 2;
    } else {
        return counter == 3;
    }
}

std::vector<AcademicBuilding*> Player::getACOwned() const {
    return academicBuildingsOwned;
}

std::vector<Gym*> Player::getGymsOwned() const {
    return gymsOwned;
}

std::vector<Residence*>& Player::getResidencesOwned() {
    return residencesOwned;
}

void Player::addAcademicBuilding(AcademicBuilding* ac) {
    auto it = std::lower_bound(
        academicBuildingsOwned.begin(),
        academicBuildingsOwned.end(),
        ac,
        [](AcademicBuilding* a, AcademicBuilding* b) {
            return a->getPosition() < b->getPosition();
        }
    );
    academicBuildingsOwned.insert(it, ac);
}

void Player::addGym(Gym* gym) {
    auto it = std::lower_bound(
        gymsOwned.begin(),
        gymsOwned.end(),
        gym,
        [](Gym* a, Gym* b) {
            return a->getPosition() < b->getPosition();
        });
    gymsOwned.insert(it, gym);
}

void Player::addResidence(Residence* residence) {
    auto it = std::lower_bound(
        residencesOwned.begin(),
        residencesOwned.end(),
        residence,
        [](Residence* a, Residence* b) {
            return a->getPosition() < b->getPosition();
        });
    residencesOwned.insert(it, residence);
}

void Player::addProperty(Ownable* property) {
    if (auto ab = dynamic_cast<AcademicBuilding*>(property))
        academicBuildingsOwned.push_back(ab);
    else if (auto gym = dynamic_cast<Gym*>(property))
        gymsOwned.push_back(gym);
    else if (auto res = dynamic_cast<Residence*>(property))
        residencesOwned.push_back(res);
}

void Player::removeProperty(Ownable* property) {
    if (auto academic = dynamic_cast<AcademicBuilding*>(property)) {
        academicBuildingsOwned.erase(
            std::remove(academicBuildingsOwned.begin(), academicBuildingsOwned.end(), academic), 
            academicBuildingsOwned.end()
        );
    } else if (auto gym = dynamic_cast<Gym*>(property)) {
        gymsOwned.erase(
            std::remove(gymsOwned.begin(), gymsOwned.end(), gym), 
            gymsOwned.end()
        );
    } else if (auto residence = dynamic_cast<Residence*>(property)) {
        residencesOwned.erase(
            std::remove(residencesOwned.begin(), residencesOwned.end(), residence), 
            residencesOwned.end()
        );
    }
}

bool Player::tradePforP(std::shared_ptr<Player> other, Ownable* give, Ownable* receive) {
    if (give->getOwner() != this || receive->getOwner() != other.get()) {
        return false; // One of the players doesn't own the property
    }

    removeProperty(give);
    other->removeProperty(receive);

    addProperty(receive);
    other->addProperty(give);

    receive->changeOwner(this);
    give->changeOwner(other.get());

    return true;
}

bool Player::tradePforC(std::shared_ptr<Player> other, Ownable* give, int amountreceive) {
    if (give->getOwner() != this || other->getBalance() < amountreceive) {
        return false; // Player doesn't own property or other doesn't have enough money
    }

    // Ensure balance change happens first
    if (!other->changeBalance(-amountreceive)) return false;
    if (!changeBalance(amountreceive)) {
        other->changeBalance(amountreceive); // Refund the money back
        return false;
    }

    removeProperty(give);
    other->addProperty(give);
    give->changeOwner(other.get());

    return true;
}


bool Player::tradeCforP(std::shared_ptr<Player> other, int amountGive, Ownable* receive) {
    if (getBalance() < amountGive || receive->getOwner() != other.get()) {
        return false;
    }

    if (!changeBalance(-amountGive)) return false;
    if (!other->changeBalance(amountGive)) {
        changeBalance(amountGive); // Refund money back
        return false;
    }

    other->removeProperty(receive);
    addProperty(receive);
    receive->changeOwner(this);

    return true;
}

bool Player::mortgageProperties() {
    // display players assets
    std::cout << "These are your current assets :" << std::endl;
    
    displayAssets();

    std::cout << "Type 'G' to mortgage a gym, 'R' for residence building, 'A' for academic building and 'ALL' for all buldings: ";
    std::string command;
    std::cin >> command;

    if (command == "G") {
        std::cout << "\nWhich gym would you like to mortgage: ";
        std::string gym_name;
        std::cin >> gym_name;

        for (auto& gym : getGymsOwned()) {
            if (gym_name == gym->getName()) {
                gym->mortgage();
                changeBalance(gym->getCost() / 2);
                std::cout << "\nGym successfully mortgaged. New balance: " << getBalance() << std::endl;
                return true;
            }
        }

        std::cout << gym_name << " not owned by player, or doesn't exist. Try again." << std::endl;
        return false;

    } else if (command == "R") {
        std::cout << "\nWhich residence would you like to mortgage: ";
        std::string residence_name;
        std::cin >> residence_name;

        for (auto& residence : getResidencesOwned()) {
            if (residence_name == residence->getName()) {
                residence->mortgage();
                changeBalance(residence->getCost() / 2);
                std::cout << "Residence successfully mortgaged. New balance: " << getBalance() << std::endl;
                return true;
            }
        }

        std::cout << residence_name << " not owned by player, or doesn't exist. Try again." << std::endl;
        return false;
    } else if (command == "A") {
        std::cout << "Which academic building would you like to mortgage: ";
        std::string academic_name;
        std::cin >> academic_name;

        for (auto& ac : getACOwned()) {
            if (academic_name == ac->getName()) {
                ac->mortgage();
                changeBalance(ac->getCost() / 2);
                std::cout << "Academic bulding successfully mortgaged. New balance: " << getBalance() << std::endl;
                return true;
            }
        }

        std::cout << academic_name << " not owned by player, or doesn't exist. Try again." << std::endl;
        return false;
    } else if (command == "ALL") {
        
        for (auto& gym : getGymsOwned()) {
            gym->mortgage();
            changeBalance(gym->getCost() / 2);
            std::cout << "Gym successfully mortgaged."  << std::endl;
        }
    
        for (auto& residence : getResidencesOwned()) {
            residence->mortgage();
            changeBalance(residence->getCost() / 2);
            std::cout << "Residence successfully mortgaged. " << std::endl;
        }
    
        for (auto& ac : getACOwned()) {
            if (ac->numImprovements() == 0) { // can only mortgage ac if no improvements
                ac->mortgage();
                changeBalance(ac->getCost() / 2);
                std::cout << "Academic bulding successfully mortgaged." << std::endl;
            }
        }
        std::cout << "New Balance: " << getBalance() << std::endl;
        return true;
    }
    return false;
}

bool Player::possibleToSurvive(int balance_owned) {
    int sum = 0;

    sum += getBalance();

    for (auto& gym : getGymsOwned()) {
        sum += gym->getCost() / 2;
    }

    for (auto& residence : getResidencesOwned()) {
        sum += residence->getCost() / 2;
    }

    for (auto& ac : getACOwned()) {
        if (ac->numImprovements() == 0) { // can only mortgage ac if no improvements
            sum += ac->getCost() / 2;
        }
    }

    if (balance_owned >= sum) {
        return false;
    } else {
        return true;
    }
}

int Player::randNum(int n) {
    return rand() % n + 1;
}

void Player::chanceForCup() {
    int num = randNum(100);
    
    if (cups <= 4) {
        if (num == 69) {
            cups++;
            std::cout << "Congratulations you have received a Roll Up the Rim Cup!" << std::endl;
        }
    }
}

int Player::move(int n, Board& board) {
    position += n;
    if (position >= 40) {
        position -= 40;
        std::cout << name << " passed \"Collect OSAP\" and collected $200!" << std::endl;
    } else if (position <= 0) {
        position += 40;
    }

    std::cout << name << " moved to " << board.getSquare(position)->getName() << std::endl;

    if (n > 0) {
        return (position - n) % 40;
    } else {
        return (position + n) % 40;
    }
    
}

void Player::sendToTimsLine(Board& board) {
    std::cout << "Go to DC Tims Line! Do not pass go, do not collect $200.\n";
    std::cout << "You are now in the DC Tims Line." << std::endl;
    turnsInTimsLine = 0;
    inTimsLine = true;
    board.getSquare(10)->addPlayer(shared_from_this());
    board.getSquare(getPosition())->removePlayer(shared_from_this());
    board.drawBoard();
    position = 10;
}

bool Player::isInTimsLine() { return inTimsLine; }

int Player::getTurnsInTimsLine() { return turnsInTimsLine; }

void Player::leaveTimsLine() {
    inTimsLine = false;
    turnsInTimsLine = 0;
}

void Player::incTurnsInTimsLine() {
    turnsInTimsLine += 1;
}

void Player::useCup() {
    if (cups > 0) {
        cups -= 1;
    }
}

bool Player::tryToLeaveTimsLine() {
    int die1 = rand() % 6 + 1;
    int die2 = rand() % 6 + 1;

    if (die1 == die2) {
        std::cout << "\nYou have rolled double " << die1 << "!" << std::endl;
        return true;
    } else {
        std::cout << "\nYou have rolled " << die1 << " and " << die2 <<std::endl;
        return false;
    }
}

void Player::changePosition(int n) {
    position = n;
}

void Player::declareBankruptcy(std::shared_ptr<Player> creditor, Board& board, std::vector<std::shared_ptr<Player>>& players) {
    std::cout << name << " has declared bankruptcy!" << std::endl;

    // Transfer properties to the creditor, or return to bank
    for (auto& prop : academicBuildingsOwned) {
        prop->changeOwner(nullptr);

        // Remove improvements before auction or transfer
        for (int i = 0; i < prop->numImprovements(); ++i) {
            prop->degrade(this);
        }

        prop->unmortgage(); // Reset mortgage status

        if (creditor) {
            prop->changeOwner(creditor.get());
            creditor->addAcademicBuilding(prop);
        } else {
            board.startAuction(std::dynamic_pointer_cast<Ownable>(prop->shared_from_this()), players);
        }
    }
    academicBuildingsOwned.clear();

    for (auto& res : residencesOwned) {
        res->changeOwner(nullptr);

        if (creditor) {
            res->changeOwner(creditor.get());
            creditor->addResidence(res);
        } else {
            board.startAuction(std::dynamic_pointer_cast<Ownable>(res->shared_from_this()), players);
        }
    }
    residencesOwned.clear();

    for (auto& gym : gymsOwned) {
        gym->changeOwner(nullptr);

        if (creditor) {
            gym->changeOwner(creditor.get());
            creditor->addGym(gym);
        } else {
            board.startAuction(std::dynamic_pointer_cast<Ownable>(gym->shared_from_this()), players);
        }
    }
    gymsOwned.clear();

    // Transfer Roll Up the Rim Cups
    if (creditor) {
        creditor->setCups(cups + creditor->getNumCups());
    } else {
        board.returnCups(cups);
    }

    cups = 0;
    bankrupt = true;
}

bool Player::isBankrupt() const {
    return bankrupt;
}

void Player::declareBankruptcyToBank(Board& board, std::vector<std::shared_ptr<Player>>& players) {
    std::cout << name << " has declared bankruptcy to the Bank!\n";

    for (auto& prop : academicBuildingsOwned) {
        prop->changeOwner(nullptr);
        for (int i = 0; i < prop->numImprovements(); ++i) {
            prop->degrade(this);
        }
        prop->unmortgage();
        board.startAuction(std::dynamic_pointer_cast<Ownable>(prop->shared_from_this()), players);
    }

    for (auto& prop : gymsOwned) {
        prop->changeOwner(nullptr);
        prop->unmortgage();
        board.startAuction(std::dynamic_pointer_cast<Ownable>(prop->shared_from_this()), players);
    }

    for (auto& prop : residencesOwned) {
        prop->changeOwner(nullptr);
        prop->unmortgage();
        board.startAuction(std::dynamic_pointer_cast<Ownable>(prop->shared_from_this()), players);
    }

    board.returnCups(cups);
    cups = 0;
    bankrupt = true;
}
