#ifndef FIGHTER_H
#define FIGHTER_H

#include "Component.h"
#include <vector>
#include "Vec2.h"
#include "Sprite.h"
#include "Sound.h"

#define FIGHTER_HP 100
#define FIGHTER_SPEED Vec2(10)

class Fighter : public Component {
protected:
  int hp;
  Vec2 speed;
  enum FighterState { FIRST, MOVING, ATTACKING, IDLE, LAST };
  enum Orientation { LEFT, RIGHT };
  Orientation orientation;
  FighterState currentState;
  std::vector<Sprite*> sprite;
  std::vector<Sound*> sound;

  void UpdateStateMachine();
public:

  Fighter(GameObject &associated);
  ~Fighter();
  void Start();
  virtual void Update(float dt);
  void Render();
  bool Is(std::string type);
  void NotifyCollision(GameObject &other);
  void ActivateSprite(FighterState state);
};

#endif