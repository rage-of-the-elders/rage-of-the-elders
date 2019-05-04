#ifndef MINION_H
#define MINION_H

#include "Component.h"

#include <string>
#include <memory>


class Minion : public Component {
private:
  // GameObject& alienCenter;
  std::weak_ptr<GameObject> alienCenter;
  float arc;

public:
  Minion (GameObject& associated, GameObject &alienCenter, float arcOffsetDeg = 0);
  void Shoot(Vec2 target);
  void Update(float dt);
  void Render();
  bool Is(std::string type);
};

#endif