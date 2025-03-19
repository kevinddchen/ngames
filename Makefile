# https://stackoverflow.com/a/25966957

BIN := bin
SRC := games
OBJ := objects

# These will be populated as we include the modules
apps    :=
sources :=
objects :=
deps    :=

include $(SRC)/common/module.mk
include $(SRC)/mines/module.mk
include $(SRC)/snakes/module.mk

-include $(deps)

CXX 	 := g++
CPPFLAGS := -I. -MMD -MP
CXXFLAGS := -std=c++20 -O3 -Wall -Wextra -pedantic-errors
LDFLAGS  :=
LDLIBS   := -lncurses

# Link apps
.SECONDEXPANSION:
$(BIN)/%: $(common_objects) $$(%_objects)
	@mkdir -p $(@D)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

# Compile objects
$(OBJ)/%.o: $(SRC)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

.PHONY: all
all: $(apps) $(objects)

.PHONY: clean
clean:
	$(RM) -r $(BIN)/* $(OBJ)/*
