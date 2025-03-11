common_sources := $(wildcard $(SRC)/common/*.cpp)
common_objects := $(subst $(SRC),$(OBJ),$(common_sources:.cpp=.o))
common_deps    := $(common_objects:.o=.d)

sources += $(common_sources)
objects += $(common_objects)
deps += $(common_deps)
