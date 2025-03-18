#include "functions.h"

std::string OPEN = "open";    // Por si la dispersión es abierta
std::string CLOSE = "close";  // Por si la dispersión es cerrada
const std::string& SUM = "sum";
const std::string& MOD = "mod";
const std::string& RAND = "rand";
const std::string& LIN = "lin";
const std::string& QUAD = "quad";
const std::string& DHASH = "dhash";
const std::string& REHASH = "rehash";

int main(int argc, char* argv[]) {
  Usage(argc, argv);
  unsigned tableSize = 0, blockSize = 0;
  std::string fdCode, hashType, feCode;
  bool hashTypeClose = false;  // Variable para verificar si -hash es close
  srand(time(nullptr));

  for (int i = 1; i < argc; i++) {
    std::string option(argv[i]);
    if (option == "-ts") {
      if (i + 1 < argc) {
        tableSize = std::atoi(argv[++i]);
      } else {
        std::cerr << "Error: Falta el valor después de -ts" << std::endl;
        return 1;
      }
    } else if (option == "-fd") {
      if (i + 1 < argc) {
        fdCode = argv[++i];
      } else {
        std::cerr << "Error: Falta el valor después de -fd" << std::endl;
        return 1;
      }
    } else if (option == "-hash") {
      if (i + 1 < argc) {
        hashType = argv[++i];
        if (hashType == CLOSE) {
          hashTypeClose = true;
        }
      } else {
        std::cerr << "Error: Falta el valor después de -hash" << std::endl;
        return 1;
      }
    } else if (hashTypeClose && option == "-bs") {
      if (i + 1 < argc) {
        blockSize = std::atoi(argv[++i]);
      } else {
        std::cerr << "Error: Falta el valor después de -bs" << std::endl;
        return 1;
      }
    } else if (!hashTypeClose && option == "-bs") {
      std::cerr << "Error: La opción -bs solo se puede usar con dispersión cerrada (-hash close)" << std::endl;
      return 1;
    } else if (option == "-fe") {
      if (i + 1 < argc) {
        feCode = argv[++i];
      } else {
        std::cerr << "Error: Falta el valor después de -fe" << std::endl;
        return 1;
      }
    } else {
      std::cerr << "Error: Opción no reconocida: " << option << std::endl;
      return 1;
    }
  }

  if (tableSize == 0 || fdCode.empty() || hashType.empty()) {
    std::cerr << "Error: Falta uno o más parámetros necesarios" << std::endl;
    return 1;
  }

  DispersionFunction<nif>* fd = nullptr;
  ExplorationFunction<nif>* fe = nullptr;

  // Creación de la función de dispersión
  if (fdCode == MOD) {
    fd = new Module<nif>(tableSize);
  } else if (fdCode == SUM) {
    fd = new Sum<nif>(tableSize);
  } else if (fdCode == RAND) {
    fd = new Pseudoaleatoria<nif>(tableSize);
  } else {
    std::cerr << "Error: Función de dispersión no reconocida: " << fdCode << std::endl;
    return 1;
  }

  if (hashType == CLOSE) {
    if (feCode.empty()) {
      std::cerr << "Error: Falta especificar la función de exploración para dispersión cerrada" << std::endl;
      return 1;
    }
    if (feCode == LIN) {
      fe = new feLineal<nif>(fd, tableSize);
    } else if (feCode == QUAD) {
      fe = new feQuadratic<nif>(fd, tableSize);
    } else if (feCode == DHASH) {
      fe = new DoubleHashing<nif>(fd, tableSize);
    } else if (feCode == REHASH) {
      fe = new Rehashing<nif>(fd, tableSize);
    } else {
      std::cerr << "Error: Función de exploración no reconocida: " << feCode << std::endl;
      return 1;
    }
  }

  HashTable<nif, dynamicSequence<nif>> hashTableOpen(tableSize, fd);
  HashTable<nif> hashTableClose(tableSize, fd, fe, blockSize);

  HashMenu(hashTableOpen, hashTableClose, hashType);
  return 0;
}