#include "functions.h"

void Usage(int argc, char* argv[]) {
  if(argc == 2) {
    std::string argument = argv[1];
    if(argument == "--help") {
      std::cout << "Este programa trabaja con una tabla hash de tamaño dado por el usuario, pudiendole insertar y buscar elementos.\n";
      std::cout << "Los parametros son el tamaño de la tabla (-ts), el tipo de funcion de dispersion (-fd) (sum|mod|rand), el tipo de dispersion (-hash) (open|close).\n";
      std::cout << "Si la el tipo de dispersión es close habrán dos parámetros adicionales, el tamaño del bloque (-bs) y el tipo de función de exploración (-fe)\n";
      std::cout << "(lin|quad|dhash|rehash).\n";
      exit(EXIT_FAILURE);
    }
  } else if(argc < 5) {
    std::cout << "Número de parametros insuficiente.\n";
    exit(EXIT_FAILURE);
  } else if(argc > 11) {
    std::cout << "Ha sobrepasado el límite de argumentos.\n";
    exit(EXIT_FAILURE);
  }
}

void HashMenu(HashTable<nif, dynamicSequence<nif>> hashTableOpen, HashTable<nif> hashTableClose, const std::string& hashType) {
  int choise = 0;
  while (true) {
    std::cout << "¿Qué desea hacer?" << std::endl;
    std::cout << "0. Salir del programa" << std::endl;
    std::cout << "1. Insertar un elemento" << std::endl;
    std::cout << "2. Buscar un elemento" << std::endl;
    std::cout << "3. Imprimir la tabla" << std::endl;
    std::cin >> choise;

    switch (choise) {
      case 0:
        std::cout << "Saliendo del programa..." << std::endl;
        exit(EXIT_SUCCESS);
      case 1: {
        nif element;
        std::cout << "Ingrese el elemento a insertar: ";
        std::cin >> element;
        if (hashType == OPEN) {
          if (hashTableOpen.insert(element)) {
            std::cout << "Elemento insertado con éxito en la tabla de dispersión abierta." << std::endl;
          } else {
            std::cout << "El elemento no se pudo insertar en la tabla de dispersión abierta." << std::endl;
          }
        } else if (hashType == CLOSE) {
          if (hashTableClose.insert(element)) {
            std::cout << "Elemento insertado con éxito en la tabla de dispersión cerrada." << std::endl;
          } else {
            std::cout << "El elemento no se pudo insertar en la tabla de dispersión cerrada." << std::endl;
          }
        }
        break;
      }
      case 2: {
        nif element;
        std::cout << "Ingrese el elemento a buscar: ";
        std::cin >> element;
        if (hashType == OPEN) {
          if (hashTableOpen.search(element)) {
            std::cout << "El elemento se encuentra en la tabla de dispersión abierta." << std::endl;
          } else {
            std::cout << "El elemento no se encuentra en la tabla de dispersión abierta." << std::endl;
          }
        } else if (hashType == CLOSE) {
          if (hashTableClose.search(element)) {
            std::cout << "El elemento se encuentra en la tabla de dispersión cerrada." << std::endl;
          } else {
            std::cout << "El elemento no se encuentra en la tabla de dispersión cerrada." << std::endl;
          }
        }
        break;
      }
      case 3:
        if (hashType == OPEN) {
          std::cout << "Imprimiendo tabla de dispersión abierta:" << std::endl;
          hashTableOpen.printTable();
        } else if (hashType == CLOSE) {
          std::cout << "Imprimiendo tabla de dispersión cerrada:" << std::endl;
          hashTableClose.printTable();
        }
        break;
      default:
        std::cout << "Opción no válida. Por favor, seleccione una opción válida." << std::endl;
    }
  }
}