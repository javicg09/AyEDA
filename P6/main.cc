#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>

#include "lib/ABB.h"
#include "lib/ABE.h"
#include "lib/nif.h"

void printUsage(const char* prog) {
  std::cout << "Uso:\n"
            << "  " << prog << " -ab <abe|abb> -init <modo> [opciones]\n\n"
            << "Opciones de -ab:\n"
            << "  abe          Arbol binario equilibrado\n"
            << "  abb          Arbol binario de busqueda\n\n"
            << "Modos de -init:\n"
            << "  manual       Arbol vacio; el usuario inserta claves\n"
            << "  random s     Genera e inserta s claves NIF aleatorias\n"
            << "  file s f     Lee s claves NIF del fichero f e inserta\n\n"
            << "Menu interactivo:\n"
            << "  [0] Salir\n"
            << "  [1] Insertar clave NIF\n"
            << "  [2] Buscar clave NIF\n"
            << "  [3] Mostrar arbol en inorden\n\n"
            << "Ejemplos:\n"
            << "  " << prog << " -ab abb -init manual\n"
            << "  " << prog << " -ab abe -init random 8\n"
            << "  " << prog << " -ab abb -init file 10 data/nifs.txt\n";
}

int main(int argc, char* argv[]) {
  std::string tipoArbol;
  std::string modoInit;
  int numClaves = 0;
  std::string fichero;

  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg == "--help" || arg == "-h") {
      printUsage(argv[0]);
      return 0;
    } else if (arg == "-ab" && i + 1 < argc) {
      tipoArbol = argv[++i];
    } else if (arg == "-init" && i + 1 < argc) {
      modoInit = argv[++i];
      if (modoInit == "random" && i + 1 < argc) {
        numClaves = std::stoi(argv[++i]);
      } else if (modoInit == "file" && i + 2 < argc) {
        numClaves = std::stoi(argv[++i]);
        fichero = argv[++i];
      }
    }
  }

  if (tipoArbol.empty()) {
    std::cerr << "Uso: " << argv[0]
              << " -ab <abe|abb> -init <manual|random s|file s f>\n";
    return 1;
  }

  AB<NIF>* arbol = nullptr;
  if (tipoArbol == "abe") {
    arbol = new ABE<NIF>();
  } else if (tipoArbol == "abb") {
    arbol = new ABB<NIF>();
  } else {
    std::cerr << "Tipo de arbol no valido: " << tipoArbol << "\n";
    return 1;
  }

  srand(static_cast<unsigned>(time(nullptr)));

  if (modoInit == "manual" || modoInit.empty()) {
    // arbol vacio, el usuario inserta manualmente
  } else if (modoInit == "random") {
    for (int i = 0; i < numClaves; ++i) {
      NIF nif;
      arbol->insertar(nif);
    }
  } else if (modoInit == "file") {
    std::ifstream f(fichero);
    if (!f) {
      std::cerr << "Error al abrir fichero: " << fichero << "\n";
      delete arbol;
      return 1;
    }
    for (int i = 0; i < numClaves; ++i) {
      NIF nif(0);
      f >> nif;
      if (!f) break;
      arbol->insertar(nif);
    }
  } else {
    std::cerr << "Modo de inicializacion no valido: " << modoInit << "\n";
    delete arbol;
    return 1;
  }

  std::cout << *arbol;

  int opcion = -1;
  do {
    std::cout << "\n[0] Salir\n"
              << "[1] Insertar clave\n"
              << "[2] Buscar clave\n"
              << "[3] Mostrar arbol inorden\n"
              << "Opcion: ";
    if (!(std::cin >> opcion)) break;

    switch (opcion) {
      case 1: {
        long val = 0;
        std::cout << "Introduce clave NIF (numero): ";
        std::cin >> val;
        NIF clave(val);
        if (arbol->insertar(clave)) {
          std::cout << "Clave " << clave << " insertada con exito.\n";
        } else {
          std::cout << "La clave " << clave << " ya existe en el arbol.\n";
        }
        std::cout << *arbol;
        break;
      }
      case 2: {
        long val = 0;
        std::cout << "Introduce clave NIF (numero): ";
        std::cin >> val;
        NIF clave(val);
        if (arbol->buscar(clave)) {
          std::cout << "Clave " << clave << " encontrada.\n";
        } else {
          std::cout << "Clave " << clave << " no encontrada.\n";
        }
        break;
      }
      case 3:
        std::cout << "Recorrido inorden: ";
        arbol->inorden();
        break;
      case 0:
        std::cout << "Saliendo...\n";
        break;
      default:
        std::cout << "Opcion no valida.\n";
    }
  } while (opcion != 0);

  delete arbol;
  return 0;
}
