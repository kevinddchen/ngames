# https://stackoverflow.com/a/25966957

BIN := bin
SRC := src
OBJ := objects

app     := $(BIN)/mines
sources := $(wildcard $(SRC)/*.cpp)
objects := $(subst $(SRC),$(OBJ),$(sources:.cpp=.o))
deps    := $(objects:.o=.d)

CXX 	 := g++
CPPFLAGS :=
CXXFLAGS := -std=c++20 -Wall -O3
LDFLAGS  :=
LDLIBS   := -lncurses

$(app): $(objects)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ)/%.o: $(SRC)/%.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ -o $@

.PHONY: clean
clean:
	$(RM) $(objects) $(deps) $(app)

-include $(deps)
