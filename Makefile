CC = g++
CFLAGS = -I./src -Wall -std=c++20 -O3
SRC = ./src
BIN = ./bin

$(BIN)/%.o: $(SRC)/%.cpp
	@mkdir -p $(@D)
	$(CC) -c -o $@ $(CFLAGS) $<

$(BIN)/main: $(SRC)/main.cpp $(BIN)/board.o
	$(CC) -o $@ $(CFLAGS) -lncurses $^

.PHONY: clean
clean:
	rm -rf $(BIN)
