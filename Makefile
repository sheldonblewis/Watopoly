CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -g -MMD -Werror=vla
SOURCES = $(wildcard *.cc)
OBJECTS = $(SOURCES:.cc=.o)
DEPENDS = $(OBJECTS:.o=.d)
EXEC = watopoly
SHELL := cmd.exe

$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(EXEC).exe $(OBJECTS)

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

-include $(DEPENDS)

.PHONY: clean
clean:
	@if exist $(EXEC).exe del /f /q $(EXEC).exe
	@for %%f in (*.o *.d) do del /f /q %%f
