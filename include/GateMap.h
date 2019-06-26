#ifndef GATEMAP_H
#define GATEMAP_H

#include <string>
#include <vector>

class GateMap {
private:
  int currentIndex;
  int numberOfGates;
  std::vector<int> gates;

public:
  GateMap(std::string file);
  ~GateMap();

  int GetCurrentGate();

  void NextGate();
  void Load(std::string file);
};

#endif
