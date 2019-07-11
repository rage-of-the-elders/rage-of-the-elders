#include "GateMap.h"

#include <fstream>

GateMap::GateMap(std::string file) {
  this->gates = std::vector<Gate>();
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

    gateMapFile >> this->numberOfGates >> comma;
    for (int i = 0; i < this->numberOfGates; i++) {
      struct Gate newGate;

      gateMapFile >> newGate.position >> comma;
      gateMapFile >> newGate.enemiesAmount >> comma;

      for(int j = 0; j < newGate.enemiesAmount; j++) {
        EnemyInfo newEnemy;
        gateMapFile >> newEnemy.type >> comma >> newEnemy.invertSide >> comma;

        newGate.enemies.emplace_back(newEnemy);

      }
      this->gates.emplace_back(newGate);
    }

    // Indicates there is no gates left on the stage
    Gate finalGate;
    finalGate.position = -1;
    this->gates.emplace_back(finalGate);
  } else {
    printf("ERROR: Could not open '%s'", file.c_str());
    exit(-1);
  }
  gateMapFile.close();
}

Gate GateMap::GetCurrentGate() {
  return this->gates[this->currentIndex];
}

void GateMap::NextGate() {
  if(this->currentIndex < this->numberOfGates)
    this->currentIndex++;
}
