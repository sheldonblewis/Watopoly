#include <set>
#include <map>

// Inside main()
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
}
