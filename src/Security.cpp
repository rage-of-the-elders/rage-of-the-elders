#include "Security.h"
#include "Collider.h"

Security::Security(GameObject &associated) : Enemy(associated) {

  std::string character = "security";
  this->sprite[MOVING] = new Sprite(this->associated, "img/" + character + "/moving.png", 25, 0.04, 0, true);
  this->sprite[BASIC_ATTACK_ONE] = new Sprite(this->associated, "img/" + character + "/attacking.png", 11, 0.04, 0, false);
  this->sprite[IDLE] = new Sprite(this->associated, "img/" + character + "/idle.png", 25, 0.04, 0, true);
  this->sprite[HURTING] = new Sprite(this->associated, "img/" + character + "/hurting.png", 11, 0.04, 0, false);
  this->sprite[DYING] = new Sprite(this->associated, "img/" + character + "/dying.png", 25, 0.04, 0, false);

  this->associated.AddComponent(this->sprite[IDLE]);
  this->associated.AddComponent(this->sprite[BASIC_ATTACK_ONE]);
  this->associated.AddComponent(this->sprite[MOVING]);
  this->associated.AddComponent(this->sprite[HURTING]);
  this->associated.AddComponent(this->sprite[DYING]);

  this->ActivateSprite(MOVING);

  this->associated.AddComponent(new Collider(this->associated, {0.4,1}, {this->orientation ? RIGHT -1 : 1 * 40,0}));

}

Security::~Security() {

}

void Security::Update(float dt) {
  Enemy::Update(dt);
  Collider *a = (Collider*) this->associated.GetComponent("Collider");
  a->SetOffset({(this->orientation ? RIGHT -40 : 40), 0});
}
