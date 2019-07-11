#ifndef GATEMAP_H
#define GATEMAP_H

#include <string>
#include <vector>
#include <utility>

struct EnemyInfo {
  int type;
  int invertSide;
};

struct Gate {
  int position;
  int enemiesAmount;
  std::vector<EnemyInfo> enemies;
};

class GateMap {
private:
  int currentIndex;
  int numberOfGates;
  std::vector<Gate> gates;

public:
  GateMap(std::string file);
  ~GateMap();

  Gate GetCurrentGate();

  void NextGate();
  void Load(std::string file);
};

#endif
