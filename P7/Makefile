.PHONY: build test clean

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I./lib
TARGET = avl
SRC = src/main.cc
TEST_TARGET = test/testunitario
TEST_SRC = test/testunitario.cpp

build: $(SRC) lib/NodoB.h lib/AB.h lib/ABE.h lib/ABB.h lib/NodoAVL.h lib/AVL.h lib/nif.h
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

test: $(TEST_SRC) lib/NodoB.h lib/AB.h lib/ABB.h lib/NodoAVL.h lib/AVL.h
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_SRC)
	./$(TEST_TARGET)

clean:
	rm -f $(TARGET) $(TEST_TARGET)
