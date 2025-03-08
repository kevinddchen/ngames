# https://stackoverflow.com/a/25966957

BIN := bin
SRC := src
OBJ := objects

app     := $(BIN)/mines
sources := $(wildcard $(SRC)/*.cpp)
objects := $(subst $(SRC),$(OBJ),$(sources:.cpp=.o))
deps    := $(objects:.o=.d)

CXX 	 := g++
CPPFLAGS := -MMD -MP
CXXFLAGS := -std=c++20 -O3 -Werror -Wall -Wextra -pedantic-errors
LDFLAGS  :=
LDLIBS   := -lncurses

$(app): $(objects)
	@mkdir -p $(BIN)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ)/%.o: $(SRC)/%.cpp
	@mkdir -p $(OBJ)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

.PHONY: all
all: $(app) $(objects)

.PHONY: clean
clean:
	$(RM) $(BIN)/* $(OBJ)/*

-include $(deps)
