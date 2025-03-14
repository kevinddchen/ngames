snakes_sources := $(wildcard $(SRC)/snakes/*.cpp)
snakes_objects := $(subst $(SRC),$(OBJ),$(snakes_sources:.cpp=.o))
snakes_deps    := $(snakes_objects:.o=.d)

apps    += $(BIN)/snakes
sources += $(snakes_sources)
objects += $(snakes_objects)
deps    += $(snakes_deps)

.PHONY: snakes
snakes: $(BIN)/snakes
