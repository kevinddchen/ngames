mines_sources := $(wildcard $(SRC)/mines/*.cpp)
mines_objects := $(subst $(SRC),$(OBJ),$(mines_sources:.cpp=.o))
mines_deps    := $(mines_objects:.o=.d)

apps    += $(BIN)/mines
sources += $(mines_sources)
objects += $(mines_objects)
deps    += $(mines_deps)

.PHONY: mines
mines: $(BIN)/mines
