#include "SceneObject.h"
#include "Collider.h"

#include <fstream>
#include <iostream>

#define SPRITE_PATH "img/scenes_objects/"

SceneObject::SceneObject(GameObject &associated, std::string environment, int x, int y, int objectType) : Component(associated) {
  std::cout << "Constructor: " << environment << " " << x << " " << y << " " << objectType << " " << std::endl;
  std::cout << "Associated: " << associated.box.w << " " << associated.box.h << std::endl;
  this->spriteBrokenObjects = std::vector<Sprite*>(4);
  this->spriteLivingRoom = std::vector<Sprite*>(9);
  this->spriteNursery = std::vector<Sprite*>(8);
  
  this->BuildObject(environment, x, y, objectType);
  this->associated.AddComponent(new Collider(this->associated, {1, 1}, {1, 1}));
}

void SceneObject::Update(float dt) {

}

void SceneObject::Render() {

}

bool SceneObject::Is(std::string type) {

}

void SceneObject::NotifyCollision(GameObject &other) {

}

void SceneObject::BuildObject(std::string environment, int x, int y, int objectType) {
  Sprite *sprite = new Sprite(this->associated,
                              SPRITE_PATH + environment + "/" + std::to_string(objectType + 1) + ".png");

  this->associated.AddComponent(sprite);
  this->associated.box.SetPos(x, (y - this->associated.box.h));
}