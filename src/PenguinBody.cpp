#include "PenguinBody.h"
#include "PenguinCannon.h"
#include "Game.h"
#include "InputManager.h"
#include "Camera.h"
#include "Collider.h"
#include "Bullet.h"
#include "Sprite.h"
#include "Sound.h"
#include "math.h"

#define PENGUIN_ACELERATION 15
#define FOWARD_SPEED_LIMIT 40
#define BACKWARDS_SPEED_LIMIT -FOWARD_SPEED_LIMIT / 2.0
#define MAP_X_LIMIT 1408
#define MAP_Y_LIMIT 720

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
  Game::GetInstance().GetCurrentState().AddObject(go);
  this->pcannon = Game::GetInstance().GetCurrentState().GetObjectPtr(go);
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
  Vec2 newPos = speed * dt;

  this->associated.box.UpdatePos(newPos);
  this->associated.angleDeg = angle;

  if (this->associated.box.GetCenter().x  >  570 + (49 * 560) - (50 * 329))
    this->associated.box.SetCenterPos(570 + (49 * 560 - (50 * 329)),
                                      this->associated.box.GetCenter().y);
  if ((this->associated.box.GetCenter().y > MAP_Y_LIMIT))
    this->associated.box.SetCenterPos(this->associated.box.GetCenter().x, MAP_Y_LIMIT);
  else if (this->associated.box.GetCenter().x <= 0)
    this->associated.box.SetCenterPos(0, this->associated.box.GetCenter().y);
  else if (this->associated.box.GetCenter().y <= 0)
    this->associated.box.SetCenterPos(this->associated.box.GetCenter().x, 0);

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

  if (this->IsDead()) {
    GameObject *go = new GameObject();
    go->box = this->associated.box;

    int frameCount = 5;
    float frameTime = 0.5;
    go->AddComponent(new Sprite(*go, "img/penguindeath.png", frameCount, frameTime, frameCount * frameTime));

    go->AddComponent(new Sound(*go, "audio/boom.wav"));
    Game::GetInstance().GetCurrentState().AddObject(go);
    Sound *sound = (Sound *) go->GetComponent("Sound");
    sound->Play(1);
  }
}

void PenguinBody::NotifyCollision(GameObject &other) {
  if(other.GetComponent("Bullet") != nullptr) {
    Bullet *bullet = (Bullet *) other.GetComponent("Bullet");
    if (bullet->TargetsPlayer())
      this->ApplyDamage(bullet->GetDamage());
  }
}

Vec2 PenguinBody::GetPenguinCenter() {
  return this->associated.box.GetCenter();
}
