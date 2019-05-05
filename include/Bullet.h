#ifndef BULLET_H
#define BULLET_H

#include "Component.h"
#include <string>

class Bullet : public Component {
private:
  int damage;
  float distanceLeft;
  Vec2 speed;

public:
  Bullet(GameObject &associated, float angle, float speed, int damage, float maxDistance, std::string sprite);
  void Update(float dt);
  void Render();
  bool Is(std::string type);
  int GetDamage();
};

#endif