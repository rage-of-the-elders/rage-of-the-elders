#ifndef BARRIER_H
#define BARRIER_H

#include "Component.h"


class Barrier : public Component {
public:
  Barrier(GameObject &associated, Rect position = Rect());
  void Update(float dt);
  void Render();
  bool Is(std::string type);
  void NotifyCollision(GameObject &other);
};

#endif