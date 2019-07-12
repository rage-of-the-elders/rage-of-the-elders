#ifndef VETERAN_H
#define VETERAN_H

#define VETERAN_HP 250
#define VETERAN_SPEED 200
#define BULLET_DAMAGE 30
#define VETERAN_BASIC_ATK_2_DAMAGE 17
#define VETERAN_BASIC_ATK_1_DAMAGE 13
#define VETERAN_COMBO_DAMAGE 20

#include "Playable.h"

class Veteran : public Playable {
private:
  // void ManageInput(float dt);
  // void HandleMovement(float dt);
  // void UpdateStateMachine(float dt);

public:
  // static Veteran *player;
  Veteran(GameObject &associated);
  ~Veteran();
  void Update(float dt);
  // void Start();
  bool Is(std::string type);
  float GetHPPercentage();
  // bool IsOpponent(GameObject &other);
  // void NotifyCollision(GameObject &other);
};

#endif
