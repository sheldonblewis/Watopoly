CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -g

watopoly: main.o player.o board.o square.o ownable.o academicbuilding.o
	$(CXX) $(CXXFLAGS) -o watopoly main.o player.o board.o square.o ownable.o academicbuilding.o

clean:
	rm -f watopoly *.o
