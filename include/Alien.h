#ifndef ALIEN_H
#define ALIEN_H

#define ALIEN_ROTATION 2
#define ALIEN_COOLDOWN 7
#define ALIEN_BASE_SPEED 100

#include "Component.h"
#include "Timer.h"
#include <string>

class Alien : public Component {
private:
  int hp;
  int nMinions;
  Vec2 speed;
  std::vector<std::weak_ptr<GameObject> > minionArray;
  enum AlienState { MOVING, RESTING };
  AlienState state;
  Timer restTimer;
  Vec2 destination;
  int GetNearestMinion(Vec2 target);
  

public:
  static int alienCount;

  Alien(GameObject &associated, int nMinions);
  ~Alien();
  void Start();
  void Update(float dt);
  void Render();
  bool Is(std::string type);
  bool IsDead();
  void ApplyDamage(int damage);
  void NotifyCollision(GameObject &other);
};

#endif