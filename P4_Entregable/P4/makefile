CXX = g++
CXXFLAGS = -std=c++17 -Wall -I lib

SRC = src/main.cpp src/nif.cpp src/libro.cpp
OBJ = $(SRC:.cpp=.o)
BIN = hash_table

all: $(BIN)

$(BIN): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(BIN) $(OBJ)

src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(BIN)

.PHONY: all clean