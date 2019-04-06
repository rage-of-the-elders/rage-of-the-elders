#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <string>
#include <vector>
#include <memory>

#include "Rect.h"

class Component;

class GameObject {
private:
  bool isDead;
  std::vector<std::shared_ptr<Component>> components;

public:
  Rect box;

  GameObject();
  ~GameObject();
  void Update(float dt);
  void Render();
  bool IsDead();
  void RequestDelete();
  void AddComponent(Component *cpt);
  void RemoveComponent(Component *cpt);
  Component *GetComponent(std::string type);
};

#endif
