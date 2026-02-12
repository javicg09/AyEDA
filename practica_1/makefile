# Variables de compilación
CXX = g++
CXXFLAGS = -std=c++17 -Wall -g -Ilib  # -Ilib permite usar #include "ant.h" sin rutas relativas complejas

# Directorios
SRC_DIR = src
OBJ_DIR = obj

# Archivos fuente y objetos
# El main está en la raíz, los demás en src/
SOURCES = main.cpp $(SRC_DIR)/ant.cpp $(SRC_DIR)/simulator.cpp $(SRC_DIR)/tape.cpp
# Transformamos las rutas de fuentes a rutas de objetos en la carpeta obj/
OBJECTS = $(OBJ_DIR)/main.o $(OBJ_DIR)/ant.o $(OBJ_DIR)/simulator.o $(OBJ_DIR)/tape.o

# Nombre del ejecutable
TARGET = langton_ant

# Regla principal
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Regla para el objeto de main.cpp (que está en la raíz)
$(OBJ_DIR)/main.o: main.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c main.cpp -o $@

# Regla genérica para los objetos en src/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpiar archivos generados
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# Regla para ejecutar con el archivo input.txt
run: $(TARGET)
	./$(TARGET) input.txt

.PHONY: all clean run