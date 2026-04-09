#include "../lib/nif.h"
#include "../lib/static_sequence.h"
#include "../lib/selection_method.h"
#include "../lib/bubble_method.h"
#include "../lib/merge_method.h"
#include "../lib/heap_method.h"
#include "../lib/shell_method.h"
#include <string>
#include <iostream>
#include <fstream>

// Funciones auxiliares
void printUsage() {
    std::cout << "Uso: ./sort -size <s> -ord <m> -init <i> [f] [-trace <y|n>] [-alpha <a>]" << std::endl;
    std::cout << std::endl;
    std::cout << "Opciones:" << std::endl;
    std::cout << "  -size <s>       Tamaño de la secuencia" << std::endl;
    std::cout << "  -ord <m>        Método de ordenación:" << std::endl;
    std::cout << "                    a = Selección" << std::endl;
    std::cout << "                    b = Burbuja" << std::endl;
    std::cout << "                    c = MergeSort" << std::endl;
    std::cout << "                    d = HeapSort" << std::endl;
    std::cout << "                    e = ShellSort" << std::endl;
    std::cout << "  -init <i> [f]   Inicialización:" << std::endl;
    std::cout << "                    manual = introducir manualmente" << std::endl;
    std::cout << "                    random = valores aleatorios" << std::endl;
    std::cout << "                    file <f> = leer de fichero" << std::endl;
    std::cout << "  -trace <y|n>    Mostrar traza (y=sí, n=no)" << std::endl;
    std::cout << "  -alpha <a>      Factor de reducción para ShellSort (0 < a < 1)" << std::endl;
}

int main(int argc, char* argv[]) {
  if (argc == 1 || (argc == 2 && std::string(argv[1]) == "--help")) {
    printUsage();
    return 0;
  }

  // Valores por defecto
  unsigned sequenceSize = 0;
  std::string ord, init, trace, filename;
  double alpha = -1.0;

  // Parseo de argumentos
  for (int i = 1; i < argc; i++) {
    std::string arg(argv[i]);
    if (arg == "-size") {
      if (i + 1 >= argc) { std::cerr << "Error: falta valor para -size\n"; return 1; }
      sequenceSize = std::stoi(argv[++i]);
    } else if (arg == "-ord") {
      if (i + 1 >= argc) { std::cerr << "Error: falta valor para -ord\n"; return 1; }
      ord = argv[++i];
    } else if (arg == "-init") {
      if (i + 1 >= argc) { std::cerr << "Error: falta valor para -init\n"; return 1; }
      init = argv[++i];
      if (init == "file") {
        if (i + 1 >= argc) { std::cerr << "Error: falta nombre de fichero para -init file\n"; return 1; }
        filename = argv[++i];
      }
    } else if (arg == "-trace") {
      if (i + 1 >= argc) { std::cerr << "Error: falta valor para -trace\n"; return 1; }
      trace = argv[++i];
    } else if (arg == "-alpha") {
      if (i + 1 >= argc) { std::cerr << "Error: falta valor para -alpha\n"; return 1; }
      alpha = std::stod(argv[++i]);
    }
  }

  if (sequenceSize == 0) {
    std::cerr << "Error: el tamaño de la secuencia debe ser mayor que 0\n";
    return 1;
  }

  if (!ord.empty() && ord[0] == 'e' && (alpha <= 0.0 || alpha >= 1.0)) {
    std::cerr << "Error: -alpha debe ser un valor entre 0 y 1 (exclusivo) para ShellSort\n";
    return 1;
  }

  // Inicialización: Secuencia
  StaticSequence<NIF> seq(sequenceSize);

  if (init == "manual") {
    std::cout << "Modo de introducción manual de datos: " << std::endl;
    for (unsigned i = 0; i < sequenceSize; i++) {
        NIF nif;
        do {
            std::cout << "Introduce el NIF " << i+1 << " (8 dígitos): ";
            std::cin >> nif;
            if ((long)nif < 10000000 || (long)nif > 99999999)
                std::cout << "nif invalido, intentalo de nuevo" << std::endl;
        } while ((long)nif < 10000000 || (long)nif > 99999999);
        seq.insert(nif);
    }
  } else if (init == "random") {
      for (unsigned i = 0; i < sequenceSize; i++) {
        seq.insert(NIF());
      }
  } else if (init == "file") {
      std::ifstream file(filename);
      if (!file.is_open()) {
        std::cerr << "Error: no se puede abrir el fichero '" << filename << "'\n";
        return 1;
      }
      NIF dni;
      while (file >> dni && !seq.isFull()) {
          seq.insert(dni);
      }
      file.close();
  }

  // Método de ordenación
  SortMethod<NIF>* method = nullptr;

  bool doTrace = (trace == "y");

  switch(ord[0]) {
    case 'a':
      method = new Selection<NIF>(seq, sequenceSize, doTrace);
      break;
    case 'b':
      method = new Bubble<NIF>(seq, sequenceSize, doTrace);
      break;
    case 'c':
      method = new Merge<NIF>(seq, sequenceSize, doTrace);
      break;
    case 'd':
      method = new Heap<NIF>(seq, sequenceSize, doTrace);
      break;
    case 'e':
      method = new Shell<NIF>(seq, sequenceSize, alpha, doTrace);
      break;
    default:
      std::cerr << "Error: método de ordenación '" << ord << "' no válido\n";
      printUsage();
      return 1;
  }
  method->Sort();
  for (unsigned i = 0; i < sequenceSize; i++) {
    std::cout << seq[i] << " ";
  }
  std::cout << std::endl;
}