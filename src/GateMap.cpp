#include "GateMap.h"

#include <fstream>

GateMap::GateMap(std::string file) {
  this->gates = std::vector<int>();
  this->currentIndex = 0;
  this->numberOfGates = 0;

  this->Load(file);
}

GateMap::~GateMap() {
  this->gates.clear();
}

void GateMap::Load(std::string file) {
  std::ifstream gateMapFile(("assets/" + file).c_str(), std::ios::in);

  if (gateMapFile.good()) {
    char comma;

    int value;

    gateMapFile >> this->numberOfGates >> comma;

    for (int i = 0; i < this->numberOfGates; i++) {
      gateMapFile >> value >> comma;
      this->gates.emplace_back(value);
    }

    // Indicates there is no gates left on the stage
    this->gates.emplace_back(-1);
  } else {
    printf("ERROR: Could not open '%s'", file.c_str());
    exit(-1);
  }
  gateMapFile.close();
}

int GateMap::GetCurrentGate() {
  return this->gates[this->currentIndex];
}

void GateMap::NextGate() {
  if(this->currentIndex < this->numberOfGates)
    this->currentIndex++;
}
