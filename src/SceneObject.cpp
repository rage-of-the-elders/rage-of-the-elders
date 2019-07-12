#include "SceneObject.h"
#include "Collider.h"
#include "Collision.h"
#include "Playable.h"

#include <fstream>
#include <iostream>

#define SPRITE_PATH "img/scenes_objects/"
#define SHADOW_HEIGHT 30

SceneObject::SceneObject(GameObject &associated, std::string environment, int x, int y, int objectType) : Component(associated) {
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
  return type == "SceneObject";
}

void SceneObject::NotifyCollision(GameObject &other) {
  if(other.Has("Playable")) {
    Playable *player = (Playable*) other.GetComponent("Playable");
    if(Collision::IsColliding(*player->GetColliderBox(), this->associated.box, other.angleDeg, this->associated.angleDeg)) {
      printf("Quebrou!\n");
    }
  }
}

void SceneObject::BuildObject(std::string environment, int x, int y, int objectType) {
  Sprite *sprite = new Sprite(this->associated,
                              SPRITE_PATH + environment + "/" + std::to_string(objectType + 1) + ".png");

  this->associated.AddComponent(sprite);
  this->associated.box.SetPos(x, (y - this->associated.box.h) + SHADOW_HEIGHT);
}

Rect SceneObject::GetColisionRect(int colisionHeight) {
  Rect colisionRect = this->associated.box;

  colisionRect.h = (colisionHeight * (colisionRect.h / 3));
  colisionRect.y += this->associated.box.h - colisionRect.h - SHADOW_HEIGHT;

  return colisionRect;
}
