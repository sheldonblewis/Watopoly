CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -g -MMD -Werror=vla
SOURCES = $(wildcard *.cc)
OBJECTS = $(SOURCES:.cc=.o)
DEPENDS = $(OBJECTS:.o=.d)
EXEC = watopoly

$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJECTS)

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

-include $(DEPENDS)

.PHONY: clean
clean:
ifeq ($(OS),Windows_NT)
	del /Q $(subst /,\,$(OBJECTS) $(DEPENDS) $(EXEC)) 2>nul || exit 0
else
	rm -f $(OBJECTS) $(DEPENDS) $(EXEC)
endif
