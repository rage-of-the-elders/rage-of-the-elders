#ifndef NURSE_H
#define NURSE_H

#define NURSE_ATTACK_COOLDOWN 5
#define NURSE_SPEED 200
#define NURSE_BULLET_DAMAGE 5
#define NURSE_BULLET_Y_GAP 0
#define NURSE_BULLET_FRAME_COUNT 3

#include "Enemy.h"

class Nurse : public Enemy {
protected:
//   Rect target;
  void ManageInput(float dt);
  void HandleMovement(float dt);
  void HandleHurting(float dt);
  enum NurseSide { LEFT_SIDE_OF_THE_SCREEN, RIGHT_SIDE_OF_THE_SCREEN };
  NurseSide nurseSide;
//   void HandleDying(float dt);

public:
  Nurse(GameObject &associated);
  ~Nurse();
  void ResetSpeed();
  void Update(float dt);
  bool Is(std::string type);
  // void Start();
  // bool TargetIsInRange();
  // bool Is(std::string type);
  // void NotifyCollision(GameObject &other);
  // bool IsOpponent(GameObject &other);
};

#endif