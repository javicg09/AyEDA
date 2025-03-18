#pragma once

#include <iostream>
#include "hash_table.h"
#include "dynamic_sequence.h"
#include "static_sequence.h"

extern std::string OPEN;    // Por si la dispersión es abierta
extern std::string CLOSE;  // Por si la dispersión es cerrada

void Usage(int, char**);
void HashMenu(HashTable<nif, dynamicSequence<nif>>, HashTable<nif>, const std::string&);