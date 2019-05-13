#ifndef BULLET_H
#define BULLET_H

#include "Component.h"
#include <string>

class Bullet : public Component {
private:
  int damage;
  float distanceLeft;
  Vec2 speed;
  bool targetsPlayer;

public:
  Bullet(GameObject &associated, float angle, float speed, int damage, float maxDistance, std::string sprite, int frameCount, float frameTime, bool targetsPlayer);
  void Update(float dt);
  void Render();
  bool Is(std::string type);
  int GetDamage();
  void NotifyCollision(GameObject &other);
  bool TargetsPlayer();
};

#endif