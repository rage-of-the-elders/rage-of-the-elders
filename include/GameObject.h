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
  bool active;
  bool started;
  float angleDeg;

  GameObject();
  ~GameObject();
  
  void Start();
  void Render();
  bool IsDead();
  bool IsActive();
  void Activate();
  void Desactivate();
  void RequestDelete();
  void Update(float dt);
  void AddComponent(Component *cpt);
  void RemoveComponent(Component *cpt);
  void NotifyCollision(GameObject &other);
  Component *GetComponent(std::string type);
  void ReplaceComponent(Component *cpt, Component *replaceCpt);
};

#endif
