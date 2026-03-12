# Nombre del ejecutable
TARGET = hormiga_sim

# Compilador y flags
CXX = g++
CXXFLAGS = -std=c++14 -Wall -Wextra -g

# Directorios
SRCDIR = src
LIBDIR = lib
OBJDIR = obj

# Archivos fuente y objetos
SOURCES = $(wildcard $(SRCDIR)/*.cpp) main.cpp
OBJECTS = $(SOURCES:%.cpp=$(OBJDIR)/%.o)

# Crear el directorio de objetos si no existe
$(shell mkdir -p $(OBJDIR)/$(SRCDIR))

# Regla principal
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regla para compilar los .o
$(OBJDIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpieza
clean:
	rm -rf $(OBJDIR) $(TARGET)

.PHONY: clean