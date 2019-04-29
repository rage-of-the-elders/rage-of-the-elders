#ifndef ALIEN_H
#define ALIEN_H

#include "Component.h"

#include <string>
#include <queue>


class Alien : public Component {
private:
  class Action {
    public:
      enum ActionType {MOVE, SHOOT};
      ActionType type;
      Vec2 pos;

     Action (ActionType type, float x, float y);
  };

  int hp;
  int nMinions;
  Vec2 speed;
  std::queue<Action> taskQueue;
  std::vector<std::weak_ptr<GameObject> > minionArray;
  

public:
  Alien(GameObject &associated, int nMinions);
  ~Alien();
  void Start();
  void Update(float dt);
  void Render();
  bool Is(std::string type);
  bool IsDead();
};

#endif