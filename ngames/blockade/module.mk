blockade_sources := $(wildcard $(SRC)/blockade/*.cpp)
blockade_objects := $(subst $(SRC),$(OBJ),$(blockade_sources:.cpp=.o))
blockade_deps    := $(blockade_objects:.o=.d)

apps    += $(BIN)/blockade
sources += $(blockade_sources)
objects += $(blockade_objects)
deps    += $(blockade_deps)

blockade_objects += $(OBJ)/snake/snake.o

.PHONY: blockade
blockade: $(BIN)/blockade
