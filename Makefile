# https://stackoverflow.com/a/25966957

BIN := bin
SRC := src
OBJ := objects

app     := $(BIN)/mines
sources := $(wildcard $(SRC)/*.cpp)
objects := $(subst $(SRC),$(OBJ),$(sources:.cpp=.o))

CXX 	 := g++
CPPFLAGS :=
CXXFLAGS := -std=c++20 -Wall -O3
LDFLAGS  :=
LDLIBS   := -lncurses

$(app): $(objects)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ)/%.o: $(SRC)/%.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ -o $@

.PHONY: all
all: $(objects) $(app)

.PHONY: clean
clean:
	$(RM) $(objects) $(app)
