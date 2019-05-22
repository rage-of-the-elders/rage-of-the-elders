#ifndef VETERAN_H
#define VETERAN_H

#include "Component.h"
#include <vector>
#include "Vec2.h"
#include "Sprite.h"
#include "Sound.h"

#define VETERAN_HP 100
#define VETERAN_SPEED Vec2(10)

class Veteran : public Component {
  private:
  int hp;
  Vec2 speed;
  enum VeteranState { FIRST, MOVING, ATTACKING, IDLE, LAST };
  VeteranState currentState;
  std::vector<Sprite*> sprite;
  std::vector<Sound*> sound;
  bool a;

public:

  Veteran(GameObject &associated);
  ~Veteran();
  void Start();
  void Update(float dt);
  void Render();
  bool Is(std::string type);
  void NotifyCollision(GameObject &other);
  void ActivateSprite(VeteranState state);
};

#endif