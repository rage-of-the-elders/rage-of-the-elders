#include "PenguinBody.h"
#include "PenguinCannon.h"
#include "Game.h"
#include "InputManager.h"
#include "Camera.h"
#include "Collider.h"
#include "Bullet.h"

#define PENGUIN_ACELERATION 15
#define FOWARD_SPEED_LIMIT 150
#define BACKWARDS_SPEED_LIMIT -FOWARD_SPEED_LIMIT / 2.0

PenguinBody *PenguinBody::player;

PenguinBody::PenguinBody(GameObject& associated) : Component(associated) {
  this->pcannon = std::weak_ptr<GameObject>();
  this->speed = Vec2(0);
  this->linearSpeed = 0;
  this->angle = 0;
  this->hp = 100;
  this->player = this;
  this->associated.AddComponent(new Sprite(associated, "img/penguin.png"));
  this->associated.AddComponent(new Collider(associated));
}

PenguinBody::~PenguinBody() {
  this->player = nullptr;
  Camera::Unfollow();
}

void PenguinBody::Start() {
  GameObject* go = new GameObject();
  go->AddComponent(new PenguinCannon(*go, this->associated));
  Game::GetInstance().GetState().AddObject(go);
  this->pcannon = Game::GetInstance().GetState().GetObjectPtr(go);
}

void PenguinBody::Update(float dt) {
  if (InputManager::GetInstance().IsKeyDown(W_KEY)) {
    this->linearSpeed += (PENGUIN_ACELERATION * dt);
    if (this->linearSpeed > FOWARD_SPEED_LIMIT)
      this->linearSpeed = FOWARD_SPEED_LIMIT;
  }
  if (InputManager::GetInstance().IsKeyDown(S_KEY)) {
    this->linearSpeed -= (PENGUIN_ACELERATION * dt);
    if (this->linearSpeed < BACKWARDS_SPEED_LIMIT)
      this->linearSpeed = BACKWARDS_SPEED_LIMIT;
  }
  if (InputManager::GetInstance().IsKeyDown(A_KEY)) {
    this->angle -= (45 * dt);
  }
  if (InputManager::GetInstance().IsKeyDown(D_KEY)) {
    this->angle += (45 * dt);
  }

  this->speed = Vec2::GetSpeed(angle) * this->linearSpeed;
  this->associated.box.UpdatePos(speed * dt);
  this->associated.angleDeg = angle;
  // printf("hp: %d\n", hp);

  if (this->IsDead()) {
    this->pcannon.lock()->RequestDelete();
    this->associated.RequestDelete();
  }
}

void PenguinBody::Render() {
  
}

bool PenguinBody::Is(std::string type) {
  return type == "PenguinBody";
}

bool PenguinBody::IsDead() {
  return this->hp <= 0;
}

void PenguinBody::ApplyDamage(int damage) {
  this->hp -= damage;
}

void PenguinBody::NotifyCollision(GameObject &other) {
  if(other.GetComponent("Bullet") != nullptr) {
    Bullet *bullet = (Bullet *) other.GetComponent("Bullet");
    if (bullet->TargetsPlayer())
      this->ApplyDamage(bullet->GetDamage());
  }
}