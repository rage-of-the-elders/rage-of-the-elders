#ifndef PENGUINCANNON_H
#define PENGUINCANNON_H

#include "Component.h"

class PenguinCannon : public Component {
private:
  std::weak_ptr<GameObject> pbody;
  float angle;

public:
  PenguinCannon(GameObject &associated, GameObject& penguinBody);
  void Update(float dt);
  void Render();
  bool Is(std::string type);
  void Shoot();
  void ApplyDamage(int damage);
  void NotifyCollision(GameObject &other);
};

#endif