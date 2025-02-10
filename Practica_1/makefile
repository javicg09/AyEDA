# Compilador y flags
CXX       = g++
CXXFLAGS  = -std=c++11 -Wall -Wextra -Ilib

# Directorios
SRC_DIR   = src

# Nombre del ejecutable
TARGET    = mcd

# Fuentes
SRCS      = main.cpp $(SRC_DIR)/BigInteger.cpp $(SRC_DIR)/BigUnsigned.cpp

# Objetos (se generan cambiando la extensión .cpp por .o)
OBJS      = $(SRCS:.cpp=.o)

# Regla por defecto
all: $(TARGET)

# Enlaza los objetos para crear el ejecutable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Regla genérica para compilar archivos .cpp a .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpia los archivos objeto y el ejecutable
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
