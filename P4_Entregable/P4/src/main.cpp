#include <iostream>
#include <string>

#include "../lib/nif.h"
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
    DispersionFunction<NIF>* fd;
    switch(fdCode) {
        case 1: fd = new ModuleDispersion<NIF>(tableSize); break;
        case 2: fd = new SumDispersion<NIF>(tableSize); break;
        case 3: fd = new RandomDispersion<NIF>(tableSize); break;
    }
    // 3. Crear función de exploración según feCode
    ExplorationFunction<NIF>* fe = nullptr;
    if (hashType == "close") {
        switch(feCode) {
            case 1: fe = new LinealFunction<NIF>(); break;
            case 2: fe = new QuadraticFunction<NIF>(); break;
            case 3: fe = new DoubleDispersionFunction<NIF>(fd); break;
            case 4: fe = new RedispersionFunction<NIF>(); break;
        }
    }
    // 4. Crear la tabla hash
    Sequence<NIF>* table;
    if (hashType == "close") {
        table = new HashTable<NIF, StaticSequence<NIF>>(tableSize, *fd, *fe, blockSize);
    } else {
        table = new HashTable<NIF, DynamicSequence<NIF>>(tableSize, *fd);
    }
    // 5. Menú insertar/buscar
    int opcion;
    NIF k;
    do {
        std::cout << "1. Insertar" << std::endl;
        std::cout << "2. Buscar" << std::endl;
        std::cout << "0. Salir" << std::endl;
        std::cout << "Opcion: ";
        std::cin >> opcion;

        switch(opcion) {
            case 1:
                do {
                    std::cout << "Introduce el NIF (8 digitos): ";
                    std::cin >> k;
                    if ((long)k < 10000000 || (long)k > 99999999)
                        std::cout << "NIF invalido, intentalo de nuevo" << std::endl;
                } while ((long)k < 10000000 || (long)k > 99999999);
                if (table->insert(k)) std::cout << "Insertado correctamente" << std::endl;
                else std::cout << "No se pudo insertar" << std::endl;
                break;

            case 2:
                do {
                    std::cout << "Introduce el NIF (8 digitos): ";
                    std::cin >> k;
                    if ((long)k < 10000000 || (long)k > 99999999)
                        std::cout << "NIF invalido, intentalo de nuevo" << std::endl;
                } while ((long)k < 10000000 || (long)k > 99999999);
                if (table->search(k)) std::cout << "Encontrado" << std::endl;
                else std::cout << "No encontrado" << std::endl;
                break;
        }
    } while(opcion != 0);
}