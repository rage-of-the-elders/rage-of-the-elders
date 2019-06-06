#ifndef FIGHTER_H
#define FIGHTER_H

#include "Component.h"
#include <vector>
#include "Vec2.h"
#include "Sprite.h"
#include "Sound.h"

#define FIGHTER_HP 100
#define FIGHTER_SPEED 20

class Fighter : public Component {
protected:
  int hp;
  float speed;
  enum FighterState { FIRST, MOVING, BASIC_ATTACK_ONE, BASIC_ATTACK_TWO, COMBO, ULTIMATE, IDLE, HURTING, DYING, LAST, INVALID };
  enum Orientation { LEFT, RIGHT };
  Orientation orientation;
  FighterState currentState;
  FighterState storedState;
  std::vector<Sprite*> sprite;
  std::vector<Sound*> sound;

  void UpdateStateMachine();
public:

  Fighter(GameObject &associated);
  ~Fighter();
  void Start();
  Rect GetFoot();
  virtual void Update(float dt);
  void Render();
  void ApplyDamage(int damage);
  bool IsHurting();
  bool IsAttacking();
  bool Is(std::string type);
  void NotifyCollision(GameObject &other);
  void ActivateSprite(FighterState state);
  bool isTakingDamage;
  bool CanAttack(enum Orientation orientation, Rect targetRect);
};

#endif