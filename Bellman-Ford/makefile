EXEC = caminho_minimo

CXX = g++
CXXFLAGS = -std=c++11 -Wall
SRC = bellmanford.cpp

INPUT_DIR = entradas
OUTPUT_DIR = saidas

INPUT_FILES = $(wildcard $(INPUT_DIR)/input*.txt)

OUTPUT_FILES = $(patsubst $(INPUT_DIR)/input%.txt,$(OUTPUT_DIR)/output%.txt,$(INPUT_FILES))

all: $(EXEC) run_tests

$(EXEC): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(SRC)

run_tests: $(OUTPUT_FILES)

$(OUTPUT_DIR)/output%.txt: $(INPUT_DIR)/input%.txt $(EXEC)
	./$(EXEC) -f $< -o $@

clean:
	rm -f $(EXEC) $(OUTPUT_DIR)/output*.txt
