#ifndef PLAYABLE_H
#define PLAYABLE_H

#define PLAYABLE_HP 100
#define PLAYABLE_SPEED 200

#include "Fighter.h"

class Playable : public Fighter {
protected:
  void ManageInput(float dt);
  void HandleMovement(float dt);
  virtual void HandleUltimateBegin(float dt);
  virtual void HandleUltimateMidle(float dt);
  virtual void HandleUltimateFinal(float dt);
  // void UpdateStateMachine(float dt);

public:
  static Playable *player;
  Playable(GameObject &associated);
  ~Playable();
  void Start();
  bool Is(std::string type);
  bool IsOpponent(GameObject &other);
  void NotifyCollision(GameObject &other);
  void Update(float dt);
};

#endif
