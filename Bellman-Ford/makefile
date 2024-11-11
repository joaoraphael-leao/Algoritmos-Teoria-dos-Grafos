EXEC = caminho_minimo

CXX = g++
CXXFLAGS = -std=c++11 -Wall
SRC = bellmanford.cpp

INPUT_FILES = $(wildcard input*.txt)
OUTPUT_FILES = $(patsubst input%.txt,output%.txt,$(INPUT_FILES))

all: $(EXEC) run_tests

$(EXEC): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(SRC)

run_tests: $(OUTPUT_FILES)

output%.txt: input%.txt $(EXEC)
	./$(EXEC) -f $< -o $@

clean:
	rm -f $(EXEC) output*.txt

