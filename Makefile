CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -g -MMD -Werror=vla
DEPENDS = $(OBJECTS:.o=.d)
EXEC = watopoly
OBJECTS = $(SOURCES:.cc=.o)
SHELL := cmd.exe
SOURCES = $(wildcard *.cc)

$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJECTS)

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

-include $(DEPENDS)

.PHONY: clean
clean:
	del /f /q academicbuilding.o board.o gym.o main.o ownable.o player.o residence.o square.o academicbuilding.d board.d gym.d main.d ownable.d player.d residence.d square.d watopoly 2>NUL || exit 0
