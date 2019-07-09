#ifndef VETERAN_H
#define VETERAN_H

#define VETERAN_HP 100
#define VETERAN_SPEED 200

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
  // bool IsOpponent(GameObject &other);
  // void NotifyCollision(GameObject &other);
};

#endif
