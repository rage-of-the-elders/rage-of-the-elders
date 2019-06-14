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

  virtual void ManageInput(float dt) = 0;
  virtual void UpdateStateMachine(float dt) = 0;
public:

  Fighter(GameObject &associated);
  ~Fighter();
  void Start();
  Rect GetFoot();
  void Update(float dt);
  void Render();
  void ApplyDamage(int damage);
  bool IsHurting();
  bool IsAttacking();
  bool IsDead();
  bool Is(std::string type);
  virtual bool IsOpponent(GameObject &other) = 0;
  void NotifyCollision(GameObject &other);
  void ActivateSprite(FighterState state);
  enum Orientation GetOrientation();
  bool CanAttack(enum Orientation orientation, Rect targetRect);
};

#endif