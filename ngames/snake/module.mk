snake_sources := $(wildcard $(SRC)/snake/*.cpp)
snake_objects := $(subst $(SRC),$(OBJ),$(snake_sources:.cpp=.o))
snake_deps    := $(snake_objects:.o=.d)

apps    += $(BIN)/snake
sources += $(snake_sources)
objects += $(snake_objects)
deps    += $(snake_deps)

.PHONY: snake
snake: $(BIN)/snake
