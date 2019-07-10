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
  float shooterY;
  std::string shooterType;

  Bullet(GameObject &associated, float angle, float speed, int damage, float maxDistance, std::string sprite, int frameCount,
        float frameTime, bool targetsPlayer, float shooterY, std::string shooterType);
  void Update(float dt);
  void Render();
  bool Is(std::string type);
  int GetDamage();
  void NotifyCollision(GameObject &other);
  bool TargetsPlayer();
  void SetDirection(float speed, float angleDeg);
  float GetAngleDeg();
  void RemoveBullet();
};

#endif