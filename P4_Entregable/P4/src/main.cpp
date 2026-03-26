#include <iostream>
#include <string>

#include "../lib/libro.h"
#include "../lib/hash_table.h"
#include "../lib/module_dispersion.h"
#include "../lib/sum_dispersion.h"
#include "../lib/random_dispersion.h"
#include "../lib/lineal_function.h"
#include "../lib/quadratic_function.h"
#include "../lib/double_dispersion_function.h"
#include "../lib/redispersion_function.h"
#include "../lib/exploration_function.h"

int main(int argc, char* argv[]) {
    unsigned tableSize = 10, blockSize = 3;
    int fdCode = 1, feCode = 1;
    std::string hashType = "close";

    // 1. Parsear argumentos
    for (int i = 1; i < argc; i++) {
        if (std::string(argv[i]) == "-ts") tableSize = std::stoi(argv[++i]);
        else if (std::string(argv[i]) == "-fd") fdCode = std::stoi(argv[++i]);
        else if (std::string(argv[i]) == "-hash") hashType = argv[++i];
        else if (std::string(argv[i]) == "-bs") blockSize = std::stoi(argv[++i]);
        else if (std::string(argv[i]) == "-fe") feCode = std::stoi(argv[++i]);
    }

    // 2. Crear función de dispersión según fdCode
    DispersionFunction<Libro>* fd;
    switch(fdCode) {
        case 1: fd = new ModuleDispersion<Libro>(tableSize); break;
        case 2: fd = new SumDispersion<Libro>(tableSize); break;
        case 3: fd = new RandomDispersion<Libro>(tableSize); break;
    }
    // 3. Crear función de exploración según feCode
    ExplorationFunction<Libro>* fe = nullptr;
    if (hashType == "close") {
        switch(feCode) {
            case 1: fe = new LinealFunction<Libro>(); break;
            case 2: fe = new QuadraticFunction<Libro>(); break;
            case 3: fe = new DoubleDispersionFunction<Libro>(fd); break;
            case 4: fe = new RedispersionFunction<Libro>(); break;
        }
    }
    // 4. Crear la tabla hash
    Sequence<Libro>* table;
    if (hashType == "close") {
        table = new HashTable<Libro, StaticSequence<Libro>>(tableSize, *fd, *fe, blockSize);
    } else {
        table = new HashTable<Libro, DynamicSequence<Libro>>(tableSize, *fd);
    }
    // 5. Menú insertar/buscar
    int opcion;
    Libro k;
    do {
        std::cout << "1. Insertar" << std::endl;
        std::cout << "2. Buscar" << std::endl;
        std::cout << "0. Salir" << std::endl;
        std::cout << "Opcion: ";
        std::cin >> opcion;

        switch(opcion) {
            case 1:
                std::cout << "Introduce los datos del libro: " << std::endl;
                std::cin >> k;
                if (table->insert(k)) std::cout << "Insertado correctamente" << std::endl;
                else std::cout << "No se pudo insertar" << std::endl;
                break;

            case 2:
                std::cout << "Introduce los datos del libro a buscar: " << std::endl;
                std::cin >> k;
                if (table->search(k)) std::cout << "Encontrado" << std::endl;
                else std::cout << "No encontrado" << std::endl;
                break;
        }
    } while(opcion != 0);
}