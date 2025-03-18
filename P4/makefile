# Universidad de La Laguna
# Escuela Superior de Ingeniería y Tecnología
# Grado en Ingeniería Informática
# Algoritmos y Estructuras de Datos Avanzados
#
# @author Alexander Valencia Hernández 
# alu0101500386@ull.edu.es
# @date 14 Marzo 2024
# @brief A Makefile for p4_hash_search

all: main

main: main.o nif.o dynamic_sequence.o static_sequence.o hash_table.o functions.o
	g++ -o p4_hash_search main.cc nif.cc dynamic_sequence.cc static_sequence.cc hash_table.cc functions.cc
	
clean:
	rm -f p4_hash_search *.o