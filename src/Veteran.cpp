#include "Veteran.h"
#include "Sprite.h"
#include "Collider.h"
#include "InputManager.h"

Veteran::Veteran(GameObject &associated) : Component(associated) {
  this->hp = VETERAN_HP;
  this->speed = VETERAN_SPEED;
  this->currentState = IDLE;

  this->sprite = std::vector<Sprite*>(IDLE);

  this->sprite[MOVING] = new Sprite(this->associated, "img/veteran2.png", 24, 0.3, 0, true);
  this->sprite[IDLE] = new Sprite(this->associated, "img/veteran3.png", 2, 0.3, 0, true);

  this->sprite[IDLE]->Activate();
  this->sprite[MOVING]->Desactivate();

  this->sprite[MOVING]->SetScaleX(0.3);
  this->sprite[IDLE]->SetScaleX(0.3);

  this->associated.AddComponent(this->sprite[IDLE]);
  this->associated.AddComponent(this->sprite[MOVING]);

  this->associated.AddComponent(new Collider(this->associated));
}

Veteran::~Veteran(){

}

void Veteran::Start(){

}

void Veteran::Update(float dt){
  if(InputManager::GetInstance().IsKeyDown(D_KEY)){
    this->currentState = MOVING;
    this->speed = Vec2::GetSpeed(0);
    this->associated.box.UpdatePos((speed*10) * dt);
  }
  else{
    this->currentState = IDLE;
  }

  switch (this->currentState) {
    case Veteran::MOVING: {
      if(not this->sprite[MOVING]->IsActive()){
        this->sprite[IDLE]->Desactivate();
        this->sprite[MOVING]->Activate();
      }
    } break;
    case Veteran::IDLE: {
      if(not this->sprite[IDLE]->IsActive()){
        this->sprite[MOVING]->Desactivate();
        this->sprite[IDLE]->Activate();
      }
    } break;
    
    default:
      break;
  }
}

void Veteran::Render(){

}

bool Veteran::Is(std::string type){
  return(type == "Veteran");
}

void Veteran::NotifyCollision(GameObject &other){

}