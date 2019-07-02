#ifndef FIGHTER_H
#define FIGHTER_H

#include "Component.h"
#include <vector>
#include "Vec2.h"
#include "Sprite.h"
#include "Sound.h"

#define FIGHTER_HP 100
#define FIGHTER_SPEED 20
#define ATTACK_Y_RANGE 30
#define SHOOT_COOLDOWN 0.5


class Fighter : public Component {
protected:
  int hp;
  enum FighterState { FIRST, MOVING, BASIC_ATTACK_ONE, BASIC_ATTACK_TWO, COMBO, ULTIMATE_BEGIN,
                      ULTIMATE_MIDLE, ULTIMATE_FINAL, IDLE, HURTING, DYING, HIT, FROZEN, LAST, INVALID };
  enum Orientation { LEFT, RIGHT };
  int damage[LAST];
  int comboCount;
  int points;
  float speed;
  Timer shootCooldown;
  Timer ultimateDuration;
  Orientation orientation;
  FighterState storedState;
  FighterState currentState;
  std::vector<Sound*> sound;
  std::vector<Sprite*> sprite;

  virtual void ManageInput(float dt) = 0;
  virtual void UpdateStateMachine(float dt);
  virtual void HandleMovement(float dt);
  virtual void HandleAttackOne(float dt);
  virtual void HandleAttackTwo(float dt);
  virtual void HandleCombo(float dt);
  virtual void HandleUltimateBegin(float dt);
  virtual void HandleUltimateMidle(float dt);
  virtual void HandleUltimateFinal(float dt);
  virtual void HandleHurting(float dt);
  virtual void HandleDying(float dt);
  virtual void HandleFrozen(float dt);

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
  Rect GetColliderBox();
  int GetDamage();
  void SetState(FighterState state);
  bool TargetIsInYRange(Rect targetBox);
  void Shoot(std::string file, int frameCount);
};

#endif