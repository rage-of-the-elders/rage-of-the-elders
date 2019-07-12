#ifndef TEACHER_H
#define TEACHER_H

#define TEACHER_HP 100
#define TEACHER_SPEED 280
#define TEACHER_BASIC_ATK_2_DAMAGE 12
#define TEACHER_COMBO_DAMAGE 15

#include "Playable.h"

class Teacher : public Playable {
protected:
  virtual void HandleUltimateBegin(float dt);
  std::vector <std::shared_ptr<GameObject>> enemys;
  // void HandleMovement(float dt);
  // void UpdateStateMachine(float dt);

public:
  // static Veteran *player;
  Teacher(GameObject &associated);
  ~Teacher();
  void Update(float dt);
  // void Start();
  bool Is(std::string type);
  float GetHPPercentage();
  // bool IsOpponent(GameObject &other);
  // void NotifyCollision(GameObject &other);
};

#endif
