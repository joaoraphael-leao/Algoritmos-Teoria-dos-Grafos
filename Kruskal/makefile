CPP = g++
CFLAGS = -std=c++11 -Wall

BIN_DIR = ../Bat1/
SRC_DIR = .
OBJ_DIR = $(BIN_DIR)obj

BIN = $(BIN_DIR)kruskal.bin

$(BIN): $(SRC_DIR)/kruskal.c++ | $(BIN_DIR)
	$(CPP) $(CFLAGS) -o $@ $<

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm -f $(BIN)
	rm -rf $(OBJ_DIR)
