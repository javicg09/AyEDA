CXX = g++
CXXFLAGS = -std=c++17 -Wall -I lib

SRC = src/main.cpp src/nif.cpp
OBJ = $(SRC:.cpp=.o)
BIN = sort

all: $(BIN)

$(BIN): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(BIN) $(OBJ)

src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(BIN)

.PHONY: all clean