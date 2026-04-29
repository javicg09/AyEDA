CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
TARGET = arbol
SRCS = main.cc
build: $(SRCS) lib/NodoB.h lib/AB.h lib/ABE.h lib/ABB.h lib/nif.h
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)
test: test/testunitario.cpp lib/NodoB.h lib/AB.h lib/ABE.h lib/ABB.h lib/nif.h
	$(CXX) $(CXXFLAGS) -o test/testunitario test/testunitario.cpp
clean:
	rm -f $(TARGET) test/testunitario
