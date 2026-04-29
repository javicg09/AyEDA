CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
TARGET = arbol
SRCS = main.cc
build: $(SRCS) lib/NodoB.h lib/AB.h lib/ABE.h lib/ABB.h lib/nif.h
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)
clean:
	rm -f $(TARGET)
