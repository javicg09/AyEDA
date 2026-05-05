CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I./lib
TARGET = avl
SRC = src/main.cc

build: $(SRC) lib/NodoB.h lib/AB.h lib/ABE.h lib/ABB.h lib/NodoAVL.h lib/AVL.h lib/nif.h
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
