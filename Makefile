# https://stackoverflow.com/a/25966957

BIN := bin
SRC := games
OBJ := objects

apps    := $(BIN)/mines
# These will be populated as we include the modules
sources :=
objects :=
deps    :=

include $(SRC)/common/module.mk
include $(SRC)/mines/module.mk

CXX 	 := g++
CPPFLAGS := -I. -MMD -MP
CXXFLAGS := -std=c++20 -O3 -Werror -Wall -Wextra -pedantic-errors
LDFLAGS  :=
LDLIBS   := -lncurses

.SECONDEXPANSION:
$(BIN)/%: $(common_objects) $$(%_objects)
	@mkdir -p $(@D)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ)/%.o: $(SRC)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

.PHONY: all
all: $(apps) $(objects)

.PHONY: clean
clean:
	$(RM) -r $(BIN)/* $(OBJ)/*

.PHONY:
mines: $(BIN)/mines

-include $(deps)
