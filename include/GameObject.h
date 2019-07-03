#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#define  INCLUDE_SDL_IMAGE

#include "SDL_include.h"
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
  SDL_RendererFlip flip = SDL_FLIP_NONE;

  GameObject();
  ~GameObject();
  
  void Start();
  void Render();
  bool IsDead();
  bool IsActive();
  void ToggleActive();
  bool Has(std::string type);
  void Activate();
  static void NewRender(std::vector <std::shared_ptr<GameObject>> objectArray);
  void Desactivate();
  void RequestDelete();
  void Update(float dt);
  void AddComponent(Component *cpt);
  void RemoveComponent(Component *cpt);
  void NotifyCollision(GameObject &other);
  Component *GetComponent(std::string type);
  std::vector<std::shared_ptr<Component>> GetComponents();
  void ReplaceComponent(Component *cpt, Component *replaceCpt);
};

#endif
